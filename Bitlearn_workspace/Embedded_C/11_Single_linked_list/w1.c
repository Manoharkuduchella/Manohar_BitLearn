#include<stdio.h>
#include<stdlib.h>
/*Merge Sorted Lists Challenges */
struct node{
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
void EC_SLL_W1_1()
{
    struct node *head=NULL,*head2=NULL;
    head = Add_node(head,1);
    head = Add_node(head,3);
    head = Add_node(head,5);
    head = Add_node(head,7);
    print_list(head);
   
    printf("\n");
    head2 = Add_node(head2,2);
    head2 = Add_node(head2,4);
    head2 = Add_node(head2,6);
    print_list(head2);


    struct node dummy;
    struct node *un = &dummy;
    struct node *tmp = un;
    while(head != NULL && head2 != NULL)
    {
        if(head->data < head2->data)
        {
            tmp->next = head;
            head = head->next;
        }
        else {
            tmp->next = head2;
            head2 = head2->next;  
        }
        tmp = tmp->next;
    }

    while(head != NULL)
    {
        tmp->next = head;
        head = head->next;
        tmp = tmp->next;
    }
    while(head2 != NULL)
    {
        tmp->next = head;
        head2 = head->next;
        tmp = tmp->next;
    }

    printf("\nAfter union:\n");
    un = un->next;
    print_list(un);
    //free_list(head);
    //free_list(head2);
}


// Loop detection and removal (Floyd’s Cycle Detection)
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void detectAndRemoveLoop(struct Node* head) {
    struct Node *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            slow = head;
            struct Node* prev = NULL;

            while (slow != fast) {
                prev = fast;
                slow = slow->next;
                fast = fast->next;
            }
            prev->next = NULL;
            printf("Loop detected and removed.\n");
            return;
        }
    }
    printf("No loop found.\n");
}


// Palindrome check
#include <stdio.h>

int isPalindrome(struct Node* head) {
    struct Node *slow = head, *fast = head;
    struct Node *prev = NULL, *next = NULL;

    while (fast && fast->next) {
        fast = fast->next->next;

        next = slow->next;
        slow->next = prev;
        prev = slow;
        slow = next;
    }

    if (fast) slow = slow->next;

    while (prev && slow) {
        if (prev->data != slow->data)
            return 0;
        prev = prev->next;
        slow = slow->next;
    }
    return 1;
}


// Deep copy with random pointer
#include <stdio.h>
#include <stdlib.h>

struct NodeR {
    int data;
    struct NodeR *next, *random;
};

struct NodeR* copyList(struct NodeR* head) {
    struct NodeR *temp = head;

    while (temp) {
        struct NodeR* newNode = malloc(sizeof(struct NodeR));
        newNode->data = temp->data;
        newNode->next = temp->next;
        temp->next = newNode;
        temp = newNode->next;
    }

    temp = head;
    while (temp) {
        if (temp->random)
            temp->next->random = temp->random->next;
        temp = temp->next->next;
    }

    struct NodeR* newHead = head->next;
    temp = head;

    while (temp) {
        struct NodeR* copy = temp->next;
        temp->next = copy->next;
        if (copy->next)
            copy->next = copy->next->next;
        temp = temp->next;
    }

    return newHead;
}


// Intersection of two lists
int getIntersection(struct Node* a, struct Node* b) {
    struct Node *p = a, *q = b;

    while (p != q) {
        p = (p) ? p->next : b;
        q = (q) ? q->next : a;
    }
    return p ? p->data : -1;
}



// Partition around x
struct Node* partition(struct Node* head, int x) {
    struct Node *before = NULL, *after = NULL;
    struct Node *bTail = NULL, *aTail = NULL;

    while (head) {
        struct Node* next = head->next;
        head->next = NULL;

        if (head->data < x) {
            if (!before) before = bTail = head;
            else { bTail->next = head; bTail = head; }
        } else {
            if (!after) after = aTail = head;
            else { aTail->next = head; aTail = head; }
        }
        head = next;
    }

    if (!before) return after;
    bTail->next = after;
    return before;
}

// Add two numbers (reverse order)
struct Node* addLists(struct Node* l1, struct Node* l2) {
    struct Node* result = NULL;
    struct Node* tail = NULL;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) { sum += l1->data; l1 = l1->next; }
        if (l2) { sum += l2->data; l2 = l2->next; }

        struct Node* newNode = malloc(sizeof(struct Node));
        newNode->data = sum % 10;
        newNode->next = NULL;

        carry = sum / 10;

        if (!result) result = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    return result;
}




