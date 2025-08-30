#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'roadsAndLibraries' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER c_lib
 *  3. INTEGER c_road
 *  4. 2D_INTEGER_ARRAY cities
 */

long roadsAndLibraries(int n, int c_lib, int c_road, int cities_rows, int cities_columns, int** cities) {
    if (c_lib <= c_road) {
        return (long)c_lib * n;
    }

    int** adj = calloc(n + 1, sizeof(int*));
    int* adj_size = calloc(n + 1, sizeof(int));
    int* adj_capacity = calloc(n + 1, sizeof(int));

    for (int i = 0; i < cities_rows; i++) {
        int u = cities[i][0];
        int v = cities[i][1];

        if (adj_capacity[u] == 0) {
            adj_capacity[u] = 2;
            adj[u] = malloc(adj_capacity[u] * sizeof(int));
        } else if (adj_size[u] == adj_capacity[u]) {
            adj_capacity[u] *= 2;
            adj[u] = realloc(adj[u], adj_capacity[u] * sizeof(int));
        }
        adj[u][adj_size[u]++] = v;

        if (adj_capacity[v] == 0) {
            adj_capacity[v] = 2;
            adj[v] = malloc(adj_capacity[v] * sizeof(int));
        } else if (adj_size[v] == adj_capacity[v]) {
            adj_capacity[v] *= 2;
            adj[v] = realloc(adj[v], adj_capacity[v] * sizeof(int));
        }
        adj[v][adj_size[v]++] = u;
    }


    int* visited = calloc(n + 1, sizeof(int));
    long total_cost = 0;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            int* stack = malloc(n * sizeof(int));
            int top = 0;
            stack[top++] = i;
            visited[i] = 1;
            int component_size = 1;

            while (top > 0) {
                int node = stack[--top];
                for (int j = 0; j < adj_size[node]; j++) {
                    int neighbor = adj[node][j];
                    if (!visited[neighbor]) {
                        visited[neighbor] = 1;
                        stack[top++] = neighbor;
                        component_size++;
                    }
                }
            }

            free(stack);
            total_cost += c_lib + (component_size - 1) * c_road;
        }
    }

    for (int i = 0; i <= n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adj_size);
    free(adj_capacity);
    free(visited);

    return total_cost;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int m = parse_int(*(first_multiple_input + 1));

        int c_lib = parse_int(*(first_multiple_input + 2));

        int c_road = parse_int(*(first_multiple_input + 3));

        int** cities = malloc(m * sizeof(int*));

        for (int i = 0; i < m; i++) {
            *(cities + i) = malloc(2 * (sizeof(int)));

            char** cities_item_temp = split_string(rtrim(readline()));

            for (int j = 0; j < 2; j++) {
                int cities_item = parse_int(*(cities_item_temp + j));

                *(*(cities + i) + j) = cities_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, m, 2, cities);

        fprintf(fptr, "%ld\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
