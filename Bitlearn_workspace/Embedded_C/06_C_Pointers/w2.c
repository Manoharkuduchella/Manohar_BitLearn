#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 1. Pointer Declaration and Initialization */
void EC_CP_W2_1()
{
    int a = 10;
    float b = 5.5;
    char c = 'A';

    int *p1 = &a;
    float *p2 = &b;
    char *p3 = &c;

    printf("%d %.2f %c\n", *p1, *p2, *p3);

    int *dyn = (int*)malloc(sizeof(int));
    *dyn = 20;
    printf("%d\n", *dyn);

    dyn++;
    dyn--; // pointer arithmetic

    free(dyn);
}

/* 2. Array and Pointer Arithmetic */
void EC_CP_W2_2()
{
    int arr[] = {1,2,3,4,5};
    int *p = arr;
    int sum = 0;

    for(int i=0;i<5;i++)
    {
        sum += *(p+i);
    }
    printf("Sum = %d\n", sum);
}

/* 3. Double Pointer */
void EC_CP_W2_3()
{
    int *p;
    int **dp;

    p = (int*)malloc(sizeof(int));
    dp = &p;

    **dp = 50;
    printf("%d\n", **dp);

    free(p);
}

/* 4. Pointer and Function */
void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void EC_CP_W2_4()
{
    int x=5,y=10;
    swap(&x,&y);
    printf("x=%d y=%d\n",x,y);
}

/* 5. Dynamic Memory Allocation */
void EC_CP_W2_5()
{
    int *p = (int*)malloc(3*sizeof(int));

    for(int i=0;i<3;i++)
        p[i]=i+1;

    p = (int*)realloc(p,5*sizeof(int));

    for(int i=3;i<5;i++)
        p[i]=i+1;

    for(int i=0;i<5;i++)
        printf("%d ",p[i]);

    free(p);
}

/* 6. Character Pointer and String */
void EC_CP_W2_6()
{
    char str[20] = "hello";
    char *p = str;

    while(*p)
    {
        printf("%c", *p);
        p++;
    }
}

/* 7. Buffer Safety */
void EC_CP_W2_7()
{
    char *buf = (char*)malloc(10);
    fgets(buf,10,stdin); // safe input
    printf("%s",buf);
    free(buf);
}

/* 8. Multi-dimensional Array */
void EC_CP_W2_8()
{
    int a[2][2]={{1,2},{3,4}};
    int *p = &a[0][0];

    for(int i=0;i<4;i++)
        printf("%d ",*(p+i));
}

/* 9. Pointer and Structure */
struct student{
    int id;
    char name[10];
};

void EC_CP_W2_9()
{
    struct student *s;
    s = (struct student*)malloc(sizeof(struct student));

    s->id = 1;
    strcpy(s->name,"Ram");

    printf("%d %s",s->id,s->name);

    free(s);
}

/* 10. Pointer and File I/O */
void EC_CP_W2_10()
{
    FILE *fp = fopen("test.txt","w+");
    char *data = (char*)malloc(20);

    strcpy(data,"Hello File");

    fprintf(fp,"%s",data);

    fclose(fp);
    free(data);
}

/* 11. Linked List */
struct node{
    int data;
    struct node *next;
};

void EC_CP_W2_11()
{
    struct node *head=NULL,*temp;

    head = (struct node*)malloc(sizeof(struct node));
    head->data = 10;
    head->next = NULL;

    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = 20;
    temp->next = NULL;

    head->next = temp;

    struct node *p = head;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}

/* 12. Pointer and Recursion */
void reverse(char *str)
{
    if(*str)
    {
        reverse(str+1);
        printf("%c",*str);
    }
}
void EC_CP_W2_12()
{
    char str[]="hello";
    reverse(str);
}


int main()
{
    //EC_CP_W1_1();
    //EC_CP_W1_2();
    //EC_CP_W1_3();
    //EC_CP_W1_4();
    //EC_CP_W1_5();
    //EC_CP_W1_6();
    //EC_CP_W1_7();
    //EC_CP_W1_8();
    //EC_CP_W1_9();
    //EC_CP_W1_10();
    EC_CP_W1_11();
    EC_CP_W1_12();

}