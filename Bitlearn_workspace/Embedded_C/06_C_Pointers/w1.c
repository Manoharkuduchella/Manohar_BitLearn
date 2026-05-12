#include<stdio.h>

/*. Pointer Declaration and Initialization
*/
void EC_CP_W1_1()
{
    int a=5;
    int *p = &a;

    printf("%d",*p);
}

/* Using & (Address-of) Operator*/
void EC_CP_W1_2()
{
    int x; float y; char z;

    int *ip = &x;float *fp=&y; char *cp=&z;

    *ip = 20;  *fp = 1.2; *cp = 'a';

    printf("%d %f %c",*ip,*fp,*cp);

}

/*Swapping Two Numbers Using Pointers*/
void swap(int *a,int *b)
{
    int t;
    *a = *a ^ *b;
    *b = *a ^ *b;
    * a = *a ^ *b;
}
void EC_CP_W1_4()
{
    int a =10,b=20;
    swap(&a,&b);
    printf("%d %d",a,b);
}

/*Pointer Arithmetic with Arrays*/
void EC_CP_W1_5()
{
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;
    for(int i=0;i<5;i++)
    {
        printf("%d ",*(p+i));
    }
}

/*Modify Array Elements Using Pointers*/
void EC_CP_W1_7()
{
    int arr[] = {2, 4, 6};
    int *p = arr;
    *(p+2) = 3;
    printf("%d",*(p+2));
}

/*. NULL Pointer Safety*/
void EC_CP_W1_8()
{
     int *p = NULL;int a= 10;
     if (p == NULL)
        p = &a; 

}

/*Passing Array to Function*/
void display(int *p,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d",p[i]);
    }
}
void EC_CP_W1_9()
{
    int arr[] = {2, 4, 6};
    display(arr,3);
}

/* Visualizing Memory Addresses*/
void EC_CP_W1_10()
{
    int a,b,c;
    printf("%x %x %x",&a,&b,&c);
}

/*Pointer to Pointer (int **)*/
void EC_CP_W1_11()
{
     int a = 5;
     int *p = &a;
     int **pp = &p;

     printf("%d %d %d ",a,*p,**pp);
}

/* Garbage Pointer*/
void EC_CP_W1_12()
{
    int *p;
    printf("%x",p);
}


/* Pointer Type Compatibility*/
void EC_CP_W1_13()
{
    int *ip;float *fp;
    ip=(int*)fp;

}


int main()
{
    //EC_CP_W1_4();
    //EC_CP_W1_5();
    //EC_CP_W1_7();
    //EC_CP_W1_9();
    //EC_CP_W1_10();
    //EC_CP_W1_11();
    //EC_CP_W1_12();
    EC_CP_W1_13();
}