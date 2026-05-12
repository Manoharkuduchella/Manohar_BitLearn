#include<stdlib.h>
#include<stdio.h>
/*Find the union of two arrays
Question description:
Write a C program to find the union of two arrays (all unique elements from both arrays).
Sample data:
Array 1: 1 2 3 4 Array 2: 3 4 5 6
Expected output:
Union: 1 2 3 4 5 6*/
void EC_Arr_W2_26()
{
    int arr1[4] = {1,2,3,4},arr2[4] = {3,4,5,6};
    int i=0,j=0;
    printf("Union: ");
    while(i<4 && j<4)
    {
        if(arr1[i] != arr2[j])
        {
            if(arr1[i] < arr2[j])
                printf("%d ",arr1[i++]);
            else
                printf("%d ",arr2[j++]);
        }
        else{
            printf("%d ",arr2[j]);
            i++;j++;
        }
    }
    while(i<4 || j<4)
    {
        if(i<4)
            printf("%d ",arr1[i++]);
        if(j<4)
            printf("%d ",arr2[j++]);
    }

}

/*Find the intersection of two arrays
Question description:
Write a C program to find the intersection of two arrays (common elements).
Sample data:
Array 1: 1 2 3 4 Array 2: 3 4 5 6
Expected output:
Intersection: 3 4*/
void EC_Arr_W2_27()
{
    int arr1[4] = {1,2,3,4},arr2[4] = {3,4,5,6};
    
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(arr1[i] == arr2[j])
            {
                printf("%d ",arr1[i]);
            }
        }
    }
}

/*
Find the difference of two arrays
Question description:
Write a C program to find the difference of two arrays (elements present in first array but not in second).
Sample data:
Array 1: 1 2 3 4 Array 2: 3 4 5 6
Expected output:
Difference (Array1 - Array2): 1 2*/
void EC_Arr_W2_28()
{
    int arr1[4] = {1,2,3,4},arr2[4] = {3,4,5,6};
    printf("difference of Arr1-Arr2:");
    int j;
    for(int i=0;i<4;i++)
    {
        int j;
        for(j=0;j<4;j++)
        {
            if(arr1[i] == arr2[j])
                break;
            
        }
        if(j==4)
            printf("%d ",arr1[i]);
    }

}

/* Check if array is palindrome
Question description:
Write a C program to check whether an array is palindrome (reads the same forward and backward).
Sample data:
Input: 1 2 3 2 1
Expected output:
The array is a palindrome.
*/
void EC_Arr_W2_29()
{
    int arr[5] = {1,2,3,2,1};
    int i,j;
    for(i=0,j=4;i<j;i++,j--)
    {
        if(arr[i] != arr[j])
        break;
    }
    if(i<j)
        printf("The array is not a palindrome\n");
    else
        printf("The array is a plindrome\n");
}

/*Count pairs with given sum
Question description:
Write a C program to find number of pairs in the array whose sum is equal to a given value.
Sample data:
Input array: 1 5 7 -1 5 Sum = 6
Expected output:
Number of pairs: 3
*/
void EC_Arr_W2_30()
{
    int arr[5] = {1,5,7,-1,5};
    int sum = 6,cnt=0;
    for(int i=0;i<5;i++)
    {
        for(int j=i+1;j<5;j++)
        {
            if((arr[i]+arr[j])==sum)
            cnt++;
        }
    }
    printf("No of Pairs:%d",cnt);
}


/*
 Find missing number in array
Question description:
Write a C program to find the missing number in an array of size n containing numbers from 1 to n+1.
Sample data:
Input: 1 2 4 5 6
Expected output:
Missing number is: 3
*/
void EC_Arr_W2_31()
{
    int arr[5] = {1,2,4,5,6};
    int sum=0,asum=0;
    for(int i=1;i<=5+1;i++)
    {
        sum += i;
    }
    for(int i=0;i<5;i++)
    {
        asum += arr[i];
    }

    printf("Missing number is:%d",sum-asum);
}

/*
Question description:
Write a C program to find the missing number in an array of size n containing numbers from 1 to n+1.
Sample data:
Input: 1 2 4 5 6
Expected output:
Missing number is: 3
*/
void EC_Arr_W2_32()
{
    int arr[7]={2,2,1,2,3,2,2};int n=7;

    int candidate =-1,cnt=0;
    for(int i=0;i<7;i++)
    {
        if(cnt==0)
        {
            candidate = arr[i];
            cnt = 1;
        }else if(candidate == arr[i])
        {
            cnt++;
        }
        else{
            cnt--;
        }
    }
    cnt=0;
    for(int i=0;i<n;i++)
    {
        if(candidate == arr[i])
            cnt++;
    }

    if(cnt > n/2)
        printf("Majority:%d",candidate);


}

