#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef  struct st
{
    int rollno;
    char name[100];
    float marks;
    struct st *next;
}std;

void stud_add(std **);
int count_node(std *);
void stud_show(std *);
void stud_del(std **);
void del_all(std **);
void rev_list(std **);
void read_file(std **);
void save_file(std *);
void exit_1(std *);
void sort_data(std *);
void stud_modi(std *);