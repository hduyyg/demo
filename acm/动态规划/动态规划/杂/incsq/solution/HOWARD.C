#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 80
char line[MAX_LEN+1];

int num_cmp(char *n1, int len1, char *n2, int len2)
{
  for (; len1 > 1 && *n1 == '0'; n1++, len1--)
    ;
  for (; len2 > 1 && *n2 == '0'; n2++, len2--)
    ;

  if (len1 < len2) {
    return -1;
  } else if (len1 > len2) {
    return 1;
  } else {
    while (len1 > 0) {
      if (*n1 < *n2) {
	return -1;
      } else if (*n1 > *n2) {
	return 1;
      }
      len1--;
      len2--;
      n1++;
      n2++;
    }
    return 0;
  }
}

int better(char *seq1, char *seq2)
{
  char *p1, *p2;
  int len1, len2, t;

  if (*seq1 == ',') {
    return better(seq1+1, seq2);
  }
  if (*seq2 == ',') {
    return better(seq1, seq2+1);
  }

  if (!(*seq1) && !(*seq2)) {
    return 0;
  }
  assert(*seq1 && *seq2);

  p1 = strchr(seq1, ',');
  p2 = strchr(seq2, ',');
  len1 = (p1) ? p1 - seq1 : strlen(seq1);
  len2 = (p2) ? p2 - seq2 : strlen(seq2);

  t = num_cmp(seq1, len1, seq2, len2);
  if (t < 0) {
    return 0;
  } else if (t > 0) {
    return 1;
  } else {
    return better(seq1 + len1, seq2 + len2);
  }
}

int read_case(void)
{
  scanf("%s", line);
  if (line[0] == '0' && strlen(line) == 1) {
    return 0;
  } else {
    return 1;
  }
}

void solve_case(void)
{
  int best[MAX_LEN], best2[MAX_LEN];
  char seq[2*MAX_LEN+1], best_seq[2*MAX_LEN+1];
  int i, j, k, k1, k2, n, flag;

  n = strlen(line);

  /* first minimize last element */
  best[0] = 1;
  for (i = 1; i < n; i++) {
    best[i] = -1;
    for (j = 1; j <= i && best[i] == -1; j++) {
      k2 = i+1-j;
      k1 = k2 - best[k2-1];
      if (num_cmp(line+k1, best[k2-1], line+k2, j) < 0) {
	best[i] = j;
      }
    }
    if (best[i] == -1) {
      best[i] = i+1;
    }
  }
  
  flag = 0;
  if (!num_cmp(line+n-best[n-1], best[n-1], line, n)) {
    strcpy(best_seq, line);
    flag = 1;
  }
  for (k = best[n-1]; k < n && !num_cmp(line+n-best[n-1], best[n-1],
					 line+n-k, k); k++) {
    k1 = n-k-best[n-k-1];
    if (num_cmp(line+k1, best[n-k-1], line+n-k, k) < 0) {
      /* now go backward to break ties */
      best2[n-k] = k;
      for (i = n-k; i >= 0; i--) {
	for (j = 1; i+j <= n-k; j++) {
	  if (num_cmp(line+i, j, line+i+j, best2[i+j]) < 0) {
	    best2[i] = j;
	  }
	}
      }

      for (i = k2 = 0; i < n; i += best2[i]) {
	if (i) {
	  seq[k2++] = ',';
	}
	for (j = 0; j < best2[i]; j++) {
	  seq[k2++] = line[i+j];
	}
      }
      seq[k2++] = 0;

      if (!flag || better(seq, best_seq)) {
	strcpy(best_seq, seq);
	flag = 1;
      } 
    }
  }
  assert(flag);
  printf("%s\n", best_seq);
}

int main(void)
{
  while (read_case()) {
    solve_case();
  }
  return 0;
}
