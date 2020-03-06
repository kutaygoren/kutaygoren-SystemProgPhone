#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data
{
    int id;
    char name[50];
    long int number;
    char department[200];
};

#define BUFFER_SIZE 120

struct data saveToStruct (char* str)
{
    struct data res;
    int flag = 0;
    char *token = strtok(str, ",");

    while( token != NULL )
    {
        if (0 == flag)
            res.id = atoi(token);
        else if (1 == flag)
            strcpy(res.name, token);
        else if (2 == flag)
            res.number = atol(token);
        else
            strcpy(res.department, token);
        flag++;
        token = strtok( NULL, "," );
    }
    return res;
}

void print(struct data* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("ID: %d, Ad Soyad: %s, Numara: %ld, Departman: %s\n", arr[i].id, arr[i].name, arr[i].number, arr[i].department);
    }
}
