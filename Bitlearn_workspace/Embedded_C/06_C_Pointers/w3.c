#include <stdio.h>
#include <stdint.h>
void EC_CP_W3_1()
{
    int arr[5] = {10,20,30,40,50};
    int *ptr = arr;

    printf("Array address: %p\n", arr);
    printf("Pointer address: %p\n", ptr);
    printf("Address of array: %p\n", &arr);

    printf("sizeof(arr) = %lu\n", sizeof(arr));
    printf("sizeof(ptr) = %lu\n", sizeof(ptr));

    for(int i=0;i<5;i++)
        printf("%d %d\n", arr[i], *(ptr+i));
}



void EC_CP_W3_2()
{
    int sensors[3][3] = {
        {100,101,102},
        {110,111,112},
        {120,121,122}
    };

    int *p = &sensors[0][0];

    for(int i=0;i<9;i++)
        printf("%d ", *(p+i));
}




#define REG_BASE 0x40000000

void EC_CP_W3_3()
{
    volatile uint32_t *reg_modifiable = (uint32_t *)REG_BASE;
    const uint32_t *reg_readonly = (const uint32_t *)REG_BASE;
    const volatile uint32_t *reg_cv = (const volatile uint32_t *)REG_BASE;

    *reg_modifiable = 10;  
    printf("%u\n", *reg_modifiable);

    
    printf("%u\n", *reg_readonly);

   
    printf("%u\n", *reg_cv);
}




void mem_copy(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;

    for(size_t i=0;i<n;i++)
        d[i] = s[i];
}

void EC_CP_W3_4()
{
    int a[3] = {1,2,3}, b[3];
    mem_copy(b,a,sizeof(a));

    for(int i=0;i<3;i++)
        printf("%d ", b[i]);
}



struct A {
    char status;
    int control;
    short error;
};

struct __attribute__((packed)) B {
    char status;
    int control;
    short error;
};

void EC_CP_W3_5()
{
    printf("Size A: %lu\n", sizeof(struct A));
    printf("Offsets A: %lu %lu %lu\n",
           offsetof(struct A,status),
           offsetof(struct A,control),
           offsetof(struct A,error));

    printf("Size B: %lu\n", sizeof(struct B));
}





void init(){ printf("Init\n"); }
void start(){ printf("Start\n"); }
void stop(){ printf("Stop\n"); }

void EC_CP_W3_6()
{
    void (*cmd_table[])() = {init,start,stop};

    int cmd = 1;
    cmd_table[cmd]();
}




int* allocate_buffer()
{
    int *buf = (int*)malloc(10*sizeof(int));
    return buf;
}

void EC_CP_W3_7()
{
    int *p = allocate_buffer();

    free(p);

    
    printf("%d\n", p[0]); 
}





void EC_CP_W3_8()
{
    int rows=4, cols=4;

    int **reg_block = malloc(rows*sizeof(int*));

    for(int i=0;i<rows;i++)
        reg_block[i] = malloc(cols*sizeof(int));

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            reg_block[i][j] = i*10+j;

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
            printf("%d ", reg_block[i][j]);
        printf("\n");
    }

    for(int i=0;i<rows;i++)
        free(reg_block[i]);
    free(reg_block);
}




typedef int (*CalibArrayPtr)[10];

CalibArrayPtr get_data()
{
    static int arr[10] = {0,1,2,3,4,5,6,7,8,9};
    return &arr;
}

void EC_CP_W3_9()
{
    CalibArrayPtr p = get_data();

    for(int i=0;i<10;i++)
        printf("%d ", (*p)[i]);
}



struct Peripheral {
    uint8_t status;
    uint8_t control;
    uint16_t data;
};

void EC_CP_W3_10()
{
    struct Peripheral arr[5];
    struct Peripheral *p = arr;

    for(int i=0;i<5;i++)
    {
        (p+i)->status = i;
        (p+i)->control = i+1;
        (p+i)->data = i+100;
    }

    for(int i=0;i<5;i++)
        printf("%d %d %d\n",
               (p+i)->status,
               (p+i)->control,
               (p+i)->data);
}


