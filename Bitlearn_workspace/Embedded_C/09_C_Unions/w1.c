#include<stdio.h>
#include <string.h>

union var
{
    int a;
    float f;
    char arr[20];
};


void EC_U_W1_1()
{
    union var v;
    printf("enter a:\n");
    scanf("%d",&v.a);
    printf("enter f:\n");
    scanf("%f",&v.f);
    printf("enter arr:\n");
    for(int i=0;i<6;i++)
    {
        scanf("%c",&v.arr[i]);
    }
    printf("v.a:%d \n v.f:%f \n v.arr[0]:%c\n",v.a,v.f,v.arr[0]);
}


void EC_STC_W1_2()
{
    printf("size of union var:%d",sizeof(union var));
}

struct st
{
    union u{
        int b;
        char c;
    }g;
    int a;
    
};
void EC_STC_W1_5()
{
    struct st var;
    printf("var.g.b:%d",var.g.b);
}


void EC_STC_W1_6()
{
    union var v;
    union var *up = &v;

    up->a = 6;
    printf("up->a:%d",up->a);
}


struct Student {
    char type; 
    union {
        int roll_number;
        char id[10];
    } data;
};

void init_roll(struct Student *s, int roll)
{
    s->type = 'r';
    s->data.roll_number = roll;
}

void init_id(struct Student *s, char *id)
{
    s->type = 'i';
    strcpy(s->data.id, id);
}

void display(struct Student s)
{
    if(s.type == 'r')
        printf("Roll Number: %d\n", s.data.roll_number);
    else
        printf("ID: %s\n", s.data.id);
}

void EC_STC_W1_7()
{
    struct Student s1, s2;

    init_roll(&s1, 101);
    init_id(&s2, "A123");

    display(s1);
    display(s2);
}



union Data {
    struct {
        int x;
        int y;
    } point;
    int val;
};

void EC_STC_W1_8()
{
    union Data d;

    d.point.x = 10;
    d.point.y = 20;

    printf("x = %d, y = %d\n", d.point.x, d.point.y);

    d.val = 50; 

    printf("val = %d\n", d.val);
    printf("After overwrite x = %d, y = %d\n", d.point.x, d.point.y);
}



union Value {
    int i;
    float f;
    char c;
};

void EC_STC_W1_9()
{
    union Value arr[3];

    arr[0].i = 10;
    arr[1].f = 5.5;
    arr[2].c = 'A';

    printf("Int: %d\n", arr[0].i);
    printf("Float: %.1f\n", arr[1].f);
    printf("Char: %c\n", arr[2].c);

    // Demonstration of overwrite
    arr[0].f = 3.14;
    printf("After overwrite Int: %d (unexpected)\n", arr[0].i);
}


struct Employee {
    int id;
    char type; // 's' salary, 'h' hourly
    union {
        float salary;
        float hourly;
    } pay;
};

void input(struct Employee *e)
{
    printf("Enter ID: ");
    scanf("%d", &e->id);

    printf("Type (s/h): ");
    scanf(" %c", &e->type);

    if(e->type == 's')
    {
        printf("Enter salary: ");
        scanf("%f", &e->pay.salary);
    }
    else
    {
        printf("Enter hourly wage: ");
        scanf("%f", &e->pay.hourly);
    }
}

void display_emp(struct Employee e)
{
    printf("ID: %d\n", e.id);

    if(e.type == 's')
        printf("Salary: %.2f\n", e.pay.salary);
    else
        printf("Hourly: %.2f\n", e.pay.hourly);
}

void EC_STC_W1_10()
{
    struct Employee e[2];

    for(int i=0;i<2;i++)
        input(&e[i]);

    for(int i=0;i<2;i++)
        display_emp(e[i]);
}




int main()
{
    //EC_U_W1_1();
    //EC_STC_W1_2();

    //EC_STC_W1_5();
    //EC_STC_W1_6();
    //EC_STC_W1_7();

    EC_STC_W1_9();

    EC_STC_W1_10();
   
}