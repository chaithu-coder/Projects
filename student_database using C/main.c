#include "header.h"
int r = 1;
int df = 0;
void main()
{
    std *head = NULL;
    char choice;
    while (1)
    {
        printf("\n******* STUDENT RECORD MENU *******\n");
        printf("\n a/A  :add new record\n d/D  :delete a record\n s/S  :show the list\n m/M  :modify a record\n v/V  :save\n e/E  :exit\n t/T  :sort the list\n l/L  :delete all the records\n r/R  :reverse the list\n Y/y  :read_file data\n");

        printf("enter a choice\n");
        scanf(" %c", &choice);
        if (choice >= 'A' && choice <= 'Z')
            choice = choice + 32;
        switch (choice)
        {
        case 'a':
            stud_add(&head);
            break;
        case 's':
            stud_show(head);
            break;
        case 'd':
            stud_del(&head);
            break;
        case 'v':
            save_file(head);
            break;

        case 'l':
            del_all(&head);
            break;
        case 'r':
            rev_list(&head);
            break;
        case 'y':
            read_file(&head);
            break;
        case 't':
            sort_data(head);
            break;
        case 'm':
            stud_modi(head);
            break;
        case 'e':
            exit_1(head);
            break;
        default:
            printf("unknown choice");
        }
    }
}

/**************************** stud_add ************************/

void stud_add(std **ptr)
{
    std *new, *last, *prev;
    new = malloc(sizeof(std));
    int i, j, c = count_node(*ptr), r = 0;
    i = 0;
    j = c;

    std *d;
    for (i = 1; i <= j + 1; i++)
    {
        d = *ptr;
        df = 0;
        while (d)
        {
            if (d->rollno == i)
            {
                df = 1;
                break;
            }
            d = d->next;
        }
        if (df == 0)
        {
            r = i;

            break;
        }
    }
    if (r != 0)
    {
        j = r;
    }

    else
    {
        j = r + 1;
    }
    new->rollno = j;

    printf("enter  name and marks respectivly\n");
    scanf("%s%f", new->name, &new->marks);
    if ((*ptr == 0) || (new->rollno < (*ptr)->rollno))
    {
        new->next = *ptr;
        *ptr = new;
        
    }
    else
    {
        last = *ptr;
        while ((last->next != 0) && (new->rollno) > (last->next->rollno))
        {
            // prev=last;
            last = last->next;
            
        }
        // new->next=prev->next;
        // prev->next=new;
        new->next = last->next;
        last->next = new;
    }
}

/*
void stud_add(std **ptr)
{
    std *new, *last;
    int c = 0;
    new = malloc(sizeof(std));
    printf("Enter student name and marks \n");
    scanf("%s %f", new->name, &new->marks);

    new->next = 0;
    if (*ptr == 0)
    {
        new->rollno = ++c;
        *ptr = new;
    }
    else
    {
        c = count_node(*ptr);
        last = *ptr;
        while (last->next)
            last = last->next;
        new->rollno = ++c;
        last->next = new;
    }
}
*/
/**************************** stud_show ************************/
void stud_show(std *ptr)
{

    if (ptr == 0)
    {
        printf("no records found\n");
        return;
    }
    while (ptr)
    {
        printf("%d %s %f\n", ptr->rollno, ptr->name, ptr->marks);
        ptr = ptr->next;
    }
}

/**************************** save_file ************************/
void save_file(std *ptr)
{
    if (ptr == 0)
    {
        printf("no records found\n");
        return;
    }
    FILE *fp;
    fp = fopen("student.txt", "w");
    while (ptr)
    {
        fprintf(fp, "%d %s %.3f\n", ptr->rollno, ptr->name, ptr->marks);
        ptr = ptr->next;
    }
    printf("data saved in file\n");
    fclose(fp);
}

/**************************** read_file ************************/
void read_file(std **ptr)
{
    // system("clear");
    std *new, *last;
    FILE *fp;
    fp = fopen("student.txt", "r");
    if (fp == 0)
    {
        printf("file not found\n");
        return;
    }
    while (1)
    {
        new = malloc(sizeof(std));
        if (fscanf(fp, "%d %s %f", &new->rollno, new->name, &new->marks) == -1)
            break;
        new->next = 0;
        if (*ptr == 0)
            *ptr = new;
        else
        {
            last = *ptr;
            while (last->next)
                last = last->next;
            last->next = new;
        }
    }
}

