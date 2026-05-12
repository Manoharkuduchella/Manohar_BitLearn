#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{

    /*
    //find it is a 64 or 32 bit cpu
    if(sizeof(int*)==8)
        printf("its a 64\n");
    else if(sizeof(int*) == 4)
        printf("its a 32\n");
    */

    /*
    //right rotate bits of a number
    int r=2,num=0x00000003;
    printf("before:%x\n",num);
    num=(num>>r)|(num<<(32-r));
    printf("after:%x\n",num);
    */

    /*find count of duplicates
    Input: int arr[10] = {1,10,20,1,25,1,10,30,25,1};
    Output: 5*/
    /*int arr[10] = {1,10,20,1,25,1,10,30,25,1};
    int cnt=0;
    for(int i=0;i<10;i++)
    {
        for(int j=i+1;j<10;j++)
        {
            if(arr[i] == arr[j])
            {
                cnt++;
                break;
            }
        }
    }
    printf("count:%d",cnt);*/

    //remove the repeated words
    //input: str[] = "red blue green red yellow blue"
    //Output: "red blue green yellow"

    char str[31] = "red blue green red yellow blue";

    char *ptr = str;int cnt=0;
    char **aptr=NULL;

    ptr = strtok(str," ");
    while(ptr != NULL)
    {
        //printf("%s\n",ptr);
        
        aptr = realloc(aptr,sizeof(char *)*((cnt)+1));

        aptr[cnt++] = ptr;

        ptr = strtok(NULL," ");
    }

    for(int i=0;i<cnt;i++)
    {
        if(aptr[i]==NULL)
            continue;
            
        for(int j=i+1;j<cnt;j++)
        {
            if(aptr[j] && strcmp(aptr[i],aptr[j])==0)
            {
                aptr[j] = NULL;
            }
        }
    }

    printf("after removal:");
    for(int i=0;i<cnt;i++)
    {
        if(aptr[i] != NULL)
            printf("%s ",aptr[i]);
    }


    




}