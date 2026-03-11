#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "task.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Not enough params for the app\n");

    return 1;
  }

  if (strcmp(argv[1], "add") == 0) {
    if (argv[2]) {
      FILE *f = fopen("tasks.dat", "ab+");

      if (f == NULL) {
        printf("File doesn't exist");

        return 1;
      }

      Task task;
      // count of task to add id
      // const int count = (ftell(f) * fseek(f, 0, SEEK_END))  / sizeof(Task);
      fseek(f, 0, SEEK_END);

      const int size = ftell(f);
      const int count = size / sizeof(Task);      
      
      task.id = count + 1;
      strncpy(task.title, argv[2], 29);
      task.title[29] = '\0';
      task.status = TODO;

      print_task(&task);

      fwrite(&task, sizeof(Task), 1, f);
      fclose(f);
    } else {
      printf("There is no value for a new task, write next after add\n");
    }
  } else if (strcmp(argv[1], "list") == 0) {
    FILE *f = fopen("tasks.dat", "rb");
    if (f == NULL) {
      printf("There is no file to read");

      return 1;
    }

    Task task;

    while (fread(&task, sizeof(Task), 1, f) == 1) {
      print_task(&task);
    }
  } else if (strcmp(argv[1], "done") == 0) {
    const int target_id = atoi(argv[2]);
    FILE *f = fopen("tasks.dat", "rb+");

    int found = 0;

    Task task;
    while(fread(&task, sizeof(Task), 1, f)) {
      if (task.id == target_id) {
        task.status = DONE;
        fseek(f, -sizeof(Task), SEEK_CUR);
        fwrite(&task, sizeof(Task), 1, f);
        printf("Task %s is DONE!\n", task.title);
        found = 1;
        break;
      }
    }

    if (!found) {
      printf("Sorry, but task with id [%d] was not found\n", target_id);
    }

    fclose(f);
  } else if (strcmp(argv[1], "stats") == 0) {
    FILE *f = fopen("tasks.dat", "rb");

    fseek(f, 0, SEEK_END);
    const int count = ftell(f) / sizeof(Task);
    Task *all_tasks = malloc(count * sizeof(Task));

    fseek(f, 0, SEEK_SET);
    fread(all_tasks, sizeof(Task), count, f);
    
    int done_tasks = 0;
    for (int i = 0; i < count; i++) {
      if (all_tasks[i].status == DONE) {
        done_tasks += 1;
      }
    }

    printf("Total tasks %d, and done %d\n", count, done_tasks);

    fclose(f);
    free(all_tasks);
  } else {
    printf("Incorrect command, supported commands: add\n");
  }

  return 0;
}