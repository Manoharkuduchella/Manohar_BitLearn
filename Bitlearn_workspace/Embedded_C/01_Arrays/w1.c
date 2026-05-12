#include <stdio.h>
#include <string.h>

/*
Question: Print elements of an array
Question description: Write a C program to read n elements into an array and display them.
Sample data:
Enter the number of elements: 5
Enter the elements: 10 20 30 40 50
*/
void EC_Arr_W1_1()
{
    int n;
    printf("enter the noof elements:\n");
    scanf("%d",&n);
    int arr[n];
    
    printf("enter the elements:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    printf("elements in the array are:\n");
    for(int j=0;j<n;j++)
    {
        printf("%d ",arr[j]);
    }
    
}

/*
Question: Sum of all elements in array
Question description: Write a C program to find the sum of all array elements entered by the user.
Sample data:
Input: 1 2 3 4 5
Expected output:
Sum = 15
*/
void EC_Arr_W1_2()
{
    int arr[5],sum=0;
    printf("enter the elements:\n");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    for(int j=0;j<5;j++)
    {
        sum += arr[j];
    }
    printf("Sum=%d",sum);
}

/*
Question: Find maximum and minimum element
Question description: Write a C program to find the largest and smallest element in the array.
Sample data:
Input: 8 3 15 6 2
Expected output:
Maximum = 15
Minimum = 2
*/
void EC_Arr_W1_3()
{
    int max=0,min=20;int arr[5];
    printf("enter the elements:\n");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    for(int j=0;j<5;j++)
    {
        if(max < arr[j])
        {
            max = arr[j];
        }
        
        if(min > arr[j])
        {
            min = arr[j];
        }
    }
    
    printf("Maximum = %d\nMinimum = %d",max,min);
}


/*
Question: Count even and odd elements
Question description: Write a C program to count how many even and odd numbers are in the array.
Sample data:
Input: 4 7 9 10 22
Expected output:
Even: 3
Odd: 2

*/
void EC_Arr_W1_4()
{
    int e_cnt=0,o_cnt=0;int arr[5];
    printf("enter the elements:\n");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    for(int j=0;j<5;j++)
    {
        if(!(arr[j]%2))
        {
            e_cnt++;
        }else
        {
            o_cnt++;   
        }
    }
    
    printf("Even:%d\nOdd:%d",e_cnt,o_cnt);
}

/*
Question: Copy array elements
Question description: Write a C program to copy all elements from one array to another.
Sample data:
Input: 1 2 3 4 5
Expected output:
Copied array: 1 2 3 4 5
*/

void EC_Arr_W1_5()
{
    int arr1[5],arr2[5];
    printf("enter the elements:\n");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&arr1[i]);
    }
    
    for(int i=0;i<5;i++)
    {
        arr2[i]=arr1[i];
    }
    
    printf("Copied array:\n");
    for(int i=0;i<5;i++)
    {
        printf("%d ",arr2[i]);
    }
    
}


/*
Question: Count negative elements
Question description: Write a C program to count total number of negative elements in an array.
Sample data:
Input: -1 3 -4 5 0 -7
Expected output:
Total negative elements: 3
*/
void EC_Arr_W1_6()
{
    int arr[5],cnt=0;
    printf("enter the elements:\n");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    for(int i=0;i<5;i++)
    {
        if(arr[i] < 0)
        {
            cnt++;
        }
    }
    
}
/*
Question: Find for an element
Question description: Write a C program to search for a number in an array and print its index.
Sample data:
Array: 10 20 30 40 50
Find: 30
Expected output:
Element found at index: 2
*/
void EC_Arr_W1_7()
{
    int arr[5];int elm;
    printf("enter the elements:\n");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("Find:");
    scanf("%d",&elm);
    
    for(int i=0;i<5;i++)
    {
        if(arr[i] == elm)
        {
            printf("Eelement found at index:%d",i);
        }
    }
}

