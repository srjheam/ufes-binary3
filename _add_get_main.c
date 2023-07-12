#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

#include "binary_tree.h"

int *intdup(int n) {
    int *p = malloc(sizeof(int));
    *p = n;
    return p;
}

int cmp(void *a, void *b) { return *(int *)a - *(int *)b; }

int main() {
    int n;
    scanf("%d", &n);

    BinaryTree *b3 = binary_tree_construct(cmp, free, person_destruct);

    while (n--) {
        char op[4];
        scanf("%s", op);

        if (op[0] == 'G' || op[0] == 'g') {
            int cpf;
            scanf("%d", &cpf);

            Person *p = binary_tree_get(b3, &cpf);

            person_print(p);
            printf("\n");
        } else if (op[0] == 'S' || op[0] == 's') {
            int cpf; // https://twitter.com/errologista/status/1677058877353873409?s=20
            char name[19];
            int age;
            float h;
            scanf("%d %s %d %f", &cpf, name, &age, &h);

            binary_tree_add(b3, intdup(cpf), person_construct(name, age, h));
        } else {
            fprintf(stderr, "Invalid operation: %4s\n", op);
            exit(EXIT_FAILURE);
        }
    }

    binary_tree_destroy(b3);

    return EXIT_SUCCESS;
}
