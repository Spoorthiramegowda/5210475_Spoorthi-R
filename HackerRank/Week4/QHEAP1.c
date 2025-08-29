#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000
#define MOD 1000000007

int heap[MAX+5];
int heapSize = 0;

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void heapify_up(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent] > heap[idx]) {
            swap(&heap[parent], &heap[idx]);
            idx = parent;
        } else break;
    }
}

void heapify_down(int idx) {
    while (1) {
        int left = 2*idx + 1;
        int right = 2*idx + 2;
        int smallest = idx;
        if (left < heapSize && heap[left] < heap[smallest]) smallest = left;
        if (right < heapSize && heap[right] < heap[smallest]) smallest = right;
        if (smallest != idx) {
            swap(&heap[idx], &heap[smallest]);
            idx = smallest;
        } else break;
    }
}

void insert(int val) {
    heap[heapSize] = val;
    heapify_up(heapSize);
    heapSize++;
}

#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define HASH_SIZE 200003

typedef struct Node {
    int val;
    int count;
    struct Node* next;
} Node;

Node* hashTable[HASH_SIZE];

unsigned int hash(int x) {
    return ((unsigned int)(x % HASH_SIZE) + HASH_SIZE) % HASH_SIZE;
}

void add_to_delete(int val) {
    unsigned int h = hash(val);
    Node* cur = hashTable[h];
    while (cur) {
        if (cur->val == val) {
            cur->count++;
            return;
        }
        cur = cur->next;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->count = 1;
    newNode->next = hashTable[h];
    hashTable[h] = newNode;
}

int check_delete(int val) {
    unsigned int h = hash(val);
    Node* cur = hashTable[h];
    while (cur) {
        if (cur->val == val) return cur->count;
        cur = cur->next;
    }
    return 0;
}

void remove_from_delete(int val) {
    unsigned int h = hash(val);
    Node* cur = hashTable[h];
    while (cur) {
        if (cur->val == val) {
            cur->count--;
            return;
        }
        cur = cur->next;
    }
}

int getMin() {
    while (heapSize > 0 && check_delete(heap[0]) > 0) {
        remove_from_delete(heap[0]);
        heap[0] = heap[heapSize-1];
        heapSize--;
        heapify_down(0);
    }
    return heap[0];
}

int main() {
    int Q;
    scanf("%d", &Q);

    for (int i=0; i<Q; i++) {
        int type, v;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d", &v);
            insert(v);
        } else if (type == 2) {
            scanf("%d", &v);
            add_to_delete(v);
        } else if (type == 3) {
            printf("%d\n", getMin());
        }
    }
    return 0;
}