/**************************** stud_modi ************************/
void stud_modi(std *head1)
{
    std *ptr = head1;
    char op, name[50], mname[50];
    int num, rollno, r, flag = 0;
    float marks, nmarks;
    printf("enter which record to search fo modification\n R/r :to search a rollno\n N/n :to search a name\n P/p :percentage based\n");
    scanf(" %c", &op);
    if (op >= 'A' && op <= 'Z')
        op = op + 32;
    if (op == 'r')
    {
        printf("enter a rollno to search\n");
        scanf(" %d", &num);
        if (ptr == 0)
        {
            printf("no records found\n");
            return;
        }
        int flag = 0;

        while (ptr)
        {
            if (ptr->rollno == num)
            {
                printf("enter new rollno without repeating previous rollno's\n");
                scanf("%d", &rollno);
                flag = 1;
                ptr->rollno = rollno;
            }
            ptr = ptr->next;
        }
        if (flag == 0)
            printf("name not found\n");
    }

    else if (op == 'n')
    {
        int c = 0;
        printf("enter a name to search\n");
        scanf("%s", name);
        if (ptr == 0)
        {
            printf("no records found\n");
            return;
        }

        while (ptr)
        {
            if (strcmp(name, ptr->name) == 0)
            {
                c++;
                if (c >= 1)
                {
                    printf("%d %s %f\n", ptr->rollno, ptr->name, ptr->marks);
                }
                flag = 1;
            }
            ptr = ptr->next;
        }
        if (flag == 0)
            printf("name not found\n");
        if (c == 1)
        {
            ptr = head1;

            while (ptr)
            {
                if (strcmp(name, ptr->name) == 0)
                {
                    printf("enter a new name ");
                    scanf("%s", mname);
                    strcpy(ptr->name, mname);
                    break;
                }
                ptr = ptr->next;
            }
        }
        else if (c >= 1)
        {
            ptr = head1;

            printf("enter rollno to choose student\n");
            scanf("%d", &r);
            while (ptr)
            {
                if (ptr->rollno == r)
                {
                    printf("enter a new name ");
                    scanf("%s", mname);
                    strcpy(ptr->name, mname);
                }
                ptr = ptr->next;
            }
        }
    }

    else if (op == 'p')
    {
        int c = 0;
        printf("enter a marks to search\n");
        scanf("%f", &marks);
        if (ptr == 0)
        {
            printf("no records found\n");
            return;
        }
        int flag = 0;
        while (ptr)
        {
            if (ptr->marks == marks)
            {
                c++;
                if (c >= 1)
                {
                    printf("%d %s %f\n", ptr->rollno, ptr->name, ptr->marks);
                }
                flag = 1;
            }
            ptr = ptr->next;
        }
        if (flag == 0)
            printf("name not found\n");

        if (c == 1)
        {
            ptr = head1;

            while (ptr)
            {
                if (ptr->marks == marks)
                {
                    printf("enter a new marks ");
                    scanf("%f", &nmarks);
                    ptr->marks = nmarks;
                    break;
                }
                ptr = ptr->next;
            }
        }
        else if (c > 1)
        {
            ptr = head1;

            printf("enter rollno to choose student\n");
            scanf("%d", &r);
            while (ptr)
            {
                if (ptr->rollno == r)
                {
                    printf("enter a new marks ");
                    scanf("%f", &nmarks);
                    ptr->marks = nmarks;
                }
                ptr = ptr->next;
            }
        }
    }
}

/**************************** sort_data ************************/
void sort_data(std *ptr)
{
    int op;

    printf("enter choice\n 1)name based \n 2)marks based\n");
    scanf("%d", &op);
    if (op == 1)
    {
        if (ptr == 0)
        {
            printf("no records found\n");
            return;
        }
        int i, j, c = count_node(ptr);
        std *p1, *p2, t;
        p1 = p2 = ptr;
        for (i = 0; i < c - 1; i++)
        {
            p2 = p1->next;
            for (j = 0; j < c - i - 1; j++)
            {
                if (strcmp(p1->name, p2->name) > 0)
                {
                    t.rollno = p1->rollno;
                    strcpy(t.name, p1->name);
                    t.marks = p1->marks;

                    p1->rollno = p2->rollno;
                    strcpy(p1->name, p2->name);
                    p1->marks = p2->marks;

                    p2->rollno = t.rollno;
                    strcpy(p2->name, t.name);
                    p2->marks = t.marks;
                }
                p2 = p2->next;
            }
            p1 = p1->next;
        }
    }
    if (op == 2)
    {
        if (ptr == 0)
        {
            printf("no records found\n");
            return;
        }
        int i, j, c = count_node(ptr);
        std *p1, *p2, t;
        p1 = p2 = ptr;
        for (i = 0; i < c - 1; i++)
        {
            p2 = p1->next;
            for (j = 0; j < c - i - 1; j++)
            {
                if (p1->marks > p2->marks)
                {
                    t.rollno = p1->rollno;
                    strcpy(t.name, p1->name);
                    t.marks = p1->marks;

                    p1->rollno = p2->rollno;
                    strcpy(p1->name, p2->name);
                    p1->marks = p2->marks;

                    p2->rollno = t.rollno;
                    strcpy(p2->name, t.name);
                    p2->marks = t.marks;
                }
                p2 = p2->next;
            }
            p1 = p1->next;
        }
    }
}

