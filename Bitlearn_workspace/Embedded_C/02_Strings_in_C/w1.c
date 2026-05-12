#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Program: Reverse order of words in a given string
          Input: "hello world from C"

         Output: "C from world hello"*/
void EC_Str_W1_1()
{
    char str[] = "hello world from C";

    char *ptr;int cnt=0;
    char **aptr=NULL;
    ptr = strtok(str," ");

    while(ptr != NULL)
    {
        aptr = realloc(aptr,sizeof(char *)*(cnt+1));
        aptr[cnt++] = ptr;
        ptr = strtok(NULL," ");
    }

    for(int i=cnt-1;i>=0;i--)
    {
        printf("%s ",aptr[i]);
    }
}

/*Program: Remove all repeated characters from a given string
         Input: "programming"

        Output: "progamin"*/
void EC_Str_W1_2()
{
    char str[] = "programming";
    int l = strlen(str);
    for(int i=0;i<l-1;i++)
    {
        for(int j=i+1;j<l;j++)
        {
            if(str[i] == str[j])
            {
                memmove(str+j,str+j+1,strlen(str+j+1)+1);
            }
        }
    }
    printf("%s",str);
}

/* Program: Find highest frequency character in a string
          Input: "engineering"

          Output: 'e' appears 3 times*/

void EC_Str_W1_3()
{
    char str[] = "engineering";
    int l = strlen(str),cnt,max=0,ind;
    for(int i=0;i<l-1;i++)
    {
        cnt=1;
        for(int j=i+1;j<l;j++)
        {
            if(str[i] == str[j])
            {
                cnt++;
            }
        }
        if(cnt > max)
        {
            max = cnt;
            ind = i;
        }
    }
    printf("%c appears %d times\n",str[ind],max);
}


/*Program: Find lowest frequency character in a string
          Input: "engineering"

         Output: 'g', 'r', 'n' each appear once*/

void EC_Str_W1_4()
{
    char str[] = "engineering";
    char occ[126]={0};
    for(int i=0;str[i];i++)
    {
        occ[(unsigned int)str[i]]++;
    }
    for(int i=0;i<126;i++)
    {
        if(occ[i] == 1)
            printf("%c ",i);
    }
    printf(" each appear once");
}

/*Program: Reverse a string without using library functions
         Input: "OpenAI"

         Output: "IAnepO"
*/

