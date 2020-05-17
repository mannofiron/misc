/* Toy connect-4 alpha-beta minimax */

#include <stdio.h>
#include <assert.h>

unsigned char board[6];
char col_heights[7] = {0};

static int check_square(int player, int column, int row) {
  return column >= 0 && column < 7 && row >= 0 && row < col_heights[column]
    && (board[row] & (1 << column)) == (player << column);
}

static int move_and_check(int player, int column) {
  int n_in_a_row;
#define check_(column_offset, row_offset)                   \
  for (int i = 1;; ++i) {                                   \
    if (!check_square(player,                               \
                      column + (column_offset),             \
                      col_heights[column] + (row_offset)))  \
      break;                                                \
    if (++n_in_a_row == 4)                                  \
      return 1;                                             \
  }
#define check(column_offset, row_offset) do {   \
    n_in_a_row = 1;                             \
    check_((column_offset), (row_offset));      \
    check_(-(column_offset), -(row_offset));    \
  } while (0)

  check(0, i);
  check(i, 0);
  check(i, i);
  check(i, -i);
  board[col_heights[column]] &= ~(1 << column);
  board[col_heights[column]++] |= player << column;
  return 0;
}

static int solve(size_t depth, int player, int alpha, int beta) {
  if (depth == 0)
    return -2;
  int n_illegal = 0, indet = 0;
  for (int i = 0; i < 7; ++i) {
    if (col_heights[i] < 6) {
      if (move_and_check(player, i)) {
        return 1;
      }
      int sub = -solve(depth-1, !player, -beta, -alpha);
      if (sub == 2) {
        indet = 1;
      } else {
        if (sub > alpha)
          alpha = sub;
        if (alpha >= beta) {
          --col_heights[i];
          return beta;
        }
      }
      --col_heights[i];
    } else {
      ++n_illegal;
    }
  }
  if (n_illegal == 7)
    return 0;
  else if (indet)
    return -2;
  return alpha;
}

int main() {
  size_t depth = 0;
  int result;
  while ((result = solve(++depth, 0, -1, 1)) == -2)
    printf("Finished checking depth %zu\n", depth);
  printf("result=%d, depth=%zu\n", result, depth);
}
