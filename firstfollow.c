#include <stdio.h>
#include <string.h>
#define MAX 50

char prod[MAX][MAX], nt[20];
int n, nnt = 0;
int FIRST[20][128], FOLLOW[20][128];

int idx(char c){
    for(int i=0;i<nnt;i++) if(nt[i]==c) return i;
    nt[nnt++] = c;
    return nnt-1;
}

int isNT(char c){
    return (c >= 'A' && c <= 'Z');
}

void split(char *r, char p[][MAX], int *c){
    int j = 0; *c = 0;
    for(int i=0;r[i];i++){
        if(r[i]=='|'){
            p[*c][j] = 0;
            (*c)++; j = 0;
        } else {
            p[*c][j++] = r[i];
        }
    }
    p[*c][j] = 0;
    (*c)++;
}

int main(){
    printf("Enter no. of productions: ");
    scanf("%d%*c", &n);

    for(int i=0;i<n;i++){
        fgets(prod[i], MAX, stdin);
        prod[i][strcspn(prod[i], "\n")] = 0;

        char t[MAX];
        int k = 0;

        for(int j=0; prod[i][j]; j++)
            if(prod[i][j] != ' ')
                t[k++] = prod[i][j];

        t[k] = 0;
        strcpy(prod[i], t);

        idx(prod[i][0]);  // collect non-terminals
    }

    // ---------------- FIRST -----------------
    int changed = 1;
    while(changed){
        changed = 0;

        for(int i=0;i<n;i++){
            char A = prod[i][0];
            int Aidx = idx(A);

            char rhsParts[20][MAX];
            int c = 0;
            split(strstr(prod[i], "->") + 2, rhsParts, &c);

            for(int p=0;p<c;p++){
                char *alpha = rhsParts[p];
                int pos = 0, nullable = 1;

                while(alpha[pos] && nullable){
                    char X = alpha[pos];
                    nullable = 0;

                    if(isNT(X)){
                        int Xi = idx(X);
                        for(int t=0;t<128;t++){
                            if(FIRST[Xi][t] && t!='#' && !FIRST[Aidx][t]){
                                FIRST[Aidx][t] = 1;
                                changed = 1;
                            }
                        }
                        if(FIRST[Xi]['#']){ nullable = 1; pos++; }
                    } else {
                        if(!FIRST[Aidx][(int)X]){
                            FIRST[Aidx][(int)X] = 1;
                            changed = 1;
                        }
                    }
                }

                if(nullable){
                    if(!FIRST[Aidx]['#']){
                        FIRST[Aidx]['#'] = 1;
                        changed = 1;
                    }
                }
            }
        }
    }

    // ---------------- FOLLOW -----------------
    FOLLOW[idx(prod[0][0])]['$'] = 1;

    changed = 1;
    while(changed){
        changed = 0;

        for(int i=0;i<n;i++){
            char A = prod[i][0];
            int Aidx = idx(A);

            char rhsParts[20][MAX];
            int c = 0;
            split(strstr(prod[i], "->") + 2, rhsParts, &c);

            for(int p=0;p<c;p++){
                char *alpha = rhsParts[p];
                int len = strlen(alpha);

                for(int j=0;j<len;j++){
                    char B = alpha[j];
                    if(!isNT(B)) continue;

                    int Bi = idx(B);
                    int k = j+1;
                    int nullable = 1;

                    while(k < len && nullable){
                        char X = alpha[k];
                        nullable = 0;

                        if(isNT(X)){
                            int Xi = idx(X);
                            for(int t=0;t<128;t++){
                                if(FIRST[Xi][t] && t!='#' && !FOLLOW[Bi][t]){
                                    FOLLOW[Bi][t] = 1;
                                    changed = 1;
                                }
                            }
                            if(FIRST[Xi]['#']){ nullable = 1; k++; }
                        } else {
                            if(!FOLLOW[Bi][(int)X]){
                                FOLLOW[Bi][(int)X] = 1;
                                changed = 1;
                            }
                        }
                    }

                    if(nullable){
                        for(int t=0;t<128;t++){
                            if(FOLLOW[Aidx][t] && !FOLLOW[Bi][t]){
                                FOLLOW[Bi][t] = 1;
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    // -------- Print FIRST ----------
    printf("\nFIRST sets:\n");
    for(int i=0;i<nnt;i++){
        printf("FIRST(%c)={", nt[i]);
        int f = 0;
        for(int t=0;t<128;t++){
            if(FIRST[i][t]){
                if(f) printf(",");
                f = 1;
                if(t=='#') printf("ε");
                else printf("%c", t);
            }
        }
        printf("}\n");
    }

    // -------- Print FOLLOW ----------
    printf("\nFOLLOW sets:\n");
    for(int i=0;i<nnt;i++){
        printf("FOLLOW(%c)={", nt[i]);
        int f = 0;
        for(int t=0;t<128;t++){
            if(FOLLOW[i][t]){
                if(f) printf(",");
                f = 1;
                if(t=='$') printf("$");
                else printf("%c", t);
            }
        }
        printf("}\n");
    }
}
