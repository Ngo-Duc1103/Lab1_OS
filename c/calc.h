#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>


void calculator() {
    double ans = 0, num1, num2, res;
    char operator;

    char input[100];
    char str_num1[50];
    char str_num2[50];
    char str_res[100];

    char *eptr;
    FILE *fp;
    char filename[] = "ans.txt";
    fp = fopen(filename, "r");
    if (fp) {
        fscanf(fp, "%s", input);
        ans = strtod(input, &eptr);
        fclose(fp);
    }
    fp = fopen(filename, "w");
    while (1) {
        system("clear");
        printf(">> ");
        fgets(input, 100, stdin);
        sscanf(input, "%s %c %s", str_num1, &operator, str_num2);

        if (!strcmp(input, "EXIT\n")) {
            break;
        }

        if (!strcmp(str_num1, "ANS")) {
            num1 = ans;
        }
        else {
            num1 = strtod(str_num1, &eptr);
            if (num1 == 0.0 && strcmp(str_num1, "0") && strcmp(str_num1, "0.0")) {
                printf("SYNTAX ERROR\n");
                getchar();
                continue;
            }
        }
        if (!strcmp(str_num2, "ANS")) {
            num2 = ans;
        }
        else {
            num2 = strtod(str_num2, &eptr);
            if (num2 == 0.0 && strcmp(str_num2, "0") && strcmp(str_num2, "0.0")) {
                printf("SYNTAX ERROR\n");
                getchar();
                continue;
            }
        }

        if ((operator != '+') && (operator != '-') && (operator != '*') && (operator != '/') && (operator != '%')) {
            printf("SYNTAX ERROR\n");
            getchar();
            continue;
        }

        if (((num2 == 0) && (operator == '/')) || ((num2 == 0) && (operator == '%'))) {
            printf("MATH ERROR\n");
            getchar();
            continue;
        }

        switch (operator) {
            case '+':
                res = num1 + num2;
                break;
            case '-':
                res = num1 - num2;
                break;
            case '*':
                res = num1 * num2;
                break;
            case '/':
                res = num1 / num2;
                break;
            case '%':
                res = (int) (num1 / num2);
                break;
        }

        if (fmod(res, 1.0) == 0) {  
            sprintf(str_res, "%.0lf", res);
        }
        else {
            sprintf(str_res, "%.2lf", res);
        }

        ans = res;
        printf("%s\n", str_res);
        getchar();
    }

    if (fp) {
        fprintf(fp, "%.04lf", ans);
        fclose(fp);
    }
}
