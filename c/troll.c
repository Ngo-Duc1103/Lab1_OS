#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_HISTORY_SIZE 5
#define MAX_INPUT_SIZE 50

int main() {
    char hist[MAX_HISTORY_SIZE][MAX_INPUT_SIZE];
    char input[MAX_INPUT_SIZE];
    char *num1, *num2, *operator;
    double store = 0;
    int hist_index = 0;

    printf(">> ");
    fgets(input, MAX_INPUT_SIZE, stdin);
    input[strcspn(input, "\n")] = 0; // remove newline character

    while (strcmp(input, "EXIT") != 0) {

        if (strcmp(input, "HIST") == 0) {
            for (int i = 0; i < hist_index; i++) {
                printf("%s\n", hist[i]);
            }
        } 
        else {
            num1 = strtok(input, " ");
            operator = strtok(NULL, " ");
            num2 = strtok(NULL, " ");

            if (num1 == NULL || num2 == NULL || operator == NULL) {
                printf("SYNTAX ERROR\n");
            }
            else if ((sscanf(num1, "%lf", &store) != 1 && strcmp(num1, "ANS") != 0) || 
                    (sscanf(num2, "%lf", &store) != 1 && strcmp(num2, "ANS") != 0) || 
                    (strcmp(operator, "+") != 0 && strcmp(operator, "-") != 0 && 
                     strcmp(operator, "*") != 0 && strcmp(operator, "/") != 0 && 
                     strcmp(operator, "%") != 0)) {
                printf("SYNTAX ERROR\n");
            }
            else if ((strcmp(operator, "/") == 0 || strcmp(operator, "%") == 0) && 
                     atof(num2) == 0) {
                printf("MATH ERROR\n");
            }
            else {
                double n1 = (strcmp(num1, "ANS") == 0) ? store : atof(num1);
                double n2 = (strcmp(num2, "ANS") == 0) ? store : atof(num2);
                double result = 0;

                switch (operator[0]) {
                    case '+':
                        result = n1 + n2;
                        break;
                    case '-':
                        result = n1 - n2;
                        break;
                    case '*':
                        result = n1 * n2;
                        break;
                    case '/':
                        result = n1 / n2;
                        break;
                    case '%':
                        result = fmod(n1, n2);
                        break;
                }

                store = result;

                if (isnan(store) || isinf(store)) {
                    printf("MATH ERROR\n");
                } 
                else {
                    sprintf(hist[hist_index], "%s %s %s = %.2lf", num1, operator, num2, result);
                    hist_index = (hist_index + 1) % MAX_HISTORY_SIZE;

                    printf("%.2lf\n", store);
                }
            }
        }

        printf(">> ");
        fgets(input, MAX_INPUT_SIZE, stdin);
        input[strcspn(input, "\n")] = 0;
    }

    return 0;
}

