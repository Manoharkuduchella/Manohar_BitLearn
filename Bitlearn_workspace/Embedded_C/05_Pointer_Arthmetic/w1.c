#include<stdio.h>

/*1 

int arr[] = {5, 10, 15, 20, 25}; 

Expected output: 

Third element is 15 */
void EC_PA_W1_1()
{
    int arr[] = {5,10,15,20,25};

    int *ptr = arr;

    printf("third element is %d",*(ptr+2));
} 

/*int arr[] = {5, 10, 15, 20, 25}; 

Expected output: 

Last element is 25 */

void EC_PA_W1_2()
{
    int arr[] = {5, 10, 15, 20, 25};
    int *ptr = arr;

    printf("third element is %d",*(ptr+4));
}

/*int arr[] = {2, 4, 6, 8, 10}; 

int *p1 = &arr[4]; // points to 10 

int *p2 = &arr[1]; // points to 4 

Expected output: 

Distance between pointers is 3 */

void EC_PA_W1_3()
{
    int arr[] = {2, 4, 6, 8, 10}; 
    int *p1 = &arr[4];
    int *p2 = &arr[1];

    printf("Distance between pointers is %d",(p1-p2));

}

void EC_PA_W1_4()
{
    int arr[] = {11, 22, 33, 44, 55}; 
    int *p1 = &arr[2];
    int *p2 = &arr[4];

    if((p2-p1)>0)
    {
        printf("p1 is earlier than p2");
    }
    else
    {
        printf("p2 is earlier than p1");
    }
}

/*
Using only a pointer (no array indexing), print all elements of the array.*/
void EC_PA_W1_5()
{
    int arr[] = {100, 200, 300, 400}; 
    int *ptr = arr,i=0;
    while(i++ < 4)
    {
        printf("%d ",*ptr++);
    }
}
void EC_PA_W1_6()
{
    //two pointers cant be added
}
/*double darr[] = {1.1, 2.2, 3.3}; 

Expected output: 

Second element is 2.2 */
void EC_PA_W1_7()
{
    double darr[] = {1.1, 2.2, 3.3}; 
    printf("second element is %.2lf",*(darr+1));
}

/*
int arr[] = {10, 20, 30}; 

int *ptr = arr + 5; // Out of bounds */
void EC_PA_W1_8()
{
    //error
}

/*1 

int arr[] = {1, 2, 3, 4, 5}; 

Expected output: 

Reversed array: 5 4 3 2 1 */
void EC_PA_W1_9()
{
    int arr[] = {1, 2, 3, 4, 5};
    int *b = arr,*e=arr+4;

    int tmp;

    for(;(e-b)>0;e++,b--)
    {
        tmp = *b;
        *b = *e;
        *e = tmp;
    }

    for(int i=0;i<5;i++)
    {
        printf("%d ",arr[i]);
    }

}
int main()
{
    //EC_PA_W1_1();
    //EC_PA_W1_2();
    //EC_PA_W1_3();
    //EC_PA_W1_4();
    //EC_PA_W1_5();

    //EC_PA_W1_7();
    EC_PA_W1_9();
}