/*Find subarray with maximum sum (Kadane’s Algorithm)
Question description:
Write a C program to find the maximum sum of a contiguous subarray.
Sample data:
Input: -2 -3 4 -1 -2 1 5 -3
Expected output:
Maximum contiguous sum is 7
*/
//33
void EC_Arr_W2_33()
{
    int arr[] = {-2,-3,4,-1,-2,1,5,-3};
    int max = arr[0], cur = arr[0];

    for(int i=1;i<8;i++)
    {
        if(arr[i] > cur + arr[i])
            cur = arr[i];
        else
            cur += arr[i];

        if(cur > max)
            max = cur;
    }

    printf("Maximum contiguous sum is %d",max);
}

/*Find leader elements in array
Question description:
Write a C program to find all leader elements in the array (elements greater than all elements to their right).
Sample data:
Input: 16 17 4 3 5 2
Expected output:
Leader elements: 17 5 2
*/

void EC_Arr_W2_34()
{
    int arr[6] = {16,17,4,3,5,2};

    int leaders[6],cnt=0;
    int max = arr[5];
    leaders[cnt++] = max;
    for(int i=4;i>=0;i--)
    {
        if(arr[i] >= max)
        {
            max = arr[i];
            leaders[cnt++] = max;
        }
    }
    for(int i=cnt-1;i>=0;i--)
    {
        printf("%d ",leaders[i]);
    }
}

/*Find second smallest element
Question description:
Write a C program to find the second smallest element in the array.
Sample data:
Input: 12 13 1 10 34 1
Expected output:
Second smallest element is 10*/
void EC_Arr_W2_36()
{
    int arr[6] = {12,13,1,10,34,1};
    int sm=100,ssm=90;
    for(int i=0;i<6;i++)
    {
        if(arr[i] < sm)
        {
            ssm = sm;
            sm = arr[i];
        }else if(arr[i] < ssm && arr[i] != sm)
        {
            ssm = arr[i];
        }
    }

    printf("ssm:%d",ssm);
}

//35
void EC_Arr_W2_35()
{
    int arr[] = {-7,1,5,2,-4,3,0};
    int total=0,left=0;

    for(int i=0;i<7;i++)
        total+=arr[i];

    for(int i=0;i<7;i++)
    {
        total -= arr[i];
        if(left == total)
        {
            printf("Equilibrium index is %d",i);
            return;
        }
        left += arr[i];
    }
}


//37
void EC_Arr_W2_37()
{
    int a1[] = {1,2,3,4,5};
    int a2[] = {2,4,5};
    int found;

    for(int i=0;i<3;i++)
    {
        found = 0;
        for(int j=0;j<5;j++)
        {
            if(a2[i]==a1[j])
            {
                found = 1;
                break;
            }
        }
        if(!found)
        {
            printf("Array2 is not subset");
            return;
        }
    }
    printf("Array2 is a subset of Array1");
}

//38
void EC_Arr_W2_38()
{
    int arr[] = {0,1,2,0,1,2,1,0};
    int c0=0,c1=0,c2=0;

    for(int i=0;i<8;i++)
    {
        if(arr[i]==0) c0++;
        else if(arr[i]==1) c1++;
        else c2++;
    }

    int i=0;
    while(c0--) arr[i++]=0;
    while(c1--) arr[i++]=1;
    while(c2--) arr[i++]=2;

    printf("Sorted array: ");
    for(int j=0;j<8;j++)
        printf("%d ",arr[j]);
}


//39
void EC_Arr_W2_39()
{
    int arr[] = {1,2,3,4};
    int prod=1;

    for(int i=0;i<4;i++)
        prod *= arr[i];

    printf("Product: %d",prod);
}


//40
void EC_Arr_W2_40()
{
    int arr[] = {2,3,10,6,4,8,1};
    int min = arr[0], maxdiff = arr[1]-arr[0];

    for(int i=1;i<7;i++)
    {
        if(arr[i]-min > maxdiff)
            maxdiff = arr[i]-min;

        if(arr[i] < min)
            min = arr[i];
    }

    printf("Maximum difference: %d",maxdiff);
}

//41
void EC_Arr_W2_41()
{
    int arr[] = {1000,11,445,1,330,3000};
    int min,max,i;

    if(arr[0] > arr[1])
    {
        max = arr[0]; min = arr[1];
    }
    else
    {
        max = arr[1]; min = arr[0];
    }

    for(i=2;i<6;i++)
    {
        if(arr[i] > max)
            max = arr[i];
        else if(arr[i] < min)
            min = arr[i];
    }

    printf("Minimum element is %d Maximum element is %d",min,max);
}


