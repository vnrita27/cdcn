#include <stdio.h>
#include <string.h>

int main() {
    char A, s[50], p[10][50];
    int n = 0, i = 0, j = 0;

    printf("Enter production: ");
    scanf("%c->%s", &A, s);

    for (int k = 0; s[k] != '\0'; k++) {
        if (s[k] == '|') {
            p[n][j] = '\0';
            n++; j = 0;
        } else {
            p[n][j++] = s[k];
        }
    }
    p[n][j] = '\0';
    n++;

    int left = 0;
    for (i = 0; i < n; i++)
        if (p[i][0] == A) left = 1;

    if (!left) {
        printf("No Left Recursion\n");
        return 0;
    }

    printf("After eliminating Left Recursion:\n");

    printf("%c->", A);
    for (i = 0; i < n; i++)
        if (p[i][0] != A)
            printf("%s%c'|", p[i], A);

    printf("\n%c'->", A);
    for (i = 0; i < n; i++)
        if (p[i][0] == A)
            printf("%s%c'|", p[i] + 1, A);

    printf("ε\n");
}
