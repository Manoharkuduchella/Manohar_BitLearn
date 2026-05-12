#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Make a new file and save some text entered by the user.
Input: File name: test.txt
Text: Hello, this is my first file!
Output: File 'test.txt' created and saved.*/
void EC_FH_W1_1(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Wrong cmd try: ./a.exe file_name Input_text");
        return;
    }

    FILE *fptr=NULL;

    fptr = fopen(argv[1],"w");
    if(fptr == NULL)
    {
        printf("error in file creation\n");
    }
    int cnt = strlen(argv[2]);
    if(fwrite(argv[2],sizeof(char),cnt+1,fptr)==(cnt+1))
    {
        printf("File %s created and saved\n",argv[1]);
    }

}

/*Open an existing file and display its contents on the screen.
Input: File name: test.txt
Output: Hello, this is my first file!*/
void EC_FH_W1_2(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("Wrong cmd try: ./a.exe file_name");
        return;
    }

    FILE *fptr=NULL;

    fptr = fopen(argv[1],"r");
    if(fptr == NULL)
    {
        printf("error in opening file\n");
    }
    char str[30];
    if(fread(str,sizeof(char),30,fptr) > 0)
    {
        printf("%s",str);
    }

}

/*Take several lines from the user and write all of them into a file.
Input: File name: lines.txt
Number of lines: 3
Lines: Line one, Line two, Line three
Output: All lines saved in 'lines.txt'.*/
void  EC_FH_W1_3(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("Wrong cmd try: ./a.exe file_name");
        return;
    }
    FILE *fptr =NULL;

    fptr = fopen(argv[1],"w");
        if(fptr == NULL)
    {
        printf("error in opening file\n");
    }
    int l_num;char buf[10];
    printf("enter a noof line:\n");
    scanf("%d",&l_num);


    while(l_num--)
    {
        printf("enter a line:\n");
        fflush(stdin);
        fgets(buf,10,stdin);

        if(fwrite(buf,sizeof(char),9,fptr) <= 0)
        {
            printf("written failed\n");
        }
    }
    printf("All line saved in %s",argv[1]);

}

/*Read every line from a file and store those lines in an array.*/
void EC_FH_W1_4(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("Wrong cmd try: ./a.exe file_name");
        return;
    }
    FILE *fptr =NULL;

    fptr = fopen(argv[1],"r");
        if(fptr == NULL)
    {
        printf("error in opening file\n");
    }
    char (*buff)[10]=NULL;int cnt=0;

    while(1)
    {
        buff = realloc(buff,sizeof(*buff)*((cnt)+1));
        if(fgets(buff[cnt++],10,fptr) == NULL)
        {
            break;
        }
    }
    for(int i=0;i<cnt-1;i++)
    {
        printf("%s\n",buff[i]);
    }
   
}


void EC_FH_W1_5(int argc,char *argv[])
{
    if(argc < 3)
    {
        printf("Usage: ./a.out file line1 line2 ...\n");
        return;
    }

    FILE *fp = fopen(argv[1],"a");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    for(int i=2;i<argc;i++)
        fprintf(fp,"%s\n",argv[i]);

    fclose(fp);
}


void EC_FH_W1_6(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./a.out src dest\n");
        return;
    }

    FILE *src = fopen(argv[1],"r");
    FILE *dest = fopen(argv[2],"w");

    if(!src || !dest)
    {
        printf("File error\n");
        return;
    }

    char ch;
    while((ch=fgetc(src))!=EOF)
        fputc(ch,dest);

    fclose(src);
    fclose(dest);
}


void EC_FH_W1_7(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./a.out file\n");
        return;
    }

    if(remove(argv[1])==0)
        printf("File deleted\n");
    else
        printf("Delete failed\n");
}


void EC_FH_W1_8(int argc,char *argv[])
{
    if(argc != 2) return;

    FILE *fp = fopen(argv[1],"r+");
    int num;

    fscanf(fp,"%d",&num);
    printf("Read: %d\n",num);

    rewind(fp);
    fprintf(fp,"%d",100);

    fclose(fp);
}


void EC_FH_W1_9(int argc,char *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    int count=0;
    char ch;

    while((ch=fgetc(fp))!=EOF)
        if(ch=='\n') count++;

    printf("Lines: %d\n",count+1);
    fclose(fp);
}


void EC_FH_W1_10(int argc,char *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    int words=0,chars=0;
    char ch,prev=' ';

    while((ch=fgetc(fp))!=EOF)
    {
        chars++;
        if(ch==' '||ch=='\n') words++;
        prev=ch;
    }

    printf("Words:%d Characters:%d\n",words+1,chars);
}


void EC_FH_W1_11(int argc,char *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    char ch; int count=0;

    while((ch=fgetc(fp))!=EOF)
    {
        putchar(ch);
        if(ch=='\n') count++;
    }

    printf("\nTotal lines:%d\n",count+1);
}


void EC_FH_W1_12(int argc,char *argv[])
{
    int line = atoi(argv[2]);
    FILE *fp = fopen(argv[1],"r");
    FILE *temp = fopen("temp.txt","w");

    char buf[100]; int count=1;

    while(fgets(buf,100,fp))
    {
        if(count!=line)
            fputs(buf,temp);
        count++;
    }

    fclose(fp); fclose(temp);
    remove(argv[1]);
    rename("temp.txt",argv[1]);
}


void EC_FH_W1_13(int argc,char *argv[])
{
    int line = atoi(argv[2]);
    FILE *fp = fopen(argv[1],"r");
    FILE *temp = fopen("temp.txt","w");

    char buf[100]; int count=1;

    while(fgets(buf,100,fp))
    {
        if(count==line)
            fprintf(temp,"%s\n",argv[3]);
        else
            fputs(buf,temp);
        count++;
    }

    fclose(fp); fclose(temp);
    remove(argv[1]);
    rename("temp.txt",argv[1]);
}