//42
void EC_Arr_W2_42()
{
    int arr[] = {1,2,3,2,2,5};
    int key=2,count=0;

    for(int i=0;i<6;i++)
        if(arr[i]==key)
            count++;

    printf("Number %d occurs %d times",key,count);
}


//43
void EC_Arr_W2_43()
{
    int arr[] = {1,60,-10,70,-80,85};
    int minsum = 100000, a=0,b=0;

    for(int i=0;i<6;i++)
    {
        for(int j=i+1;j<6;j++)
        {
            int sum = arr[i]+arr[j];
            if(abs(sum) < abs(minsum))
            {
                minsum = sum;
                a = arr[i];
                b = arr[j];
            }
        }
    }

    printf("Pair whose sum is closest to zero: %d %d",a,b);
}


//44
void EC_Arr_W2_44()
{
    int arr[] = {1,2,3,-4,-1,4};
    int res[6];
    int p=0,n=0;

    for(int i=0;i<6;i++)
        if(arr[i]>=0) res[p++] = arr[i];
        else res[5-(n++)] = arr[i];

    printf("Rearranged array: ");
    for(int i=0;i<6;i++)
        printf("%d ",res[i]);
}


//45
void EC_Arr_W2_45()
{
    int arr[] = {1,0,2,0,0,3,4};
    int j=0;

    for(int i=0;i<7;i++)
    {
        if(arr[i]!=0)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            j++;
        }
    }

    printf("Output: ");
    for(int i=0;i<7;i++)
        printf("%d ",arr[i]);
}


//46
void EC_Arr_W2_46()
{
    int arr[] = {10,20,10,30,20,20,10,10};
    int visited[8]={0};

    for(int i=0;i<8;i++)
    {
        if(visited[i]) continue;
        int count=1;

        for(int j=i+1;j<8;j++)
        {
            if(arr[i]==arr[j])
            {
                count++;
                visited[j]=1;
            }
        }
        printf("%d: %d ",arr[i],count);
    }
}


//47
void EC_Arr_W2_47()
{
    int arr[] = {2,3,4,1,5,6,7};
    int k=3,sum=0,max=0;

    for(int i=0;i<k;i++)
        sum += arr[i];

    max = sum;

    for(int i=k;i<7;i++)
    {
        sum += arr[i] - arr[i-k];
        if(sum > max)
            max = sum;
    }

    printf("Maximum sum of 3 consecutive elements: %d",max);
}

//48
void EC_Arr_W2_48()
{
    int arr[] = {1,2,3,4,5};
    int k=2,n=5,temp[5];

    for(int i=0;i<n;i++)
        temp[(i+k)%n] = arr[i];

    printf("Output: ");
    for(int i=0;i<n;i++)
        printf("%d ",temp[i]);
}

//49
void EC_Arr_W2_49()
{
    int arr[] = {100,4,200,1,3,2};
    int maxlen=0;

    for(int i=0;i<6;i++)
    {
        int num = arr[i],len=1;

        for(int j=0;j<6;j++)
        {
            if(arr[j]==num-1)
                goto skip;
        }

        while(1)
        {
            int found=0;
            for(int j=0;j<6;j++)
            {
                if(arr[j]==num+1)
                {
                    num++;
                    len++;
                    found=1;
                    break;
                }
            }
            if(!found) break;
        }

        if(len>maxlen) maxlen=len;

        skip:;
    }

    printf("Longest consecutive sequence length: %d",maxlen);
}

//50
void EC_Arr_W2_50()
{
    int arr[] = {1,2,4,6};
    int n=4;
    int total = (n+2)*(n+3)/2;
    int sum=0;

    for(int i=0;i<n;i++)
        sum += arr[i];

    int s = total - sum;

    int pivot = s/2;
    int s1 = pivot*(pivot+1)/2;
    int sum1=0;

    for(int i=0;i<n;i++)
        if(arr[i]<=pivot)
            sum1 += arr[i];

    printf("Missing numbers: %d %d",s1-sum1, s-(s1-sum1));
}



int main()
{
    //EC_Arr_W2_26();
    //EC_Arr_W2_27();
    //EC_Arr_W2_28();
    //EC_Arr_W2_29();
    //EC_Arr_W2_30();
    //EC_Arr_W2_31();
    //EC_Arr_W2_32();
    //EC_Arr_W2_34();
    //EC_Arr_W2_35();
    //EC_Arr_W2_36();
    //EC_Arr_W2_38();
    //EC_Arr_W2_39();
    //EC_Arr_W2_40();
    //EC_Arr_W2_41();
    //EC_Arr_W2_42();
    //EC_Arr_W2_43();
    //EC_Arr_W2_44();

    EC_Arr_W2_48();

}
