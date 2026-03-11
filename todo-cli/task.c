#include <stdio.h>

#include "task.h"

const char* return_status(Status status) {
  switch(status) {
    case TODO:
      return "🔄";
    case DOING:
      return "💦";
    case DOME:
      return "✅";
    default:
      return "💀";
  }
}

void print_task(Task *t) {
  printf("[%d] %s %s\n",t->id, t->title, return_status(t->status));
}