char *my_strcpy(char *dest, const char *src)
{
    char *ret = dest;
    while((*dest++ = *src++));
    return ret;
}

char *my_strcat(char *dest, const char *src)
{
    char *ret = dest;

    while(*dest)
        dest++;

    while((*dest++ = *src++));
    return ret;
}

int my_strcmp(const char *s1, const char *s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    return (unsigned char)*s1 - (unsigned char)*s2;
}


//selection sort
void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;

    // Traverse through all array elements
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first element
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
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


///*////////////////////////////////
//fibonacci until N terms
#include <stdio.h>

int fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    int N;

    printf("Enter number of terms: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        printf("%d ", fibonacci(i));
    }

    return 0;
}

///////////////////////////////////