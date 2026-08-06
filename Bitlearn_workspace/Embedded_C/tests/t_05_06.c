/*n         = 1100
-n        = 0100  (in two's complement)
n & (-n)  = 0100*/
#define RIGHTMOST_SET_BIT(x) ((x) & (-(x)))

/*7  = 0111
8  = 1000

7 & 8 = 0*/
#define ALL_BITS_SET(x) (((x) != 0) && (((x) & ((x) + 1)) == 0))



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


//diff between monolithic and microkernel
In a monolithic kernel, most OS components run in kernel space:

Process management
Memory management
File systems
Device drivers
Networking stack

A microkernel keeps only the most essential functions in kernel space:

Scheduler
IPC (Inter-Process Communication)
Basic memory management
Other services run in user space:

File systems
Device drivers
Networking