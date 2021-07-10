{$MODE OBJFPC}

{$IFDEF RELEASE}
  {$Q-,R-,S-}
  {$ASSERTIONS OFF}
  {$INLINE ON}
  {$UNDEF DEBUG_BINTREE}
  {$UNDEF DEBUG_CALC}
  {$UNDEF DEBUG_MEMORY}
  {$UNDEF DEBUG_SIMPLE}
{$ELSE}
  {$Q+,R+,S+}
  {$ASSERTIONS ON}
  {$INLINE ON}
  {$DEFINE DEBUG_BINTREE}
  {$DEFINE DEBUG_CALC}
  {$UNDEF DEBUG_MEMORY}
  {$DEFINE DEBUG_SIMPLE}
{$ENDIF}
program network;

const
  InputFileName = 'network.in';
  OutputFileName = 'network.out';

const
  maxn = 401;
  maxm = 2 * maxn;
  maxp = 401;
  maxpool = 10;
  maxcost = 200000000;

type
  integer = longint;

  TData = array [1..2, 0..maxp, 1..maxm] of integer;
  PData = ^TData;

  TMemoryPool = class
  private
    data: array [1..maxpool] of PData;
    dataPooled: integer;
  protected
    function Allocate(): PData;
  public
    constructor Create();
    function get_New(): PData;
    procedure Recycle(var p: PData);
  end;

constructor TMemoryPool.Create();
begin
  dataPooled := maxpool;
  fillchar(data, sizeof(data), 0);
end;

function TMemoryPool.get_New(): PData;
begin
  {$IFDEF DEBUG_MEMORY}
  writeln(dataPooled);
  {$ENDIF}
  if dataPooled = 0 then get_New := Allocate()
  else
  begin
    if data[dataPooled] = nil then data[dataPooled] := Allocate();
    get_New := data[dataPooled];
    dec(dataPooled);
  end;
end;

procedure TMemoryPool.Recycle(var p: PData);
begin
  if dataPooled = maxpool then
  begin
    dispose(p);
    p := nil;
  end else
  begin
    inc(dataPooled);
    data[dataPooled] := p;
    p := nil;
  end;
end;

function TMemoryPool.Allocate(): PData;
begin
  Allocate := new(PData);
end;

type
  TList = array [0..maxm] of integer;

var
  pool: TMemoryPool;
  p, n, m, root: integer;
  fa, deg: array [1..maxn] of integer;
  c, w, calc, size: array [1..maxm] of integer;
  left, right, father: array [1..maxm] of integer;
  above: array [1..maxm, 1..maxm] of boolean;
  dist: array [1..maxm, 1..maxm] of integer;
  list: array [1..maxm] of TList;
  order: array [1..maxm] of integer;
  orderc: integer;
  d: array [1..maxm] of PData;
  _tmpArr: array [0..maxm] of integer;

{$IFDEF DEBUG_BINTREE}
procedure printBinaryTree(const root, indent: integer);
begin
  writeln('': indent, root, '(', c[root], ')');
  if left[root] <> -1 then printBinaryTree(left[root], indent+2);
  if right[root] <> -1 then printBinaryTree(right[root], indent+2);
end;
{$ENDIF}

procedure findAbove(const root: integer);
var
  i: integer;
begin
  if father[root] <> -1 then
    for i:=1 to m do
      if above[i, father[root]] then
        above[i, root] := true;
  above[root, root] := true;
  if left[root] <> -1 then findAbove(left[root]);
  if right[root] <> -1 then findAbove(right[root]);
end;

procedure initialize(); inline;
var
  i, j: integer;
begin
  assign(input, InputFileName);
  reset(input);

  read(n, p);
  if p > n then p := n;

  fillchar(fa,     sizeof(fa),     $FF);
  fillchar(left,   sizeof(left),   $FF);
  fillchar(right,  sizeof(right),  $FF);
  fillchar(father, sizeof(father), $FF);

  for i:=1 to n   do read(c[i]);
  for i:=1 to n-1 do read(j, fa[j], w[j]);

  // build binary tree
  m := n;
  fillchar(deg, sizeof(deg), 0);
  for i:=1 to n do
    if fa[i] <> -1 then
    begin
      inc(deg[fa[i]]);
      if deg[fa[i]] = 1 then
      begin
          left[fa[i]] := i;
          father[i] := fa[i];
      end else
      if deg[fa[i]] = 2 then
      begin
          right[fa[i]] := i;
          father[i] := fa[i];
      end else
      begin
        inc(m);
        left[m] := left[fa[i]];
        father[left[fa[i]]] := m;
        left[fa[i]] := m;
        father[m] := fa[i];
        right[m] := i;
        father[i] := m;
        w[m] := 0;
        c[m] := maxcost;
      end;
    end else root := i;
  {$IFDEF DEBUG_BINTREE}printBinaryTree(root, 0);{$ENDIF}

  fillchar(above, sizeof(above), false);
  findAbove(root);
  pool := TMemoryPool.Create();

  close(input);

