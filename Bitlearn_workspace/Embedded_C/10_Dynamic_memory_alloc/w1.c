#include<stdio.h>
#include<stdlib.h>
/* Compare malloc and calloc */
void print(int *p,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",p[i]);
    }
}

void EC_DMA_W1_4()
{
    int *a,*b;

    a = (int *)malloc(sizeof(int)*5);
    b = calloc(5,sizeof(int));
    printf("enter a:");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&a[i]);
    }

    printf("enter b:");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&b[i]);
    }

    print(a,5);print(b,5);


}

/* Log Session a Dynamic 2D Array*/
void EC_DMA_W1_5()
{
    int (*p)[5];

    p = malloc(3*sizeof(*p));
    printf("enter 2d array\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            scanf("%d",&p[i][j]);
        }
    }

    printf("entered 2d array\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("%d ",p[i][j]);
        }
    }
    free(p);
}

/*Dynamic String Input*/
char *getstring()
{
    char *ptr=NULL;int cnt =0;
    do
    {
        ptr = realloc(ptr,(sizeof(char)*(cnt+1)));
        ptr[cnt] = getchar();
    } while(ptr[cnt++] != '\n');
    ptr[cnt-1] = 0;

    return ptr;
    
}
void EC_DMA_W1_7()
{
    char *p;
    printf("enter the string\n");
    p = getstring();
    printf("%s",p);
    free(p);
}

/*Log Session a Linked List with 3 Nodes */
struct node{
    int data;
    struct node *next;
};

struct node *Add_node(struct node *head,int d)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = d;
    newnode->next = NULL;
    if(head == NULL)
    {
        head = newnode;
    }
    else
    {
        struct node *tmp;
        for(tmp=head;tmp->next != NULL;tmp=tmp->next);
        tmp->next = newnode;
    }
    return head;
}

void print_list(struct node *head)
{
    if(head == NULL)
    {
        printf("list is empty\n");
    }
    else
    {
        while(head != NULL)
        {
            printf("%d->",head->data);
            head = head->next;
        }
    }

}

void free_list(struct node *head)
{
    if(head == NULL)
    {
        printf("list is empty\n");
    }else{
        struct node *tmp;
        while(head != NULL)
        {
            tmp = head;
            head = head->next;
            free(tmp);
        }
    }
}
void EC_DMA_W1_9()
{
    struct node *head=NULL;
    int cnt=3;
    while(cnt-- > 0 )
    {
        head = Add_node(head,cnt);
    }
    print_list(head);
    free_list(head);
}



void EC_DMA_W1_1()
{
    int *p = (int*)malloc(sizeof(int));

    if(p == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    *p = 10;
    printf("Value: %d\n", *p);

    free(p);
}

void EC_DMA_W1_2()
{
    int n;
    scanf("%d",&n);

    int *p = (int*)malloc(n*sizeof(int));

    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);

    for(int i=0;i<n;i++)
        printf("%d ",p[i]);

    free(p);
}


void EC_DMA_W1_3()
{
    int n;
    scanf("%d",&n);

    int *p = (int*)calloc(n,sizeof(int));

    for(int i=0;i<n;i++)
        printf("%d ",p[i]);

    for(int i=0;i<n;i++)
        p[i]=i+1;

    for(int i=0;i<n;i++)
        printf("%d ",p[i]);

    free(p);
}


void EC_DMA_W1_4()
{
    int *m = (int*)malloc(5*sizeof(int));
    int *c = (int*)calloc(5,sizeof(int));

    for(int i=0;i<5;i++)
        printf("malloc:%d calloc:%d\n", m[i], c[i]);

    free(m);
    free(c);
}


void EC_DMA_W1_5()
{
    int *p = (int*)malloc(2*sizeof(int));

    for(int i=0;i<2;i++)
        scanf("%d",&p[i]);

    p = (int*)realloc(p,5*sizeof(int));

    for(int i=2;i<5;i++)
        scanf("%d",&p[i]);

    for(int i=0;i<5;i++)
        printf("%d ",p[i]);

    free(p);
}

void EC_DMA_W1_6()
{
    int r,c;
    scanf("%d%d",&r,&c);

    int **p = malloc(r*sizeof(int*));

    for(int i=0;i<r;i++)
        p[i] = malloc(c*sizeof(int));

    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            scanf("%d",&p[i][j]);

    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
            printf("%d ",p[i][j]);
        printf("\n");
    }

    for(int i=0;i<r;i++)
        free(p[i]);
    free(p);
}




#include <string.h>

void EC_DMA_W1_7()
{
    char str[100];
    scanf("%s",str);

    int len = strlen(str);

    char *p = (char*)malloc(len+1);

    strcpy(p,str);

    printf("%s",p);

    free(p);
}

char* my_strdup(const char *s)
{
    int len=0;
    while(s[len]) len++;

    char *p = (char*)malloc(len+1);

    for(int i=0;i<=len;i++)
        p[i]=s[i];

    return p;
}

void EC_DMA_W1_8()
{
    char str[]="hello";

    char *dup = my_strdup(str);

    printf("%s",dup);

    free(dup);
}


struct node{
    int data;
    struct node *next;
};

void EC_DMA_W1_9()
{
    struct node *n1 = malloc(sizeof(struct node));
    struct node *n2 = malloc(sizeof(struct node));
    struct node *n3 = malloc(sizeof(struct node));

    n1->data=1; n2->data=2; n3->data=3;

    n1->next=n2;
    n2->next=n3;
    n3->next=NULL;

    struct node *p=n1;

    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }

    free(n1); free(n2); free(n3);
}


void EC_DMA_W1_10()
{
    int n;
    scanf("%d",&n);

    int *p = malloc(n*sizeof(int));

    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);

    int *start=p, *end=p+n-1;

    while(start<end)
    {
        int temp=*start;
        *start=*end;
        *end=temp;

        start++; end--;
    }

    for(int i=0;i<n;i++)
        printf("%d ",p[i]);

    free(p);
}




int main()
{
    //EC_DMA_W1_4();
    //EC_DMA_W1_5();

    //EC_DMA_W1_7();

    EC_DMA_W1_9();
    EC_DMA_W1_10();
}