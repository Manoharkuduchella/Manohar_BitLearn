#include<stdio.h>

//arrage the array
void order(int *ptr2,int s)
{
    int tmp,cnt=0;
    for(int i=0;i<s;i++)
    {
        if(ptr2[i] != 0)
        {
            tmp = ptr2[i];
            ptr2[i] = ptr2[cnt];//1020
            ptr2[cnt] = tmp;
            cnt++;
        }
    }
}
/*
int main()
{
    /*
    //find every element of A appears in B exact same noof times(no hashing / no extra array)
    //A = {1,2,2,3} B = {2,1,3,2}

    //sort array
    int n,tmp;int i;int j;
    //int A[] = {1,2,2,3}, B[] = {2,1,3,2};
    int A[] = {1,2,2,3}, B[] = {1,1,2,3};
    printf("size of array:");
    scanf("%d",&n);
    for(i=n-1;i>0;i--)
    {
        for(j=0;j<n-1;j++)
        {
            if(A[j] > A[j+1])
            {
                tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
            if(B[j] > B[j+1])
            {
                tmp = B[j];
                B[j] = B[j+1];
                B[j+1] = tmp;
            }
        }
    }
    //check if A==B
    int flag=0,k=0;
    while(k<n)
    {
        if(A[k] == B[k])
        {
            k++;
        }
        else
        {
            flag =1;
            break;
        }
    }

    if(flag)
    {
        printf("No");
    }
    else{
        printf("Yes");
    }
    */


    /*
    //in given 2D array move all zeros to end
    int r=3,c=4;

    int arr[][4] = {{1,0,2,0},{3,4,0,5},{0,6,0,7}};

    int (*ptr)[c]=arr;

    for(int i=0;i<r;i++)
    {
        order(ptr[i],4);
    }

    //print 2d array
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            printf("%d ",arr[i][j]);
        }
    }
    */

/*}*/



//Find Nth node form the end in the list
struct Node
{
    int data;
    struct Node *next;
};

void findNthNode(struct Node *head,int n)
{
    struct Node *fast,*slow;
    fast=slow=head;

    //move fast for n times
    for(int i=0;i<n;i++)
    {
        if(fast == NULL)
        {
            printf("Error: list has fewer nodes\n");
            return;
        }
        fast = fast->next;
    }

    while(fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }
    //slow will be at nth node form the end
    printf("Node at index %d from end is: %d\n",n,slow->data);
}

int main()
{
    
}