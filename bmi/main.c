#include <stdio.h>
#include <math.h>

const float calculate_bmi (float *w, float *h) {
  return *w / (pow(*h / 100.0, 2));
}

int main () {
  int count = 0;

  while (count <= 0) {
    printf("How many people you have in your team?\n");
    scanf("%d", &count);

    if (count <= 0) {
      printf("%d is incorrect number, write more then 1 and not negative number\n", count);
    }
  }


  for (int i = 0; i < count; i++) {
    float weight;
    float height;

    printf("#%d User ---------------------\n", i + 1);

    printf("Enter your height (sm) and weight (kg) with space:\n");
    scanf("%f %f", &height, &weight);
      
    float bmi = calculate_bmi(&weight, &height);


    if (bmi < 18.5) {
      printf("You are underweight, with BMI:%0.2f\n", bmi);
    } else if (bmi >= 18.5 && bmi <= 24.9) {
      printf("Normal weight, with BMI:%0.2f\n", bmi);
    } else if (bmi >= 25.0 && bmi <= 29.9) {
      printf("Overweight, with BMI:%0.2f\n", bmi);
    } else {
      printf("Obesity with BMI:%0.2f\n", bmi);
    }
  }
  
  printf("---------------------------------\n");
  printf("Thank for using the app!\n");

  return 0;
}