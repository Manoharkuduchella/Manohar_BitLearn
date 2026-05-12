#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//multiply two strings numbers
void mul_strings()
{
    char str1[] = "12345678", str2[] = "98765432";

    int s1,s2;
    s1 = strlen(str1);
    s2 = strlen(str2);

    char res[s1+s2+1];
    int k=(s1+s2-1);

    int d1,d2,prod,p1,p2,sum;

    //initialize with zeros in res
    for(int i=0;i<(s1+s2);i++)
    {
        res[i] = 0;
    }

    for(int i=s1-1;i>=0;i--)
    {
        for(int j=s2-1;j>=0;j--)
        {
            d1 = str1[i] - '0';
            d2 = str2[j] - '0';

            prod = d1*d2;

            p1 = i+j;
            p2 = i+j+1;

            sum = prod + res[p2];

            res[p1] += sum/10;
            res[p2] = sum%10;
        }
    }
    
    //skip leading zeros
    int start =0;
    while(start < s1+s2 && res[start] == 0)
        start++;

    int r1 = (s1+s2) - start;
    char *mul_val = (char*)malloc(r1+1);

    int a=0;
    while(start < (s1+s2))
    {
        mul_val[a++] = res[start]+'0';
        start++;
    }
    mul_val[k] =0;


    //print result as str
    printf("prod: %s",mul_val);
}



//rotate string in k positions

void rot_str()
{
    int arr[5] = {2,4,3,6,7};
    int k=2;

    int tmp,t;
    for(int j=0;j < k;j++)
    {
        t = arr[4];
        for(int i=4;i>0;i--)
        {
            arr[i] = arr[i-1];
        }
        arr[0] = t;
    }

    printf("print array\n");
    for(int z = 0; z < 5; z++)
    {
        printf("%d ",arr[z]);
    }
}

int main()
{
    //rot_str();
    mul_strings();
}