void EC_Str_W1_5()
{
    char arr[] = "OpenAi";
    int l = strlen(arr);char t;

    for(int i=0,j=l-1;i<j;i++,j--)
    {
        t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
    printf("%s",arr);
}

/*Program: Remove all extra blank spaces from a given string
         Input: " This is ChatGPT "

         Output: "This is ChatGPT"*/

void EC_Str_W1_6()
{
    char str[] = " This is ChatGPT ";
    int i=0;

    while(str[i] != '\0')
    {
        if(i==0 && str[i] == ' ')
        {
            memmove(str,str+1,strlen(str+1)+1);
        }
        if(str[i] == ' ' && str[i+1] == ' ')
        {
            memmove(str+i,str+i+1,strlen(str+i+1)+1);
            i--;
        }
        i++;
    }
    str[i-1] = 0;

    printf("%s ",str);
}

/* Program: Replace all occurrences of a character with another in a string
         Input: "banana", replace 'a' with 'o'

         Output: "bonono"*/

void EC_Str_W1_7()
{
    char str[] = "banana";int i=0;
    while(str[i] != '\0')
    {
        if(str[i] == 'a')
        {
            str[i] = 'o';
        }
        i++;
    }
    printf("%s",str);
}

/*Program: Count frequency of each character in a string
         Input: "success"

         Output:
          s = 3
         u = 1
         c = 2
         e = 1*/
void EC_Str_W1_8()
{
    char str[] = "success";int cnt=1;
    char freq[126] = {0};
    for(int i=0;str[i] != '\0';i++)
    {
        freq[str[i]]++;
    }

    for(int i=0;i<126;i++)
    {
        if(freq[i] > 0)
        {
            printf("%c = %d\n",i,freq[i]);
        }
    }
}

/* Program: Find first occurrence of a word in a given string
         Input: "this is a test string", word: "test"

         Output: Found at position 11
*/
void EC_Str_W1_9()
{
    char str[] = "this is a test string";
    char word[] = "test";

    char *ptr = strstr(str,word);
    printf("Found at position %d",(ptr-str)+1);
}

/*Program: Remove all occurrence of a word in given string
           Input: "hello world hello universe", remove: "hello"

          Output: "world universe"*/
void EC_Str_W1_10()
{
    char str[] = "hello world hello universe";
    char rm[] = "hello";
    char *fnd;
    while(fnd != NULL)
    {
        fnd = strstr(str,rm);
        if(fnd != NULL)
            memmove(fnd,fnd+strlen(rm)+1,strlen(fnd+strlen(rm)+1)+1);
    }
    printf("%s",str);
}

/*Program: Count total number of words in a string
          Input: "C programming is fun"

          Output: 4*/

void EC_Str_W1_11()
{
    char str[] = "C programming is fun";
    int cnt=0;
    char *ptr;
    ptr = strtok(str," ");
    if(ptr != NULL)
        cnt =1;
    while(ptr != NULL)
    {
        ptr = strtok(NULL," ");
        if(ptr != NULL)
        {
            cnt++;
        }
    }
    printf("%d",cnt);
}


/*Program: Toggle case of each character of a string
         Input: "HeLLo"

         Output: "hEllO"*/

void EC_Str_W1_12()
{
    char str[] = "HeLLo";

    for(int i=0;str[i] != '\0';i++)
    {
        if(str[i] >= 97 && str[i] <= 122)
        {
            str[i] = (str[i]-32);
        }
        else if(str[i] >= 65 && str[i] <= 90)
        {
            str[i] += 32;
        }
        
    }

    printf("%s",str);
}

/*Program: Remove last occurrence of a character from string
          Input: "mississippi", remove 's'

          Output: "missipippi"*/
void EC_Str_W1_13()
{
    char str[] =  "mississippi";
    char rm = 's';
    int l = strlen(str);

    for(int i=l-1;i>=0;i--)
    {
        if(str[i] == rm)
        {
            memmove(str+i,str+i+1,strlen(str+i+1)+1);
            break;
        }
    }
    printf("%s",str);
}


/* Program: Replace first occurrence of a character with another in a string
         Input: "google", replace 'o' with 'a'

         Output: "gagole"*/
void EC_Str_W1_14()
{
    char str[] = "google";
    char rs = 'a';

    /*for(int i=0;str[i] != '\0';i++)
    {
        if(str[i] == 'o')
            str[i] = 'a';
    }*/
    char *ptr;
    while(ptr != NULL)
    {
        ptr = strchr(str,'o');
        if(ptr)
            *ptr = rs;
    }

    printf("%s",str);

}


/*Program: Count occurrences of a word in a given string
          Input: "hi hello hi hey hi", word: "hi"

         Output: 3*/
void EC_Str_W1_15()
{
    char str[] = "hi hello hi hey hi";
    char word[] =  "hi";

    int cnt=0;
    char *ptr=strtok(str," ");
    while(ptr != NULL)
    {
        if(strcmp(ptr,word) == 0)
            cnt++;
        ptr = strtok(NULL," ");
       
    }
    printf("%d",cnt);
}


/*Program: Check whether a string is palindrome or not
        Input: "madam"

       Output: "Palindrome"*/
void EC_Str_W1_16()
{
    char str[] = "madam";
    int l = strlen(str);
    int i,j;
    for(i=0,j=l-1;i<j;i++,j--)
    {
        if(str[i] != str[j])
        {
            break;
        }
    }
    if(i<j)
        printf("Not palindrome\n");
    else
        printf("Palindorme\n");
}

/*Program: Find last occurrence of a character in a string
        Input: "ababcabc", find 'b'

        Output: Position: 6*/
void EC_Str_W1_17()
{
    char str[] = "ababcabc";
    char f = 'b';

    char *p = strrchr(str,f);

    printf("%d",(p-str));
}

/*Program: Trim both leading and trailing white space characters from given string
        Input: " Hello World "

        Output: "Hello World*/

void EC_Str_W1_18()
{ 
    char str[] = "   Hello World   ";
    int i=0,j=strlen(str)-1;
    while(str[i] == ' ')
    {
        memmove(str+i,str+i+1,strlen(str+i+1)+1);
        i--;
        i++;

    }

    while(str[j] == ' ')
    {
        memmove(str+j-1,str+j,strlen(str+j)+1);
        j--;
        j++;
    }
    printf("%s",str);
}



/*Program: Find first occurrence of a character in a given string
       Input: "elephant", find 'e'

        Output: Position: 0*/
void EC_Str_W1_19()
{
    char str[] = "elephant";
    char f = 'e';

    printf("Position:%d",(strchr(str,f)-str));
}

/*Program: Find all occurrences of a word in given string
        Input: "the sky is the limit in the sky", search "the"

       Output: Found at positions: 0, 15, 30*/
void EC_Str_W1_20()
{
    char str[] = "the sky is the limit in the sky";
    char find[] = "the";

    char *ptr=strtok(str," ");
    printf("found at positions:");
    while(ptr != NULL)
    {
        if(strcmp(ptr,find) == 0)
        {
            printf("%d ",(ptr-str));
        }
        ptr = strtok(NULL," ");
       
    }
}






int main()
{
    //EC_Str_W1_1();
    //EC_Str_W1_2();
    //EC_Str_W1_3();
    //EC_Str_W1_4();
    //EC_Str_W1_5();

    //EC_Str_W1_6();

    //EC_Str_W1_7();

    //EC_Str_W1_8();

    //EC_Str_W1_9();

    //EC_Str_W1_10();

    //EC_Str_W1_11();

    //EC_Str_W1_12();

    //EC_Str_W1_13();
    //EC_Str_W1_14();

    //EC_Str_W1_15();

    //EC_Str_W1_16();

    //EC_Str_W1_17();

    //EC_Str_W1_18();
    //EC_Str_W1_19();

    EC_Str_W1_20();

}