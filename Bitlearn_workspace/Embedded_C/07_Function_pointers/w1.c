#include<stdio.h>
#include<math.h>
#include<string.h>

/*Mathematical Operations with Function Pointers */
int add(int a,int b)
{
    printf("add called\n");
    return (a+b);
}
int sub(int a,int b)
{
    printf("sub called\n");
    return (a-b);
}
int prod(int a,int b)
{
    printf("prod called\n");
    return (a*b);
}

void EC_FP_W1_1()
{
    char ch;
    int a = 4,b=3;
    int (*fn)(int,int)=NULL;

    printf("enter choice:\n");
    scanf("%c",&ch);
    switch(ch)
    {
        case 'a':
            fn=add; 
            printf("sum:%d\n",(*fn)(a,b)); 
            break;
        case 's': 
            fn=sub;
            printf("sum:%d\n",(*fn)(a,b)); 
            break;
        case 'p': 
            fn=prod;
            printf("sum:%d\n",(*fn)(a,b));
            break;
        default:
            printf("enter btw a or s or p\n");
    }

}

/*Sorting Algorithms Selector */
void bubble(int *a,int b)
{
    printf("bubble called\n");
    int tmp;
    for(int i=b-1;i>0;i--)
    {
        for(int j=0;j<b;j++)
        {
            if(a[j] > a[j+1])
            {
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
}
void selection(int *a,int b)
{
    printf("selection called\n");int min,tmp;
    for(int i=0;i<b-1;i++)
    {
        min = i;
        for(int j=i+1;j<b;j++)
        {
            if(a[j] < a[min])
            {
               min = j;

            }
        }
        tmp = a[i];
        a[i] = a[min];
        a[min] = tmp;
    }
    
}
void insertion(int *a,int b)
{
    printf("insertion called\n");
    for(int i=1;i<b;i++)
    {
        int key = a[i];
        int j=i-1;

        while(j>=0 && a[j] > key)
        {
            a[j+1] = a[j];
            j=j-1;
        }
        a[j+1] =key;
    }
}

void print_arr(int *a,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
}

void EC_FP_W1_2()
{
    char ch;
    int a[] = {4,5,2,6,4},n=5;
    void (*fn)(int *,int)=NULL;

    printf("enter choice:\n");
    scanf("%c",&ch);
    switch(ch)
    {
        case 'b':
            fn=bubble; 
            (*fn)(a,n); print_arr(a,n); 
            break;
        case 's': 
            fn=selection;
            (*fn)(a,n); print_arr(a,n); 
            break;
        case 'i': 
            fn=insertion;
            (*fn)(a,n); print_arr(a,n);
            break;
        default:
            printf("enter btw a or s or p\n");
    }

}



/*Callback Function Array Processing */

void print_array(int *a,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
}

void increment(int *a,int s)
{
    printf("increment called\n");
    for(int i=0;i<s;i++)
    {
        a[i]++;
    }
}
void doubleValue(int *a,int s)
{
    printf("doubleValue called\n");
    for(int i=0;i<s;i++)
    {
        a[i] *= 2;
    }
}
void processArray(int *arr,int size,void (*fn)(int*,int))
{
    printf("\nproccess array called\n");
    (*fn)(arr,size);
    print_array(arr,size);

}

void EC_FP_W1_3()
{
    int arr[] = {4,5,2,6,4},n=5; 
    processArray(arr,n,increment);
    processArray(arr,n,doubleValue);
}

/*Menu-driven Calculator Using Function Pointers */
//void (*fptr[3])(int*,int);//-->FUNCTION pointer array

void power(int a, int pw )
{
    printf("called power:%lf\n",pow(a,pw));
}

void modulo(int a, int b)
{
    printf("called modulo:%d",a%b);
}

void sqt(int a,int dummy)
{
    printf("called sqrt:%lf",sqrt((double)a));
}

void (*fptr[3])(int,int) = { 0 };
void EC_FP_W1_4()
{
    char ch;
    int a=3,b=2;

    printf("enter choice:\n");
    scanf("%c",&ch);
    switch(ch)
    {
        case 'p':
            fptr[0]=power;
            fptr[0](a,b);  
            break;
        case 'm': 
            fptr[1]=modulo;
            fptr[1](a,b);  
            break;
        case 's': 
            fptr[2]=sqt;
            fptr[2](a,b); 
            break;
        default:
            printf("enter btw p or m or s\n");
    }
}



/*Generic find implementaion*/
void  iseven(int *arr, int s)
{
    for(int i=0;i<s;i++)
    {
        if(arr[i]%2 == 0)
        {
            printf("its even\n");
            return;
        }
            
    }
    printf("even not found\n");
    
}

void ispositive(int *arr, int s)
{
    for(int i=0;i<s;i++)
    {
        if(arr[i] > 0)
        {
            printf("its positive\n");
            return;
        }
            
    }
    printf("positive not found\n");
    
}

void isprime(int *arr, int s)
{
    int flag=0;
    for(int i=0;i<s;i++)
    {
        flag = 0;
        for(int j=2;j<arr[i];j++)
        {
            if(arr[i]%j == 0)
            {
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            printf("has prime");
            return;
        }     
    }
    printf("prime not found\n");
    
}

void find(int *arr, int s, void (*fptr)(int *arr,int s))
{
    fptr(arr,s);
}

void EC_FP_W1_8()
{
    int arr[] = {-4,5,2,6,4},n=5;
    find(arr,n,isprime);
    find(arr,n,ispositive);
    find(arr,n,iseven);

}


/*Function pointer as return value*/
void add2(int a,int b)
{
    printf("add:%d",a+b);
}

void sub2(int a,int b)
{
    printf("add:%d",a+b);
}

void mul2(int a,int b)
{
    printf("add:%d",a+b);
}

void (*getOperation(char *op))(int a, int b)//returns function ptr
{
    if(strcmp(op,"add") == 0)
    {
        return add2;
    }else if(strcmp(op,"sub") == 0)
    {
        return sub2;
    }else if(strcmp(op,"mul") == 0)
    {
        return mul2;
    }
}

void EC_FP_W1_11()
{
    void (*fn)(int,int) = NULL;
    fn = getOperation("add");
    fn(3,4);
}

/*Multidimentional function pointer array*/
void intAdd(int a,int b)
{
    printf("intadd:%d",a+b);
}

void floatAdd(int a,int b)
{
    printf("floatadd:%d",a+b);
}

void floatAdd_B(int a,int b)
{
    printf("flaotaddB:%d",a+b);
}

void intAdd_B(int a,int b)
{
    printf("intaddB:%d",a^b);
}

/*
                int     float
    arthmatic   00       01

    bitwise     10      11

*/
void (*fnptr[2][2])(int ,int) = {
    {intAdd,intAdd_B},
    {floatAdd,floatAdd_B}
};

void EC_FP_W1_15()
{
    int i,j;
    printf("enter i and j values\n");
    scanf("%d %d",&i,&j);

    fnptr[i][j](4,6);
}

void EC_FP_W1_16()
{
    int fact_func(int);
    
    int (*fp)(int);   
    fp = fact_func;

    int fact_func(int n)
    {
        if(n <= 1)
            return 1;
        return n * fp(n - 1);
    }

    int n = 5;
    printf("Factorial of %d = %d\n", n, fp(n));
}

int add(int a,int b){ return a+b; }
int sub(int a,int b){ return a-b; }
int mul(int a,int b){ return a*b; }

struct Calculator
{
    int (*op[3])(int,int);
};

void EC_FP_W1_17()
{
        struct Calculator calc;

    calc.op[0] = add;
    calc.op[1] = sub;
    calc.op[2] = mul;

    int a = 10, b = 5;

    printf("Add: %d\n", calc.op[0](a,b));
    printf("Sub: %d\n", calc.op[1](a,b));
    printf("Mul: %d\n", calc.op[2](a,b));
}

void cmd1(){ 
    printf("Command 1 executed\n"); 
}
void cmd2(){ 
    printf("Command 2 executed\n"); 
}
void cmd3(){ 
    printf("Command 3 executed\n"); 
}

void EC_FP_W1_18()
{
        void (*cmd_table[3])();

    cmd_table[0] = cmd1;
    cmd_table[1] = cmd2;
    cmd_table[2] = cmd3;

    int cmd = 2; // simulate input

    if(cmd >=0 && cmd <3)
        cmd_table[cmd]();
    else
        printf("Invalid command\n");
}

int main()
{
    //EC_FP_W1_1();
    //EC_FP_W1_2();

    //EC_FP_W1_3();

    
    //EC_FP_W1_4();

    //EC_FP_W1_8();

    //EC_FP_W1_11();

    EC_FP_W1_15();
}