/**************************** stud_del ************************/
void stud_del(std **ptr)
{
    std *del = *ptr;
    char op;
    int n;
    printf("enter a oprtion to delite student data\n R/r->rollno based\n N/n->name based\n");
    scanf(" %c", &op);
    if (op >= 'A' && op <= 'Z')
        op = op + 32;
    // roll number based
    if (op == 'r')
    {

        if (*ptr == 0)
        {
            printf("no records found\n");
            return;
        }
        int num;
        printf("enter a roll no to delite\n");
        scanf("%d", &num);
        std *del, *prev;
        del = *ptr;
        while (del)
        {
            if (del->rollno == num)
            {
                if (*ptr == del)
                    *ptr = del->next;
                else
                    prev->next = del->next;
                df = 1;
                free(del);
                return;
            }
            prev = del;
            del = del->next;
        }
        printf("rollno data delited suuccessfully\n");
    }

    // based on name
    else if (op == 'n')
    {
        if (*ptr == 0)
        {
            printf("no records found\n");
            return;
        }
        char name[50];
        int count = 0;
        printf("enter a name to delite\n");
        scanf("%s", name);
        std *del, *prev;
        del = *ptr;
        while (del)
        {
            if (strcmp(name, del->name) == 0)
            {
                count++;

                if (count >= 1)
                {
                    printf("%d %s %f\n", del->rollno, del->name, del->marks);
                }
            }
            del = del->next;
        }
        if (count == 1)
        {
            del = *ptr;
            while (del)
            {
                if (strcmp(name, del->name) == 0)
                {
                    if (*ptr == del)
                        *ptr = del->next;
                    else
                        prev->next = del->next;
                    free(del);
                    return;
                }
                prev = del;
                del = del->next;
            }
        }
        else if (count > 1)
        {
            int num;
            printf("enter a roll no to delete\n");
            scanf("%d", &num);
            std *prev;
            del = *ptr;
            while (del)
            {
                if (del->rollno == num)
                {
                    if (*ptr == del)
                        *ptr = del->next;
                    else
                        prev->next = del->next;
                    free(del);
                    return;
                }
                prev = del;
                del = del->next;
            }
        }
        else
            printf("invalid option\n");
    }
}

/**************************** exit_1 ************************/
void exit_1(std *ptr)
{
    int op;
    printf("enter option\n 1)save and exit\n 2)exit without saving\n ");
    scanf("%d", &op);
    if (op == 1)
    {
        save_file(ptr);
        exit(0);
    }
    else if (op == 2)
    {
        exit(0);
    }
    else
        printf("wrong option\n");
}

/**************************** del_all ************************/
void del_all(std **ptr)
{
    int c = count_node(*ptr);
    if (*ptr == 0)
    {
        printf("no records found\n");
        return;
    }
    std *del;
    del = *ptr;
    while (del)
    {
        *ptr = del->next;
        free(del);
        del = *ptr;
    }
    printf("all %d records are deleted\n", c);
}

/**************************** rev_list ************************/
void rev_list(std **ptr)
{
    if (*ptr == 0)
    {
        printf("no records found\n");
        return;
    }
    int i = 0, c = count_node(*ptr);
    std **p, *t;
    if (c > 1)
    {
        p = malloc(sizeof(std *) * c);
        t = *ptr;
        while (t)
        {
            p[i++] = t;
            t = t->next;
        }
        for (i = 1; i < c; i++)
            p[i]->next = p[i - 1];
        p[0]->next = 0;
        *ptr = p[c - 1];
    }
}
/**************************** count nodes ************************/

int count_node(std *ptr)
{
    int c = 0;
    while (ptr)
    {
        c++;
        ptr = ptr->next;
    }
    return c;
}
