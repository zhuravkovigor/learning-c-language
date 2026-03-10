#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"

int main() {
  int count = 0;

  while (count <= 0) {
      printf("Product Store: Enter count of items:\n");
      scanf("%d", &count);
      
      if (count <= 0) {
        printf("---------- Error ----------\n");
        printf("Sorry %d is incorrect number, please try again\n", count);
        printf("                           \n");
      }
    }
    
    struct Item *items = malloc(count * sizeof(struct Item));

    // Check malloc
    if (items == NULL) {
      printf("Memory allocation problem\n!");
      return 1;
    }

    float total_price = 0.0;

    for (int i = 0; i < count; i++) {

      // Name
      printf("Enter an item name:\n");
      scanf(" %[^\n]", items[i].name);

      // Quantity
      printf("Enter an item quantity\n");
      scanf("%d", &items[i].quantity);

      // Price
      printf("Enter an item price\n");
      scanf("%f", &items[i].price);

      // Discount, optional
      printf("Enter discount (optional):\n");
      scanf("%d", &items[i].discount);

      // Summarizing
      total_price = total_price + (items[i].price * items[i].quantity);
    }

    FILE *f = fopen("report.txt", "w");

    if (f == NULL) {
      printf("Error while opening file\n");
      return 1;
    }

    fprintf(f, "---------------CHECK--------------\n");
    printf("---------------CHECK--------------\n");
    for (int i = 0; i < count; i++) {
      print_item(&items[i], &i);

      if (items[i].discount) {
        fprintf(f, "%d. %s - %d pcs x %.2f (-%d%%) = %.2f\n", i + 1, items[i].name, items[i].quantity, items[i].price, items[i].discount, items[i].quantity * items[i].price * (1.0 - items[i].discount / 100));
      } else {
        fprintf(f, "%d. %s - %d pcs x %.2f = %.2f\n", i + 1, items[i].name, items[i].quantity, items[i].price, items[i].quantity * items[i].price);
      }
    }

  fprintf(f, "----------------------------------\n");
  fprintf(f, "Total price is: %0.2f\n", total_price);
  fclose(f);

  printf("----------------------------------\n");
  printf("Total price is: %0.2f\n", total_price);
  printf("Data is saved to report.txt\n");
  printf("----------------------------------\n");

  char search_input[24];
  while (1) {
    printf("Find: ");
    scanf(" %[^\n]", search_input);
    int has_found = false;

    if (strcmp(search_input, "exit") == 0) {
      break;
    }

    for (int i = 0; i < count; i++) {
      if (strcmp(items[i].name, search_input) == 0) {
        printf("---------------Result--------------\n");
        print_item(&items[i], &i);
        has_found = true;
        break;
      } 
    }

    if (!has_found) {
      printf("Item %s not found, please try again..", search_input);
      printf("-------------------------------------");
    }
  }

  free(items);
  return 0;
}