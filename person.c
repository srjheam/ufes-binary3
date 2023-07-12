#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "person.h"

Person *person_construct(char name[19], int age, float height) {
    Person *person = malloc(sizeof(Person));
    strcpy(person->name, name);
    person->age = age;
    person->height = height;
    return person;
}

void person_print(Person *person) {
    printf("%s %d %.2f", person->name, person->age, person->height);
}

void person_destruct(void *person) {
    free(person);
}
