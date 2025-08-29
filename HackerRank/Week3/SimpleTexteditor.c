#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX_LEN 1000000

char *stack[1000000];
int top = -1;

void push(char *s){ 
    stack[++top] = strdup(s); 
    }
char* pop(){ 
    return (top >= 0) ? stack[top--] : ""; 
    }
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int Q; scanf("%d", &Q);
    char S[MAX_LEN + 1] = "";
    push(S);

    for (int i = 0; i < Q; i++) {
        int type; scanf("%d", &type);
        if (type == 1) {
            char W[1000001]; scanf("%s", W);
            strcat(S, W);
            push(S);
        } else if (type == 2) {
            int k; scanf("%d", &k);
            int len = (int)strlen(S);
            S[len - k] = '\0';
            push(S);
        } else if (type == 3) {
            int k; scanf("%d", &k);
            printf("%c\n", S[k - 1]);
        } else if (type == 4) {
            free(pop());
            strcpy(S, stack[top]);
        }
    }

    return 0;
}