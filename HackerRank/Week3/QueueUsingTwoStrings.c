#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
     int q;
    scanf("%d", &q);

    int stack1[100000], top1 = -1;
    int stack2[100000], top2 = -1;

    while (q--) {
        int type, x;
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d", &x);
            stack1[++top1] = x;
        } else if (type == 2) {
            if (top2 == -1) {
                while (top1 != -1) {
                    stack2[++top2] = stack1[top1--];
                }
            }
            if (top2 != -1) top2--; // dequeue
        } else if (type == 3) {
            if (top2 == -1) {
                while (top1 != -1) {
                    stack2[++top2] = stack1[top1--];
                }
            }
            if (top2 != -1) printf("%d\n", stack2[top2]);
        }
    }
    return 0;
}
