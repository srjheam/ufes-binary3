#ifndef _PERSON_H_
#define _PERSON_H_

typedef struct
{
    char name[19];
    int age;
    float height;
} Person;

Person *person_construct(char name[19], int age, float height);

void person_print(Person *person);

void person_destruct(void *person);

#endif
