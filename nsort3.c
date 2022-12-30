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
/* Same as nsort2, but instead it uses a two-level red-black tree.
   If this is confusing to you, please read the next example in the lecture
   notes, which does a very similar thing. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int main()
{
  JRB level_1, level_2;
  JRB bn, bn2;
  IS is;

  is = new_inputstruct(NULL);
  level_1 = make_jrb();

  /* Read each line and look for it in the first level tree. */

  while (get_line(is) >= 0) {
    bn = jrb_find_int(level_1, atoi(is->text1));

    /* If it's not there, insert it with an empty jrb as its val. */

    if (bn == NULL) {
      bn = jrb_insert_int(level_1, atoi(is->text1), new_jval_v((void *)make_jrb()));
    }

    /* Now insert the string into the second level tree. */

    level_2 = (JRB) jval_v(bn->val);
    jrb_insert_str(level_2, strdup(is->text1), new_jval_v(NULL));
  }

  /* To print the tree, you need to do a nested double-traversal. */

  jrb_traverse(bn, level_1) {
    level_2 = (JRB) jval_v(bn->val);
    jrb_traverse(bn2, level_2) {
      printf("%s", bn2->key.s);
    }
  }

  return 0;
}