// Rotate list by k
struct Node* rotate(struct Node* head, int k) {
    if (!head) return head;

    struct Node* temp = head;
    int len = 1;

    while (temp->next) {
        temp = temp->next;
        len++;
    }

    k = k % len;
    if (k == 0) return head;

    temp->next = head;

    for (int i = 0; i < len - k; i++)
        temp = temp->next;

    struct Node* newHead = temp->next;
    temp->next = NULL;

    return newHead;
}

// Swap kth node
struct Node* swapKth(struct Node* head, int k) {
    struct Node *x = head, *y = head;

    for (int i = 1; i < k && x; i++)
        x = x->next;

    struct Node* temp = x;
    while (temp->next) {
        temp = temp->next;
        y = y->next;
    }

    int t = x->data;
    x->data = y->data;
    y->data = t;

    return head;
}


// Merge sort
struct Node* merge(struct Node* a, struct Node* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->data < b->data) {
        a->next = merge(a->next, b);
        return a;
    } else {
        b->next = merge(a, b->next);
        return b;
    }
}

void split(struct Node* head, struct Node** a, struct Node** b) {
    struct Node* slow = head;
    struct Node* fast = head->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *a = head;
    *b = slow->next;
    slow->next = NULL;
}

struct Node* mergeSort(struct Node* head) {
    if (!head || !head->next) return head;

    struct Node *a, *b;
    split(head, &a, &b);

    a = mergeSort(a);
    b = mergeSort(b);

    return merge(a, b);
}

// Nth from end
int nthFromEnd(struct Node* head, int n) {
    struct Node *p = head, *q = head;

    for (int i = 0; i < n; i++)
        q = q->next;

    while (q) {
        p = p->next;
        q = q->next;
    }

    return p->data;
}


// Merge K sorted lists (simple method)
struct Node* mergeK(struct Node* arr[], int k) {
    struct Node* result = NULL;

    for (int i = 0; i < k; i++)
        result = merge(result, arr[i]);

    return result;
}



// Odd-even rearrangement
struct Node* oddEven(struct Node* head) {
    if (!head) return head;

    struct Node *odd = head, *even = head->next, *evenHead = even;

    while (even && even->next) {
        odd->next = even->next;
        odd = odd->next;

        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead;
    return head;
}

// Reverse in pairs
struct Node* pairReverse(struct Node* head) {
    if (!head || !head->next) return head;

    struct Node* temp = head->next;
    head->next = pairReverse(temp->next);
    temp->next = head;

    return temp;
}



// Reverse in blocks of k
struct Node* reverseK(struct Node* head, int k) {
    struct Node *curr = head, *prev = NULL, *next = NULL;
    int count = 0;

    while (curr && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    if (next)
        head->next = reverseK(next, k);

    return prev;
}


// Alternate k reverse
struct Node* altK(struct Node* head, int k) {
    struct Node *curr = head, *prev = NULL, *next = NULL;
    int count = 0;

    while (curr && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    if (head)
        head->next = curr;

    count = 0;
    while (count < k - 1 && curr) {
        curr = curr->next;
        count++;
    }

    if (curr)
        curr->next = altK(curr->next, k);

    return prev;
}


// Split list into halves
void splitHalf(struct Node* head, struct Node** a, struct Node** b) {
    struct Node *slow = head, *fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *a = head;
    *b = slow->next;
    slow->next = NULL;
}


// Merge alternate nodes
struct Node* mergeAlt(struct Node* a, struct Node* b) {
    struct Node* head = a;

    while (a && b) {
        struct Node* aNext = a->next;
        struct Node* bNext = b->next;

        a->next = b;
        b->next = aNext;

        a = aNext;
        b = bNext;
    }
    return head;
}


// Interleave lists
struct Node* interleave(struct Node* a, struct Node* b) {
    return mergeAlt(a, b);
}


// Swap adjacent nodes (iterative)
struct Node* swapPairs(struct Node* head) {
    struct Node dummy;
    dummy.next = head;
    struct Node* prev = &dummy;

    while (head && head->next) {
        struct Node* first = head;
        struct Node* second = head->next;

        prev->next = second;
        first->next = second->next;
        second->next = first;

        prev = first;
        head = first->next;
    }

    return dummy.next;
}







int main()
{
    //EC_SLL_W1_1();
}