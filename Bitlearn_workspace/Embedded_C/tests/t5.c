//prg for nth highest frequency char in string
#include<stdio.h>
#include<stdlib.h>
struct char_map
{
    int cnt;
    char ch;
};

void Kth_high_freq_char()
{
    char str[] = "success";int k=2;
    char freq[256] = {0};

    for(int i=0;str[i] != '\0';i++)
    {
        freq[(unsigned int)str[i]]++;
    }

    struct char_map *ar_ch=NULL;int ct =0;

    for(int i=0;str[i] != '\0';i++)
    {
        ar_ch = realloc(ar_ch,sizeof(struct char_map)*(ct+1));
        ar_ch[ct].ch = str[i];
        ar_ch[ct].cnt = freq[str[i]];
        ct++;
    }
     
    //sort by freq cnt
    struct char_map tmp;

    for(int i=ct-1;i>0;i--)
    {
        for(int j=0;j<ct-1;j++)
        {
            if(ar_ch[j].cnt < ar_ch[j+1].cnt)
            {
                tmp = ar_ch[j];
                ar_ch[j] = ar_ch[j+1];
                ar_ch[j+1] = tmp;

            }
        }
    }

    printf("%dth most frequent char is:%c",k,ar_ch[k].ch);

}

int main()
{
    Kth_high_freq_char();
}