void EC_FH_W1_14(int argc,char *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    FILE *temp = fopen("temp.txt","w");

    char word[100];

    while(fscanf(fp,"%s",word)!=EOF)
    {
        if(strcmp(word,argv[2])==0)
            fprintf(temp,"%s ",argv[3]);
        else
            fprintf(temp,"%s ",word);
    }

    fclose(fp); fclose(temp);
    remove(argv[1]);
    rename("temp.txt",argv[1]);
}


void EC_FH_W1_15(int argc,char *argv[])
{
    FILE *fp = fopen(argv[1],"r+");
    char ch;

    while((ch=fgetc(fp))!=EOF)
    {
        fseek(fp,-1,SEEK_CUR);
        fputc(toupper(ch),fp);
    }
}

void EC_FH_W1_16(int argc,char *argv[])
{
    FILE *fp = fopen(argv[1],"r+");
    char ch;

    while((ch=fgetc(fp))!=EOF)
    {
        fseek(fp,-1,SEEK_CUR);
        fputc(tolower(ch),fp);
    }
}

void EC_FH_W1_17(int argc,char *argv[])
{
    FILE *fp = fopen(argv[1],"r+");
    char ch,prev=' ';

    while((ch=fgetc(fp))!=EOF)
    {
        if(prev==' ')
        {
            fseek(fp,-1,SEEK_CUR);
            fputc(toupper(ch),fp);
        }
        prev=ch;
    }
}


void EC_FH_W1_18(int argc,char *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    char buf[100][100];
    int i=0;

    while(fgets(buf[i],100,fp)) i++;

    for(int j=i-1;j>=0;j--)
        printf("%s",buf[j]);
}

void EC_FH_W1_19(int argc,char *argv[])
{
    FILE *fp = fopen(argv[1],"r+");
    char ch;

    while((ch=fgetc(fp))!=EOF)
    {
        fseek(fp,-1,SEEK_CUR);
        fputc(ch+3,fp);
    }
}

void EC_FH_W1_20(int argc,char *argv[])
{
    FILE *fp = fopen(argv[1],"r+");
    char ch;

    while((ch=fgetc(fp))!=EOF)
    {
        fseek(fp,-1,SEEK_CUR);
        fputc(ch-3,fp);
    }
}

void EC_FH_W1_21(int argc,char *argv[])
{
    FILE *f1=fopen(argv[1],"r");
    FILE *f2=fopen(argv[2],"r");
    FILE *f3=fopen(argv[3],"w");

    char ch;

    while((ch=fgetc(f1))!=EOF) fputc(ch,f3);
    while((ch=fgetc(f2))!=EOF) fputc(ch,f3);
}


void EC_FH_W1_22(int argc,char *argv[])
{
    FILE *f1=fopen(argv[1],"r");
    FILE *f2=fopen(argv[2],"r");
    FILE *f3=fopen(argv[3],"w");

    char a[100],b[100];

    while(fgets(a,100,f1)||fgets(b,100,f2))
    {
        if(a) fputs(a,f3);
        if(b) fputs(b,f3);
    }
}

void EC_FH_W1_23(int argc,char *argv[])
{
    FILE *f1=fopen(argv[1],"a");
    FILE *f2=fopen(argv[2],"r");

    char ch;
    while((ch=fgetc(f2))!=EOF)
        fputc(ch,f1);
}


void EC_FH_W1_24(int argc,char *argv[])
{
    FILE *f1=fopen(argv[1],"r");
    FILE *f2=fopen(argv[2],"r");

    char c1,c2;

    while(1)
    {
        c1=fgetc(f1);
        c2=fgetc(f2);

        if(c1!=c2)
        {
            printf("Different\n");
            return;
        }
        if(c1==EOF) break;
    }
    printf("Identical\n");
}

void EC_FH_W1_25(int argc,char *argv[])
{
    FILE *fp=fopen(argv[1],"r");
    fseek(fp,0,SEEK_END);
    printf("Size:%ld\n",ftell(fp));
}

void EC_FH_W1_25(int argc,char *argv[])
{
    FILE *fp=fopen(argv[1],"r");
    fseek(fp,0,SEEK_END);
    printf("Size:%ld\n",ftell(fp));
}


void EC_FH_W1_27(int argc,char *argv[])
{
    FILE *fp=fopen(argv[1],"r");
    char buf[100];
    int count=0;

    while(fgets(buf,100,fp))
    {
        if(buf[0]=='\n') count++;
    }

    printf("Blank lines:%d\n",count);
}





int main(int argc,char *argv[])
{

    //EC_FH_W1_1(argc,argv);
    //EC_FH_W1_2(argc,argv);

    //EC_FH_W1_3(argc,argv);
    //EC_FH_W1_4(argc,argv);
    //EC_FH_W1_5(argc,argv);
    //EC_FH_W1_6(argc,argv);
    //EC_FH_W1_8(argc,argv);
    //EC_FH_W1_9(argc,argv);
    //EC_FH_W1_10(argc,argv);
    //EC_FH_W1_11(argc,argv);
    //EC_FH_W1_12(argc,argv);

    //EC_FH_W1_13(argc,argv);
    //EC_FH_W1_14(argc,argv);
    //EC_FH_W1_15(argc,argv);
    //EC_FH_W1_16(argc,argv);
    //EC_FH_W1_17(argc,argv);
    //EC_FH_W1_18(argc,argv);
    //EC_FH_W1_19(argc,argv);
    EC_FH_W1_22(argc,argv);


    return 0;
}