Program ScaleRhyme_Cash;
Const
	InPath = 'cash.in' ;
	OutPath = 'cash.out' ;
	MaxN = 100000 ;
	Infinity = MaxLongint Div 8 ;
Type
	TIndex = Longint ;
	PTreapNode = ^TTreapNode ;
	TTreapNode = Record
		LRange,RRange,A,B:Extended;
		Priority:TIndex;
		LeftNode,RightNode:PTreapNode;
	End;
	TTreap = Object
		NullNode,RootNode,TmpNode:PTreapNode;
		A,B:Extended;
		Procedure Initialize;
		Procedure LeftRotate(Var CurNode:PTreapNode);
		Procedure RightRotate(Var CurNode:PTreapNode);
		Procedure DeleteNode(Var CurNode:PTreapNode);
		Procedure InsertNode(Var CurNode:PTreapNode;P,Q,L,R:Extended);
		Procedure Insert(P,Q,L,R:Extended);
		Procedure GetAB(E:Extended);
	End;
	Procedure TTreap.Initialize;
	Begin
		New(NullNode);
		NullNode^.Priority := Infinity ;
		NullNode^.LeftNode := NullNode ;
		NullNode^.RightNode := NullNode ;
		RootNode := NullNode ;
	End;
	Procedure TTreap.LeftRotate(Var CurNode:PTreapNode);
	Begin
		TmpNode := CurNode^.LeftNode ;
		CurNode^.LeftNode := TmpNode^.RightNode ;
		TmpNode^.RightNode := CurNode ;
		CurNode := TmpNode ;
	End;
	Procedure TTreap.RightRotate(Var CurNode:PTreapNode);
	Begin
		TmpNode := CurNode^.RightNode ;
		CurNode^.RightNode := TmpNode^.LeftNode ;
		TmpNode^.LeftNode := CurNode ;
		CurNode := TmpNode ;
	End;
	Procedure TTreap.DeleteNode(Var CurNode:PTreapNode);
	Begin
		If (CurNode^.LeftNode = NullNode) And (CurNode^.RightNode = NullNode) Then
		Begin
			Dispose(CurNode);
			CurNode := NullNode ;
			Exit;
		End;
		If CurNode^.LeftNode^.Priority < CurNode^.RightNode^.Priority Then
		Begin
			LeftRotate(CurNode);
			DeleteNode(CurNode^.RightNode);
		End
		Else	// CurNode^.LeftNode^.Priority >= CurNode^.RightNode^.Priority Then
		Begin
			RightRotate(CurNode);
			DeleteNode(CurNode^.LeftNode);
		End;
	End;
	Procedure TTreap.InsertNode(Var CurNode:PTreapNode;P,Q,L,R:Extended);
	Var
		X:Extended;
	Begin
		If CurNode = NullNode Then
		Begin
			New(CurNode);
			CurNode^.A := P ;
			CurNode^.B := Q ;
			CurNode^.LRange := L ;
			CurNode^.RRange := R ;
			CurNode^.Priority := Random(Infinity) ;
			CurNode^.LeftNode := NullNode ;
			CurNode^.RightNode := NullNode ;
			Exit;
		End;
		If (CurNode^.A >= P) And (CurNode^.B >= Q) Then
			Exit;
		If (CurNode^.A <= P) And (CurNode^.B <= Q) Then
		Begin
			DeleteNode(CurNode);
			InsertNode(CurNode,P,Q,L,R);
			Exit;
		End;
		X := (P - CurNode^.A)/(CurNode^.B - Q) ;
		If CurNode^.B > Q Then
		Begin
			If X < L Then
				Exit;
			If X < R Then
				R := X ;
			If CurNode^.RRange < X Then
			Begin
				DeleteNode(CurNode);
				InsertNode(CurNode,P,Q,L,R);
				Exit;
			End;
			If CurNode^.LRange < X Then
				CurNode^.LRange := X ;
		End
		Else	//CurNode^.B < Q
		Begin
			If X > R Then
				Exit;
			If X > L Then
				L := X ;
			If CurNode^.LRange > X Then
			Begin
				DeleteNode(CurNode);
				InsertNode(CurNode,P,Q,L,R);
				Exit;
			End;
			If CurNode^.RRange > X Then
				CurNode^.RRange := X ;
		End;
		If CurNode^.LRange >= R Then
		Begin
			InsertNode(CurNode^.LeftNode,P,Q,L,R);
			If CurNode^.LeftNode^.Priority < CurNode^.Priority Then
				LeftRotate(CurNode);
		End
		Else	//CurNode^.RRange < L
		Begin
			InsertNode(CurNode^.RightNode,P,Q,L,R);
			If CurNode^.RightNode^.Priority < CurNode^.Priority Then
				RightRotate(CurNode);
		End;
	End;
	Procedure TTreap.Insert(P,Q,L,R:Extended);
	Begin
		InsertNode(RootNode,P,Q,L,R);
	End;
	Procedure TTreap.GetAB(E:Extended);
	Begin
		TmpNode := RootNode ;
		While True Do
		Begin
			If (TmpNode^.LRange <= E) And (TmpNode^.RRange > E) Then
			Begin
				A := TmpNode^.A ;
				B := TmpNode^.B ;
				Exit;
			End;
			If TmpNode^.LRange > E Then
				TmpNode := TmpNode^.LeftNode
			Else	//TmpNode^.RRange < E
				TmpNode := TmpNode^.RightNode ;
		End;
	End;
Var
	FileIn,FileOut:Text;
	N:TIndex;
	StartMoney:Extended;
	A,B,Rate:Array [1..MaxN + 1] Of Extended;
	Q:Extended;
	F,FA,FB:Array [1..MaxN] Of Extended;
	Treap:TTreap;
	Procedure Init;
	Var
		I:TIndex;
	Begin
		ReadLn(FileIn,N,StartMoney);
		For I := 1 To N Do
			ReadLn(FileIn,A[I],B[I],Rate[I]);
	End;
	Procedure Main1;
	Var
		I,J:TIndex;
	Begin
		Q := StartMoney ;
		F[1] := Q/(A[1] * Rate[1] + B[1]) ;
		For I := 2 To N Do
		Begin
			For J := 1 To I - 1 Do
				If Q < F[J] * B[I] + F[J] * Rate[J] * A[I] Then
					Q := F[J] * B[I] + F[J] * Rate[J] * A[I] ;
			F[I] := Q/(A[I] * Rate[I] + B[I]) ;
		End;
		WriteLn(FileOut,Q:0:3);
	End;
	Procedure Main2;
	Var
		I:TIndex;
	Begin
		Randomize;
		Treap.Initialize;
		Q := StartMoney ;
		FB[1] := Q/(A[1] * Rate[1] + B[1]) ;
		FA[1] := FB[1] * Rate[1] ;
		Treap.Insert(FA[1],FB[1],0,Infinity);
		For I := 2 To N Do
		Begin
			Treap.GetAB(B[I]/A[I]);
			If A[I] * Treap.A + B[I] * Treap.B > Q Then
				Q := A[I] * Treap.A + B[I] * Treap.B ;
			FB[I] := Q/(A[I] * Rate[I] + B[I]) ;
			FA[I] := FB[I] * Rate[I] ;
			Treap.Insert(FA[I],FB[I],0,Infinity);
		End;
		WriteLn(FileOut,Q:0:3);
	End;
Begin
	Assign(FileIn,InPath);
	Reset(FileIn);
	Assign(FileOut,OutPath);
	Rewrite(FileOut);
	Init;
	If N <= 1000 Then
		Main1
	Else
		Main2;
	Close(FileIn);
	Close(FileOut);
End.
