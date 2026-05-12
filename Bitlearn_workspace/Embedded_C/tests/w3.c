//find loop and remove loop
#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *Add_node(struct node *head,int d)
{
    struct node *newnode = (struct node *)calloc(1,sizeof(struct node));
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

void detect_loop()
{
    struct node *head=NULL,*head2=NULL;
    head = Add_node(head,1);
    head = Add_node(head,3);
    head = Add_node(head,5);
    head = Add_node(head,7);
    print_list(head);

    

    free_list(head);
}

int main()
{
    detect_loop();
}