end;

function findCalc(const root: integer): integer;
var
  leftCalc, rightCalc: integer;
begin
  if (left[root] = -1) and (right[root] = -1) then
  begin
    findCalc := 1;
    calc[root] := 1;
  end else
  if left[root] = -1 then
  begin
    calc[root] := 2;
    rightCalc := findCalc(right[root]);
    if rightCalc > calc[root] then calc[root] := rightCalc;
  end else
  if right[root] = -1 then
  begin
    calc[root] := 2;
    leftCalc := findCalc(left[root]);
    if leftCalc > calc[root] then calc[root] := leftCalc;
  end else
  begin
    leftCalc := findCalc(left[root]);
    rightCalc := findCalc(right[root]);
    if leftCalc = rightCalc then calc[root] := leftCalc + 1 else
    if leftCalc > rightCalc then calc[root] := leftCalc else
    calc[root] := rightCalc;
    if calc[root] < 3 then calc[root] := 3;
  end;
end;

procedure merge(const root, tar: integer; var a, b: TList; const fixup: integer);
var
  i, t, j, c: integer;
begin
  j := 1;
  c := 0;
  for i:=1 to b[0] do
  if not above[b[i], root] then
  begin
    t := dist[tar, b[i]] + fixup;
    while (j <= a[0]) and (dist[root, a[j]] <= t) do
    begin
      inc(c);
      _tmpArr[c] := a[j];
      inc(j);
    end;
    inc(c);
    _tmpArr[c] := b[i];
    dist[root, b[i]] := t;
    dist[b[i], root] := t;
  end;
  while j <= a[0] do
  begin
    inc(c);
    _tmpArr[c] := a[j];
    inc(j);
  end;
  a := _tmpArr;
  a[0] := c;
end;

procedure findDist(const root: integer);
var
  i: integer;
begin
  list[root, 0] := 1;
  list[root, 1] := root;
  dist[root, root] := 0;
  if father[root] <> -1 then
  begin
    inc(list[root, 0], list[father[root], 0]);
    for i:=1 to list[father[root], 0] do
    begin
      list[root, i+1] := list[father[root], i];
      dist[root, list[root, i+1]] := dist[father[root], list[root, i+1]] + w[root];
      dist[list[root, i+1], root] := dist[root, list[root, i+1]];
    end;
  end;
  if left[root]  <> -1 then findDist(left[root]);
  if right[root] <> -1 then findDist(right[root]);
  if left[root]  <> -1 then merge(root, left[root], list[root], list[left[root]], w[left[root]]);
  if right[root] <> -1 then merge(root, right[root], list[root], list[right[root]], w[right[root]]);
end;

procedure merge2(const root, tar: integer; var a, b: TList; const fixup: integer);
var
  i, t, j, c: integer;
begin
  j := 1;
  c := 0;
  for i:=1 to b[0] do
    if not above[root, b[i]] and not above[b[i], root] then
    begin
      t := dist[tar, b[i]] + fixup;
      while (j <= a[0]) and (dist[root, a[j]] <= t) do
      begin
        inc(c);
        _tmpArr[c] := a[j];
        inc(j);
      end;
      inc(c);
      _tmpArr[c] := b[i];
      dist[root, b[i]] := t;
      dist[b[i], root] := t;
    end;
  while j <= a[0] do
  begin
    inc(c);
    _tmpArr[c] := a[j];
    inc(j);
  end;
  a := _tmpArr;
  a[0] := c;
end;

procedure findDist2(const root: integer);
begin
  if father[root] <> -1 then
    merge2(root, father[root], list[root], list[father[root]], w[root]);
  if left[root]  <> -1 then findDist2(left[root]);
  if right[root] <> -1 then findDist2(right[root]);
end;

function findAll(const root: integer): integer;
begin
  if (left[root] = -1) and (right[root] = -1) then
  begin
    size[root] := 1;
  end else
  if left[root] = -1 then
  begin
    size[root] := 1 + findAll(right[root]);
  end else
  if right[root] = -1 then
  begin
    size[root] := 1 + findAll(left[root]);
  end else
  begin
    size[root] := 1;
    if calc[left[root]] > calc[right[root]] then
    begin
      inc(size[root], findAll(left[root]));
      inc(size[root], findAll(right[root]));
    end else
    begin
      inc(size[root], findAll(right[root]));
      inc(size[root], findAll(left[root]));
    end;
  end;
  inc(orderc);
  order[orderc] := root;
  findAll := size[root];
