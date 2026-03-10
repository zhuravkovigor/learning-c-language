#include <stdio.h>
#include "item.h"

void print_item(struct Item *it, int *index) {
  if (it->discount) {
    printf("%d. %s - %d pcs x %.2f (-%d%%) = %.2f\n", (*index) + 1, it->name, it->quantity, it->price, it->discount, it->quantity * it->price * (1.0 - it->discount / 100.0));
  } else {
    printf("%d. %s - %d pcs x %.2f = %.2f\n", (*index + 1), it->name, it->quantity, it->price, it->quantity * it->price);
  }
}