/* https://www.spoj.com/problems/STACKEZ/ */

#include <stdio.h>

int n;

/* Recursive function, where each stack frame contains one value on the stack */
/* To understand the code, realize that, at each level of the stack, the only
 * important value is the smallest value on the stack; pushing a value greater
 * than the smallest behaves the same as pushing the smallest value. Therefore
 * we make sure that, at each level of the stack, the value stored is the
 * smallest value on the stack; therefore, the stack minimum is always at the
 * top of the stack. */
void helper(int max) {
  while (n --> 0) {
    int t;
    scanf("%d", &t);
    switch (t) {
    case 1:
      /* PUSH : call HELPER with the new top-of-stack value */
      scanf("%d", &t);
      helper(t > max ? t : max);
      break;
    case 2:
      /* POP : return, so this frame (value) is no longer on the stack */
      return;
    case 3:
      /* PRINT : print the top-of-stack value, which is the one in this frame */
      printf("%d\n", max);
    }
  }
}

int main(int argc, char *argv[argc]) {
  scanf("%d", &n);
  helper(0);
}
