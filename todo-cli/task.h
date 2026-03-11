#ifndef TASK_H
#define TASK_H


typedef enum {
  TODO,
  DOING,
  DONE
} Status;

typedef struct {
  int id;
  char title[30];
  Status status;
} Task;


void print_task(Task *t);

#endif