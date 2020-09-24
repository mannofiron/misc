#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

static const int plate_weights[] = { 1, 2, 4, 6, 8, 10 };
static const int plate_prices[] = { 25, 40, 70, 90, 120, 145 };

int best_price = INT_MAX, plates[34];
static void helper(int depth, int price, uint64_t weights) {
  if (price > best_price)
    return;
  if (!(~weights & UINT64_C(0b1111111111111111111111111111111))) {
    best_price = price;
    for (int i = 0; i < depth; ++i)
      printf("%.1f ", 2.5f * plate_weights[plates[i]]);
    printf(" price=%i\n", price);
    return;
  }
  int start = 0;
  if (depth > 0)
    start = plates[depth - 1];
  for (int i = start; i < 6; ++i) {
    plates[depth] = i;
    helper(depth + 1, price + plate_prices[i], weights | weights << plate_weights[i]);
  }
}

int main() {
  helper(0, 0, 1);
}
