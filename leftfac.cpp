#include <stdio.h>
#include <string.h>

int main() {
    char A, s[50], p[10][50];
    int n = 0, i, j = 0;

    printf("Enter production: ");
    scanf("%c->%s", &A, s);

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '|') {
            p[n][j] = '\0';
            n++; 
            j = 0;
        } else {
            p[n][j++] = s[i];
        }
    }
    p[n][j] = '\0';
    n++;

    int k = 0;
    while (p[0][k] != '\0') {
        for (i = 1; i < n; i++) {
            if (p[i][k] != p[0][k])
                break;
        }
        if (i == n)
            k++;
        else
            break;
    }

    if (k == 0) {
        printf("No Left Factoring Needed\n");
        return 0;
    }

    printf("After Left Factoring:\n");

    printf("%c->", A);
    for (i = 0; i < k; i++)
        printf("%c", p[0][i]);
    printf("%c'\n", A);

    printf("%c'->", A);
    for (i = 0; i < n; i++) {
        if (p[i][k] == '\0')
            printf("ε|");
        else
            printf("%s|", p[i] + k);
    }
    printf("\n");

    return 0;
}