end;

function min(const a, b: integer): integer;
begin
  if a < b then min := a else min := b;
end;

function max(const a, b: integer): integer;
begin
  if a > b then max := a else max := b;
end;

{$IFDEF DEBUG_CALC}
procedure printAnsVal(const root: integer; const ans: PData);
var
  i, q: integer;
begin
  writeln('-----------', root, '------------');
  writeln('F:');
  for q:=0 to min(size[root], p) do
  begin
    for i:=1 to m do write(ans^[1, q, i], ' ');
    writeln;
  end;
  writeln('G:');
  for q:=0 to min(size[root], p) do
  begin
    writeln('q=', q);
    for i:=1 to m do write(ans^[2, q, i], ' ');
    writeln;
  end;
end;
{$ENDIF}

function calculate: PData;
var
  leftVal, rightVal, res: PData;
  i, k, q, t, q1, root, curr, last, lsize, rsize: integer;
begin
  for k:=1 to m do
  begin
    root := order[k];
    if (left[root] = -1) and (right[root] = -1) then
    begin
      res := pool.get_New();
      //fillchar(res^, sizeof(res^), $FF);
      // leaf nodes
      for i := 1 to m do
      begin
        res^[2, 0, i] := maxcost;
        res^[2, 1, i] := c[root];
        if not above[root, i] then
        begin
          res^[1, 0, i] := dist[root, i];
          res^[1, 1, i] := min(res^[1, 0, i], c[root]);
        end else
        begin
          res^[1, 0, i] := maxcost;
          res^[1, 1, i] := maxcost;
        end;
      end;
    end else
    if left[root] = -1 then
    begin
      rightVal := d[right[root]];
      res := pool.get_New();
      for i := 1 to m do
      begin
        res^[2, 0, i] := maxcost;
        if not above[root, i] then
        begin
          res^[1, 0, i] := dist[root, i] + rightVal^[1, 0, i];
        end else res^[1, 0, i] := maxcost;
      end;
      for q := 1 to min(p, size[root]) do
      begin
        if c[root] < maxcost then res^[2, q, root] := c[root] + rightVal^[1, q-1, root]
        else res^[2, q, root] := maxcost;
        res^[1, q, root] := maxcost;
        for i := 2 to m do
        begin
          curr := list[root, i];
          last := list[root, i-1];
          res^[2, q, curr] := res^[2, q, last];
          if above[root, curr] then
          begin
            if dist[root, curr] + rightVal^[2, q, curr] < res^[2, q, curr] then
              res^[2, q, curr] := dist[root, curr] + rightVal^[2, q, curr];
            res^[1, q, curr] := maxcost;
          end else
          begin
            res^[1, q, curr] := res^[2, q, curr];
            if dist[root, curr] + rightVal^[1, q, curr] < res^[1, q, curr] then
              res^[1, q, curr] := dist[root, curr] + rightVal^[1, q, curr];
          end;
        end;
      end;
      pool.Recycle(rightVal);
      d[right[root]] := nil;
    end else
    if right[root] = -1 then
    begin
      leftVal := d[left[root]];
      lsize := size[left[root]];
      res := pool.get_New();
      for i := 1 to m do
      begin
        res^[2, 0, i] := maxcost;
        if not above[root, i] then
        begin
          res^[1, 0, i] := dist[root, i] + leftVal^[1, 0, i];
        end else res^[1, 0, i] := maxcost;
      end;
      for q := 1 to min(p, size[root]) do
      begin
        if c[root] < maxcost then res^[2, q, root] := c[root] + leftVal^[1, q-1, root]
        else res^[2, q, root] := maxcost;
        res^[1, q, root] := maxcost;
        for i := 2 to m do
        begin
          curr := list[root, i];
          last := list[root, i-1];
          res^[2, q, curr] := res^[2, q, last];
          if above[root, curr] then
          begin
            if (q <= lsize) and (dist[root, curr] + leftVal^[2, q, curr] < res^[2, q, curr]) then
              res^[2, q, curr] := dist[root, curr] + leftVal^[2, q, curr];
            res^[1, q, curr] := maxcost;
          end else
          begin
            res^[1, q, curr] := res^[2, q, curr];
            if (q <= lsize) and (dist[root, curr] + leftVal^[1, q, curr] < res^[1, q, curr]) then
              res^[1, q, curr] := dist[root, curr] + leftVal^[1, q, curr];
          end;
        end;
      end;
      pool.Recycle(leftVal);
      d[left[root]] := nil;
    end else
    begin
      leftVal := d[left[root]];
      rightval := d[right[root]];

      res := pool.get_New();

      // function codes
      for i := 1 to m do
      begin
        res^[2, 0, i] := maxcost;
        if not above[root, i] then
        begin
          res^[1, 0, i] := dist[root, i] + leftVal^[1, 0, i] + rightVal^[1, 0, i];
        end else res^[1, 0, i] := maxcost;
      end;
      for q := 1 to min(p, size[root]) do
      begin
        for i := 1 to m do
          if i = root then
          begin
            res^[2, q, i] := maxcost;
            if c[i] < maxcost then
            begin
              for q1 := max(0, q - size[right[root]] - 1) to min(q-1, size[left[root]]) do
              begin
                t := leftVal^[1, q1, i] + rightVal^[1, q - q1 - 1, i];
                if t < res^[2, q, i] then res^[2, q, i] := t;
              end;
              inc(res^[2, q, i], c[i]);
            end;
            res^[1, q, i] := maxcost;
          end else
          if not above[root, i] then
          begin
            res^[1, q, i] := maxcost;
            for q1 := max(0, q - size[right[root]]) to min(q, size[left[root]]) do
            begin
              t := dist[root, i] + leftVal^[1, q1, i] + rightVal^[1, q-q1, i];
              if t < res^[1, q, i] then res^[1, q, i] := t;
            end;
            res^[2, q, i] := maxcost;
          end else
          if above[left[root], i] then
          begin
            res^[2, q, i] := maxcost;
            for q1 := max(1, q - size[right[root]]) to min(q, size[left[root]]) do
            begin
              t := dist[root, i] + leftVal^[2, q1, i] + rightVal^[1, q-q1, i];
              if t < res^[2, q, i] then res^[2, q, i] := t;
            end;
            res^[1, q, i] := maxcost;
          end else // above[right[root], i]
          begin
            res^[2, q, i] := maxcost;
            for q1 := max(0, q - size[right[root]]) to min(q-1, size[left[root]]) do
            begin
              t := dist[root, i] + leftVal^[1, q1, i] + rightVal^[2, q-q1, i];
              if t < res^[2, q, i] then res^[2, q, i] := t;
            end;
            res^[1, q, i] := maxcost;
          end;
      end;

      for q := 1 to min(p, size[root]) do
      begin
        for i := 2 to m do
        begin
          curr := list[root, i];
          last := list[root, i-1];
          if res^[2, q, last] < res^[2, q, curr] then res^[2, q, curr] := res^[2, q, last];
          if not above[root, curr] then
          begin
            if res^[2, q, curr] < res^[1, q, curr] then
              res^[1, q, curr] := res^[2, q, curr];
          end;
        end;
      end;

      pool.Recycle(leftVal);
      pool.Recycle(rightVal);
    end;

    d[root] := res;
    {$IFDEF DEBUG_CALC}printAnsVal(root, res);{$ENDIF}
  end;

  calculate := res;
