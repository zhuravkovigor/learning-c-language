#ifndef ITEM_H
#define ITEM_H

struct Item {
  char name[30];
  int quantity;
  float price;
  int discount;
};

void print_item(struct Item *it, int *index);

#endif