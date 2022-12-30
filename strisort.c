/*
src/strsort.c: Uses red-black trees to sort standard input lexicographically.
src/strrsort1.c: Uses red-black trees to sort standard input lexicographically in reverse order. It does this by traversing the tree in reverse order.
src/strrsort2.c: Uses red-black trees to sort standard input lexicographically in reverse order. It does this by creating a new comparison function revcomp, which simply returns -strcmp(). Now the tree sorts in reverse order, so it is traversed in the forward direction.
src/strusort.c: Uses red-black trees to sort standard input lexicographically, and it removes duplicate lines. It does this by checking for a line before inserting it into the tree.
src/strisort.c: Uses red-black trees to sort standard input lexicographically, ignoring upper and lower case. It does this by creating a separate key, which is the string in upper case. It sorts with that string, and stores the original string in the val.
src/nsort.c: Uses red-black trees to sort like sort -n -- i.e. it treats each line as an integer, and sorts it that way. If the lines are not integers, or there are duplicate lines, anything goes.
src/nsort2.c: Uses red-black trees to sort like sort -n only now if two lines have the same atoi() value, then they are sorted lexicographically. This uses jrb_insert_gen().
src/nsort3.c: Same as nsort2, but instead it uses a two-level red-black tree. If this is confusing to you, please read the next example, which does a very similar thing.

*/

/* Uses red-black trees to sort standard input lexicographically,
   ignoring upper and lower case.  It does this by creating a separate key,
   which is the string in upper case.  It sorts with that string, and stores
   the original string in the val. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "jrb.h"
#include "fields.h"

int main()
{
  JRB b;
  JRB bn;
  IS is;
  int i;
  char *upper_case;

  is = new_inputstruct(NULL);
  b = make_jrb();

  while (get_line(is) >= 0) {
    upper_case = strdup(is->text1);
    for (i = 0; upper_case[i] != '\0'; i++) {
      if (upper_case[i] >= 'a' && upper_case[i] <= 'z') upper_case[i] += ('A'-'a');
    }
    (void) jrb_insert_str(b, upper_case, new_jval_s(strdup(is->text1)));
  }

  jrb_traverse(bn, b) {
    printf("%s", bn->val.s);
  }
  return 0;
}
