/* Solution to increasing sequences, revised 8/21/02 to fix "leading
  zeros"
  Bob Roos
*/

#include <stdio.h>
#include <string.h>

char digits[81];   /* input digits */
int length;        /* length of " */
int found;

char sequence[80][81];  /* reverse of sequence currently being tested */
int seqlength;          /* length of " " " */
char bestseq[80][81];   /* best sequence found so far (reversed) */
int bestseqlength;      /* length of " " " */


/* compare two strings numerically/lexicographically (e.g.,
   00062 < 814, 28193283 < 00030000000, etc.)
*/
int compare(char *first, char *second)
{
  char temp1[81], temp2[81];
  int i,maxlength;

  for (i = 0; i < 80; i++)
  {
    temp1[i] = '0';
    temp2[i] = '0';
  }
  temp1[80] = 0;
  temp2[80] = 0;
  
  /* pad the shorter one with zeros on the left so both have
     same length: */
  maxlength = strlen(first);
  if (strlen(first) < strlen(second))
  {
    maxlength = strlen(second);
  }
  strcpy(temp1+(maxlength-strlen(first)),first);
  strcpy(temp2+(maxlength-strlen(second)),second);

  return strcmp(temp1,temp2);
}

/* print out the final answer */
void printanswer()
{
  int i;
 
  for (i = bestseqlength-1; i >= 1; i--)
    printf("%s,",bestseq[i]);
  printf("%s\n",bestseq[0]);
}

/* Compare current backtrack solution to best found so far */
void updatebest()
{
  int i,j,k;

  i = seqlength-1;
  j = bestseqlength-1;
  while (i > 0 && j > 0 && compare(sequence[i],bestseq[j]) == 0)
  {
    i--;
    j--;
  }
  if (bestseqlength <= 0 || compare(sequence[i],bestseq[j]) > 0)
  {
    for (k = 0; k < seqlength; k++)
      strcpy(bestseq[k],sequence[k]);
    bestseqlength = seqlength;
  }
}

/* Do the backtracking search */
void backtrack()
{
  int i;

  /* base case: see if digits string is empty: */
  if (strlen(digits) <= 0)
  {
    found = 1;
    updatebest();
    return;
  }

  /* Otherwise, try every viable suffix, from longest to shortest.
     "Viable" means suffix value is less than last element in sequence.
  */
  i = strlen(digits) - 1; /* start with final unused digit */
  while (i >= 0 && compare(digits+i,sequence[seqlength-1]) < 0)
    i--;
  i++;
  /* Check for failure (unable to find smaller value): */
  while (i < strlen(digits))
  {
    strcpy(sequence[seqlength++],digits+i);
    digits[i] = 0;
    backtrack();
    /* restore deleted digit: */
    digits[i] = sequence[seqlength-1][0];
    --seqlength;
    i++;
  }

  return;
}


void solve()
{
  int i;
  found = 0;

  bestseqlength = 0;

  /* Try all suffixes, from shortest to longest: */

  for (i = strlen(digits) - 1; i >= 0; i--)
  {
    strcpy(sequence[0],digits+i);
    seqlength=1;

    /* "remove" suffix from string: */
    digits[i] = 0;

    /* backtrack to find remaining elements in sequence */
    backtrack();
    if(found && (i == 0 ||(i > 0 && digits[i-1] != '0')))
      break;

    /* restore old suffix */
    strcpy(digits+i,sequence[0]);
  }
  printanswer();
}

int main()
{
  while(scanf("%s",digits))
  {
    if (strcmp(digits,"0") == 0)
      break;
//    printf("String is \"%s\"\n",digits);
    solve();
  }
}
