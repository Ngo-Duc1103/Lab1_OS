#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>


void calculator() {
    double ans = 0, a, b, res;
    char op;

    char input[100];
    char str_num1[50];
    char str_num2[50];
    char str_res[100];

    FILE *file;
    char filename[] = "ans.txt";
    file = fopen(filename, "r");
    if (file) {
        fscanf(file, "%s", input);
        ans = strtod(input, NULL);
        fclose(file);
    }
    file = fopen(filename, "w");
    while (1) {
        printf(">> ");
        fgets(input, 100, stdin);
        sscanf(input, "%s %c %s", str_num1, &op, str_num2);

        if (!strcmp(input, "EXIT\n")) break;

        if (!strcmp(str_num1, "ANS")) a = ans;
        else a = strtod(str_num1, NULL);
        if (!strcmp(str_num2, "ANS")) b = ans;
        else b = strtod(str_num2, NULL);

        if ((op != '+') && (op != '-') && (op != '*') && (op != '/') && (op != '%')) {
            printf("SYNTAX ERROR\n");
	    getchar();
            continue;
        }

        if ( b == 0 && ( (op == '/') ||  (op == '%') ) ) {
            printf("MATH ERROR\n");
            getchar();
	    continue;
        }

        switch (op) {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
                break;
            case '/':
                res = a / b;
                break;
            case '%':
                res = (int) (a / b);
                break;
        }

        if (fmod(res, 1.0) == 0) sprintf(str_res, "%.0lf", res);
        else sprintf(str_res, "%.2lf", res);

        ans = res;
        printf("%s\n", str_res);
	getchar();
    }

    if (file) {
        fprintf(file, "%.04lf", ans);
        fclose(file);
    }
}