/*
Question: Reverse an array
Question description: Write a C program to reverse an array in-place.
Sample data:
Input: 10 20 30 40 50
Expected output:
Reversed array: 50 40 30 20 10
*/
void EC_Arr_W1_8()
{
    int arr[5];
    printf("enter the elements:\n");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    for(int i=0,j=(sizeof(arr)/sizeof(int))-1,tmp;i<j;i++,j--)
    {
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
        
    printf("reversed array:\n");
    for(int i=0;i<5;i++)
    {
        printf("%d ",arr[i]);
    }
    
}

/*
Question: Insert element at position
Question description: Write a C program to insert a number at a given position in an array.
Sample data:
Array: 10 20 30 40
Insert: 25 at position 2
Expected output:
Array after insertion: 10 20 25 30 40
*/
void EC_Arr_W1_9()
{
    int arr[5];int pos,ele;
    printf("enter the elements:\n");
    for(int i=0;i<4;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("element and pos\n");
    scanf("%d %d",&ele,&pos);
    
    memcpy(arr+pos+1,arr+pos,2*sizeof(int));
    arr[pos] = ele;
    
    printf("After insertion:\n");
    for(int i=0;i<5;i++)
    {
        printf("%d ",arr[i]);
    }
    
}

/*
Question: Delete element at position
Question description: Write a C program to delete a number at a given position in an array.
Sample data:
Array: 10 20 30 40
Delete at position: 2
Expected output:
Array after deletion: 10 20 40

*/
void EC_Arr_W1_10()
{
    int arr[4];int pos;
    printf("enter the elements:\n");
    for(int i=0;i<4;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("pos\n");
    scanf("%d",&pos);
    
    memmove(arr+pos,arr+pos+1,1*sizeof(int));
    
    printf("After deletion:\n");
    for(int i=0;i<3;i++)
    {
        printf("%d ",arr[i]);
    }
    
    
}
/*
Question: Sort array in ascending order
Question description: Write a C program to sort elements in ascending order.
Sample data:
Input: 20 5 10 8
Expected output:
Sorted array: 5 8 10 20

*/
void EC_Arr_W1_11()
{
    int arr[4],swp;
    printf("enter the elements:\n");
    for(int i=0;i<4;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    for(int i=3;i>0;i--)
    {
        for(int j=0;j<i;j++)
        {
            if(arr[j] > arr[j+1])
            {
                swp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = swp;
            }
        }
    }
    
    printf("Sorted Array:\n");
    for(int i=0;i<4;i++)
    {
        printf("%d ",arr[i]);
    }
    
}

/*
Question: Sort array in descending order
Question description: Write a C program to sort array elements in descending order.
Sample data:
Input: 7 2 9 4
Expected output:
Sorted array: 9 7 4 2
*/

void EC_Arr_W1_12()
{
    int arr[4],swp;
    printf("enter the elements:\n");
    for(int i=0;i<4;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    for(int i=3;i>0;i--)
    {
        for(int j=0;j<i;j++)
        {
            if(arr[j] < arr[j+1])
            {
                swp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = swp;
            }
        }
    }
    
    printf("Sorted Array:\n");
    for(int i=0;i<4;i++)
    {
        printf("%d ",arr[i]);
    }
}

/*

Question: Merge two arrays
Question description: Write a C program to merge two arrays into a third array.
Sample data:
Array 1: 1 2 3
Array 2: 4 5 6
Expected output:
Merged array: 1 2 3 4 5 6
*/
void EC_Arr_W1_13()
{
    int arr1[3],arr2[3];
    int merge[6];
    
    printf("enter the elements of arr1:\n");
    for(int i=0;i<3;i++)
    {
        scanf("%d",&arr1[i]);
    }
    
    printf("enter the elements of arr2:\n");
    for(int i=0;i<3;i++)
    {
        scanf("%d",&arr2[i]);
    }
    
    for(int i=0;i<6;i++)
    {
        if(i<3)
        {
            merge[i] = arr1[i];
        }else
        {
            merge[i] = arr2[i-3];
        }
    }
    
    printf("enter the elements of merged:\n");
    for(int i=0;i<6;i++)
    {
        printf("%d ",merge[i]);
    }
    

}

/*
Question: Frequency of each element
Question description: Write a C program to count the frequency of each element in an array.
Sample data:
Input: 1 2 2 3 3 3
Expected output:
1 occurs 1 time
2 occurs 2 times
3 occurs 3 times
*/
void EC_Arr_W1_14()
{
    int arr[6];
    printf("enter the elements of arr:\n");
    for(int i=0;i<6;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    int freq[6] = {0};
    
    for(int i=0;i<6;i++)
    {
        freq[arr[i]]++;
    }
    
    for(int i=0;i<6;i++)
    {
        if(freq[i]==1)
        {
            printf("%d occurs %d time\n",i,freq[i]);
        }
        else if(freq[i] > 1)
        {
            printf("%d occurs %d times\n",i,freq[i]);
        }
            
    }
    
}

/*
Question: Remove duplicate elements
Question description: Write a C program to remove duplicate elements from an array.
Sample data:
Input: 2 3 2 4 3 5
Expected output:
Array after removing duplicates: 2 3 4 5

*/
void EC_Arr_W1_15()
{
    int arr[6];int n=6;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(arr[i] == arr[j])
            {
                for(int k=j;k<n-1;k++)
                {
                    arr[k] = arr[k+1];
                }
                n--;
                j--;
            }
        }
    }

    printf("elements after removing:\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }

}

/*
Question: Find duplicate elements
Question description: Write a C program to find all duplicate elements in an array.
Sample data:
Input: 1 2 3 2 4 1
Expected output:
Duplicate elements: 1 2

*/
void EC_Arr_W1_16()
{
    int arr[6];int n=6;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    int visited[6] = {0};

    for(int i=0;i<n;i++)
    {
        if(visited[i] == 1)
            continue;
        for(int j=i+1;j<n;j++)
        {
            if(arr[i] == arr[j])
            {
                printf("%d ",arr[i]);
                visited[i] = visited[j] = 1;
            }
        }
    }
}

/*Question: Find second largest element
Question description: Write a C program to find the second largest number in the array.
Sample data:
Input: 10 20 50 40
Expected output:
Second largest: 40*/
void EC_Arr_W1_17()
{
    int arr[4];int n=4;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    int l = 0, sl=0;

    for(int i=0;i<n;i++)
    {
        if(arr[i] > l)
        {
            sl = l;
            l = arr[i];
        }
        else if(arr[i] > sl && arr[i] != l)
        {
            sl = arr[i];
        }
        
    }
    printf("second larges:%d",sl);
}

/*Question: Difference between max and min
Question description: Write a C program to find the difference between largest and smallest elements in an array.
Sample data:
Input: 5 1 9 3 6
Expected output:
Difference: 8*/
void EC_Arr_W1_18()
{
    int arr[5];int n=5;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    int l = arr[0], s=arr[1];

    for(int i=0;i<n;i++)
    {
        if(arr[i] > l)
        {
            l = arr[i];
        }
        if(arr[i] < s)
        {
            s = arr[i];
        }
    }

    printf("Difference:%d\n",l-s);

}

void EC_Arr_W1_19()
{
    int arr[5];int n=5,k,tmp;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("Rotate:");
    scanf("%d",&k);
    int j;
    for(int i=0;i<k;i++)
    {
        tmp = arr[0];
        for(j=0;j<n-1;j++)
        {
            arr[j] = arr[j+1];
        }
        arr[n-1] = tmp;

    }

    printf("Rotate array:\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
}

/*Question: Right rotate array by n
Question description: Write a C program to rotate an array to the right by n positions.
Sample data:
Array: 1 2 3 4 5
Rotate by: 2
Expected output:
Rotated array: 4 5 1 2 3*/
void EC_Arr_W1_20()
{
    int arr[5];int n=5,k,tmp;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("Rotate:");
    scanf("%d",&k);

    while(k--)
    {
        tmp = arr[n-1];
        for(int j=n-1;j>0;j--)
        {
            arr[j] = arr[j-1]; 
        }
        arr[0] = tmp;
    }

    printf("right Rotate array:\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
}

/*Question: Sum of even numbers
Question description: Write a C program to find the sum of all even numbers in an array.
Sample data:
Input: 2 3 4 5 6
Expected output:
Sum of even numbers: 12*/
void EC_Arr_W1_21()
{
     int arr[5];int n=5;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    int sum=0;
    for(int i=0;i<n;i++)
    {
        if(!(arr[i]%2))
            sum += arr[i];
    }
    printf("Sum of even numbers:%d",sum);
}

/*Question: Count prime numbers
Question description: Write a C program to count and display all prime numbers in an array.
Sample data:
Input: 2 4 5 6 7 8
Expected output:
Primes: 2 5 7
Count: 3*/
int isprime(int n)
{
    if(n==2)
        return 1;

    for(int i=2;i<n;i++)
    {
        if(!(n%i))
            return 0;
    }
    return 1;
}
void EC_Arr_W1_22()
{
    int arr[6];int n=6;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    int cnt=0;
    printf("Primes:");
    for(int i=0;i<n;i++)
    {
        if(isprime(arr[i]))
        {
            printf("%d ",arr[i]);
            cnt++;
        }
    }
    printf("\nCount:%d",cnt);
}

/*Question: Count duplicate elements
Question description: Write a C program to count how many duplicate values are in the array.
Sample data:
Input: 1 2 3 1 4 2
Expected output:
Total duplicate elements: 2*/
void EC_Arr_W1_23()
{
    int arr[6];int n=6;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    int visited[6] = {0};
    int cnt=0;

    for(int i=0;i<n;i++)
    {
        if(visited[i] == 1)
            continue;
        for(int j=i+1;j<n;j++)
        {
            if(arr[i] == arr[j])
            {
                cnt++;
                visited[i] = visited[j] = 1;
            }
        }
    }
    printf("Total Duplicate elements:%d",cnt);
}

/*Question: Split array into halves
Question description: Write a C program to split the array into two halves and print them separately.
Sample data:
Input: 1 2 3 4 5 6
Expected output:
First half: 1 2 3
Second half: 4 5 6*/
void EC_Arr_W1_24()
{
    int arr[6];int n=6;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    int mid = n/2;
    printf("First half:");
    for(int i=0;i<mid;i++)
        printf("%d ",arr[i]);

    printf("\nSecond half:");
    for(int i=mid;i<n;i++)
        printf("%d ",arr[i]);
}

/*Question: Segregate even and odd
Question description: Write a C program to arrange all even numbers first and then all odd numbers.
Sample data:
Input: 1 2 3 4 5 6
Expected output:
Even numbers: 2 4 6
Odd numbers: 1 3 5*/

void EC_Arr_W1_25()
{
    int arr[6];int n=6;
    printf("enter the elements of arr:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("Even numbers:");
    for(int i=0;i<n;i++)
    {
        if(!(arr[i]%2))
            printf("%d ",arr[i]);
    }

    printf("\nOdd numbers:");
    for(int i=0;i<n;i++)
    {
        if((arr[i]%2))
            printf("%d ",arr[i]);
    }
}

int main()
{
    //EC_Arr_W1_1();
    //EC_Arr_W1_2();
    //EC_Arr_W1_3();
    //EC_Arr_W1_4();
    //EC_Arr_W1_5();
    
    //EC_Arr_W1_6();
    //EC_Arr_W1_7();
    //EC_Arr_W1_8();
    
    //EC_Arr_W1_9();
    //EC_Arr_W1_10();
    
    //EC_Arr_W1_11();
    
    //EC_Arr_W1_12();
    
    //EC_Arr_W1_13();
    
    //EC_Arr_W1_14();

    //EC_Arr_W1_15();
    
    //EC_Arr_W1_16();

    //EC_Arr_W1_17();

    //EC_Arr_W1_18();
    //EC_Arr_W1_19();

    //EC_Arr_W1_20();

    //EC_Arr_W1_21();

    //EC_Arr_W1_22();

    //EC_Arr_W1_23();

    //EC_Arr_W1_24();

    EC_Arr_W1_25();
    return 0;
}