end;

procedure clearDist;
var
  i, j: integer;
begin
  for i:=n+1 to m do
    for j:=1 to m do
    begin
      dist[i, j] := 0;
      dist[j, i] := 0;
    end;
end;

var
  ans: PData;

procedure printAns(const ans: PData);
var
  min, minp, i: integer;
begin
  assign(output, OutputFileName);
  rewrite(output);
  min := maxcost;
  for i:=1 to p do
    if ans^[2, i, list[root, m]] < min then
    begin
      min := ans^[2, i, list[root, m]];
      minp := i;
    end;
  writeln(min);
  writeln(minp);
  close(output);
end;

{$IFDEF DEBUG_SIMPLE}
var
  i, j: integer;
{$ENDIF}

begin
  initialize();
  findCalc(root);
  fillchar(dist, sizeof(dist), $FF);
  findDist(root);
  findDist2(root);
  clearDist();
  orderc := 0;
  findAll(root);
  assert(orderc = m);
  {$IFDEF DEBUG_SIMPLE}
  assign(output, 'network.mem');
  rewrite(output);
  for i:=1 to m do assert(list[i, 0] = m);
  for i:=1 to m do assert(list[i, 1] = i);
  for i:=1 to m do
  begin
    for j:=1 to m do
      write(dist[i, j], ' ');
    writeln;
  end;
  close(output);
  {$ENDIF}
  {$IFDEF DEBUG_CALC}
  assign(output, 'network.dbg');
  rewrite(output);
  {$ENDIF}
  ans := calculate();
  {$IFDEF DEBUG_CALC}close(output);{$ENDIF}
  printAns(ans);
end.
