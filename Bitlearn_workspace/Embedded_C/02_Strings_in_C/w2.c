//1
void EC_Str_W2_1()
{
    char str1[20]="hello", str2[20]="world";

    strcat(str1,str2);
    strcpy(str2,str1);
    strcpy(str1,str2 + strlen(str2)-strlen(str1));

    str2[strlen(str2)-strlen(str1)]='\0';

    printf("str1=%s str2=%s",str1,str2);
}

//2
void EC_Str_W2_2()
{
    char arr[3][20]={"John","Alice","Bob"};
    char temp[20];

    for(int i=0;i<3;i++)
    {
        for(int j=i+1;j<3;j++)
        {
            if(strcmp(arr[i],arr[j])>0)
            {
                strcpy(temp,arr[i]);
                strcpy(arr[i],arr[j]);
                strcpy(arr[j],temp);
            }
        }
    }

    for(int i=0;i<3;i++)
        printf("%s ",arr[i]);
}

//3
void EC_Str_W2_3()
{
    char s[]="madam";
    int l=0,r=strlen(s)-1;

    while(l<r)
    {
        if(s[l]!=s[r])
        {
            printf("Not Palindrome");
            return;
        }
        l++;r--;
    }
    printf("Palindrome");
}

//4
void EC_Str_W2_4()
{
    char s[]="sample string";
    int freq[256]={0},max=0;
    char ch;

    for(int i=0;s[i];i++) freq[s[i]]++;

    for(int i=0;i<256;i++)
    {
        if(freq[i]>max)
        {
            max=freq[i];
            ch=i;
        }
    }
    printf("%c",ch);
}

//5
void EC_Str_W2_5()
{
    char s[]="programming";
    int seen[256]={0},j=0;

    for(int i=0;s[i];i++)
    {
        if(!seen[s[i]])
        {
            seen[s[i]]=1;
            s[j++]=s[i];
        }
    }
    s[j]='\0';

    printf("%s",s);
}

//6
void EC_Str_W2_6()
{
    char s[]="programming";
    int freq[256]={0};

    for(int i=0;s[i];i++) freq[s[i]]++;

    for(int i=0;i<256;i++)
        if(freq[i]>1)
            printf("%c ",i);
}

//7
void EC_Str_W2_7()
{
    char s1[]="hello world", s2[]="low";
    int mark[256]={0},j=0;

    for(int i=0;s2[i];i++) mark[s2[i]]=1;

    for(int i=0;s1[i];i++)
    {
        if(!mark[s1[i]])
            s1[j++]=s1[i];
    }
    s1[j]='\0';

    printf("%s",s1);
}

//8
void EC_Str_W2_8()
{
    char s1[]="abcd", s2[]="cdab";
    char temp[50];

    strcpy(temp,s1);
    strcat(temp,s1);

    if(strstr(temp,s2))
        printf("Yes");
    else
        printf("No");
}

//9
void rev(char *s,int n)
{
    if(n<0) return;
    printf("%c",s[n]);
    rev(s,n-1);
}

void EC_Str_W2_9()
{
    char s[]="hello";
    rev(s,strlen(s)-1);
}


//10
void permute(char *s,int l,int r)
{
    if(l==r)
    {
        printf("%s ",s);
        return;
    }

    for(int i=l;i<=r;i++)
    {
        char t=s[l]; s[l]=s[i]; s[i]=t;
        permute(s,l+1,r);
        t=s[l]; s[l]=s[i]; s[i]=t;
    }
}

void EC_Str_W2_10()
{
    char s[]="ABC";
    permute(s,0,2);
}

//11
void EC_Str_W2_11()
{
    char s[]="abcdefgh";
    int n=4,len=strlen(s)/n;

    for(int i=0;i<strlen(s);i+=len)
    {
        for(int j=i;j<i+len;j++)
            printf("%c",s[j]);
        printf(" ");
    }
}

//12
void EC_Str_W2_12()
{
    char s[]="swiss";
    int freq[256]={0};

    for(int i=0;s[i];i++) freq[s[i]]++;

    for(int i=0;s[i];i++)
    {
        if(freq[s[i]]==1)
        {
            printf("%c",s[i]);
            return;
        }
    }
}

//13
int hasAll(char *w,char *str)
{
    int freq[256]={0};

    for(int i=0;w[i];i++) freq[w[i]]++;

    for(int i=0;str[i];i++) freq[str[i]]--;

    for(int i=0;i<256;i++)
        if(freq[i]>0) return 0;

    return 1;
}

void EC_Str_W2_13()
{
    char *list[]={"cat","tac","act","dog"};
    char word[]="act";

    for(int i=0;i<4;i++)
    {
        if(hasAll(word,list[i]))
            printf("%s ",list[i]);
    }
}

//14
void EC_Str_W2_14()
{
    char s[]="Hello world";
    int i=strlen(s)-1;

    while(i>=0)
    {
        int j=i;
        while(j>=0 && s[j]!=' ') j--;

        for(int k=j+1;k<=i;k++)
            printf("%c",s[k]);

        printf(" ");
        i=j-1;
    }
}



//15
void EC_Str_W2_15()
{
    char s[]="aaabbcc";

    for(int i=0;s[i];)
    {
        int count=1;
        while(s[i]==s[i+1])
        {
            count++; i++;
        }
        printf("%c%d",s[i],count);
        i++;
    }
}

//16 (Minimum window substring - simplified)
void EC_Str_W2_16()
{
    char s1[]="this is a test string", s2[]="tist";
    int freq[256]={0},count=0,start=0,min=100,begin=0;

    for(int i=0;s2[i];i++) freq[s2[i]]++;

    for(int i=0;s1[i];i++)
    {
        if(freq[s1[i]]>0) count++;
        freq[s1[i]]--;

        while(count==strlen(s2))
        {
            if(i-start+1 < min)
            {
                min=i-start+1;
                begin=start;
            }

            freq[s1[start]]++;
            if(freq[s1[start]]>0) count--;
            start++;
        }
    }

    for(int i=begin;i<begin+min;i++)
        printf("%c",s1[i]);
}

//17
void EC_Str_W2_17()
{
    char txt[]="hello world", pat[]="lo";

    for(int i=0;txt[i];i++)
    {
        int j;
        for(j=0;pat[j];j++)
        {
            if(txt[i+j]!=pat[j]) break;
        }
        if(!pat[j])
            printf("Pattern found at index %d",i);
    }
}


//18 (Rabin-Karp)
void EC_Str_W2_18()
{
    char txt[]="abcxabcdabcdabcy", pat[]="abcdabcy";
    int d=256,q=101,m=8,n=16;
    int h=1,p=0,t=0;

    for(int i=0;i<m-1;i++) h=(h*d)%q;

    for(int i=0;i<m;i++)
    {
        p=(d*p+pat[i])%q;
        t=(d*t+txt[i])%q;
    }

    for(int i=0;i<=n-m;i++)
    {
        if(p==t)
        {
            int j;
            for(j=0;j<m;j++)
                if(txt[i+j]!=pat[j]) break;
            if(j==m)
                printf("Pattern found at index %d",i);
        }

        if(i<n-m)
        {
            t=(d*(t-txt[i]*h)+txt[i+m])%q;
            if(t<0) t+=q;
        }
    }
}

//19
void EC_Str_W2_19()
{
    char s[]="abcabcbb";
    int max=0;

    for(int i=0;s[i];i++)
    {
        int visited[256]={0},len=0;

        for(int j=i;s[j];j++)
        {
            if(visited[s[j]]) break;
            visited[s[j]]=1;
            len++;
        }
        if(len>max) max=len;
    }

    printf("%d",max);
}


//20
void interleave(char *s1,char *s2,char *res,int i,int j,int k)
{
    if(!s1[i] && !s2[j])
    {
        res[k]='\0';
        printf("%s ",res);
        return;
    }

    if(s1[i])
    {
        res[k]=s1[i];
        interleave(s1,s2,res,i+1,j,k+1);
    }
    if(s2[j])
    {
        res[k]=s2[j];
        interleave(s1,s2,res,i,j+1,k+1);
    }
}

void EC_Str_W2_20()
{
    char s1[]="AB", s2[]="CD", res[10];
    interleave(s1,s2,res,0,0,0);
}


//21
void EC_Str_W2_21()
{
    char s1[]="abc", s2[]="def", s3[]="adbcef";
    int i=0,j=0,k=0;

    while(s3[k])
    {
        if(s1[i] && s3[k]==s1[i]) i++;
        else if(s2[j] && s3[k]==s2[j]) j++;
        else
        {
            printf("False");
            return;
        }
        k++;
    }

    if(!s1[i] && !s2[j])
        printf("True");
    else
        printf("False");
}



//22
void EC_Str_W2_22()
{
    char s1[]="listen", s2[]="silent";
    int count[256]={0};

    for(int i=0;s1[i];i++) count[s1[i]]++;
    for(int i=0;s2[i];i++) count[s2[i]]--;

    for(int i=0;i<256;i++)
    {
        if(count[i]!=0)
        {
            printf("False");
            return;
        }
    }
    printf("True");
}


//23
void EC_Str_W2_23()
{
    char txt[]="here is a simple example";
    char pat[]="example";
    int bad[256];

    for(int i=0;i<256;i++) bad[i]=-1;
    for(int i=0;pat[i];i++) bad[pat[i]]=i;

    int m=7,n=24;

    int s=0;
    while(s<=n-m)
    {
        int j=m-1;

        while(j>=0 && pat[j]==txt[s+j]) j--;

        if(j<0)
        {
            printf("Pattern found at index %d",s);
            return;
        }
        else
        {
            s += (j - bad[txt[s+j]] > 1) ? (j - bad[txt[s+j]]) : 1;
        }
    }
}


//24
int isPal(char *s,int i,int j)
{
    while(i<j)
        if(s[i++]!=s[j--]) return 0;
    return 1;
}

void EC_Str_W2_24()
{
    char s[]="ababbbabbababa";
    int n=14, dp[20];

    for(int i=0;i<n;i++)
    {
        if(isPal(s,0,i)) dp[i]=0;
        else
        {
            dp[i]=100;
            for(int j=0;j<i;j++)
            {
                if(isPal(s,j+1,i) && dp[j]+1 < dp[i])
                    dp[i]=dp[j]+1;
            }
        }
    }
    printf("%d",dp[n-1]);
}


//25
void EC_Str_W2_25()
{
    char s[]="babad";
    int start=0,max=1,n=5;

    for(int i=0;i<n;i++)
    {
        int l=i,r=i;
        while(l>=0 && r<n && s[l]==s[r])
        {
            if(r-l+1>max){start=l;max=r-l+1;}
            l--;r++;
        }

        l=i;r=i+1;
        while(l>=0 && r<n && s[l]==s[r])
        {
            if(r-l+1>max){start=l;max=r-l+1;}
            l--;r++;
        }
    }

    for(int i=start;i<start+max;i++)
        printf("%c",s[i]);
}



//26
int isAnagram(char *a,char *b)
{
    int c[256]={0};
    for(int i=0;a[i];i++) c[a[i]]++;
    for(int i=0;b[i];i++) c[b[i]]--;
    for(int i=0;i<256;i++) if(c[i]) return 0;
    return 1;
}

void EC_Str_W2_26()
{
    char *arr[]={"cat","tac","act","dog"};
    int used[4]={0};

    for(int i=0;i<4;i++)
    {
        if(used[i]) continue;
        printf("[ ");
        printf("%s ",arr[i]);
        used[i]=1;

        for(int j=i+1;j<4;j++)
        {
            if(!used[j] && isAnagram(arr[i],arr[j]))
            {
                printf("%s ",arr[j]);
                used[j]=1;
            }
        }
        printf("]\n");
    }
}


//27
void EC_Str_W2_27()
{
    char s[]="Hello world";
    int count=0,i=0;

    while(s[i])
    {
        if((i==0 || s[i-1]==' ') && s[i]!=' ')
            count++;
        i++;
    }
    printf("%d",count);
}

//28 (Wildcard matching)
int match(char *p,char *s)
{
    if(!*p && !*s) return 1;

    if(*p=='*')
        return match(p+1,s) || (*s && match(p,s+1));

    if(*p=='?' || *p==*s)
        return match(p+1,s+1);

    return 0;
}

void EC_Str_W2_28()
{
    char p[]="g*ks", s[]="geeks";

    if(match(p,s)) printf("Match");
    else printf("No Match");
}

//29
void EC_Str_W2_29()
{
    char s[]="1234";
    int num=0;

    for(int i=0;s[i];i++)
        num = num*10 + (s[i]-'0');

    printf("%d",num);
}


//30 (Longest Common Substring)
void EC_Str_W2_30()
{
    char s1[]="abcdxyz", s2[]="xyzabcd";
    int dp[20][20]={0},max=0,end=0;

    for(int i=1;i<=7;i++)
    {
        for(int j=1;j<=7;j++)
        {
            if(s1[i-1]==s2[j-1])
            {
                dp[i][j]=dp[i-1][j-1]+1;
                if(dp[i][j]>max)
                {
                    max=dp[i][j];
                    end=i;
                }
            }
        }
    }

    for(int i=end-max;i<end;i++)
        printf("%c",s1[i]);
}


//31
void EC_Str_W2_31()
{
    char s[]="abacb";
    char res[20];
    int j=0;

    for(int i=0;s[i];i++)
    {
        if(s[i]=='b') continue;
        if(s[i]=='a' && s[i+1]=='c')
        {
            i++;
            continue;
        }
        res[j++]=s[i];
    }
    res[j]='\0';

    printf("%s",res);
}


//32 (DP Interleaving)
void EC_Str_W2_32()
{
    char s1[]="abc", s2[]="def", s3[]="adbcef";
    int dp[10][10]={0};

    dp[0][0]=1;

    for(int i=0;i<=3;i++)
    {
        for(int j=0;j<=3;j++)
        {
            if(i>0 && s1[i-1]==s3[i+j-1])
                dp[i][j] |= dp[i-1][j];
            if(j>0 && s2[j-1]==s3[i+j-1])
                dp[i][j] |= dp[i][j-1];
        }
    }

    printf(dp[3][3] ? "True":"False");
}



//33 (First non-repeating char stream)
void EC_Str_W2_33()
{
    char s[]="aabc";
    int freq[256]={0};

    for(int i=0;s[i];i++)
    {
        freq[s[i]]++;

        for(int j=0;j<=i;j++)
        {
            if(freq[s[j]]==1)
            {
                printf("%c ",s[j]);
                break;
            }
        }
    }
}


//34
void removeDup(char *s)
{
    int n=strlen(s);
    int top=-1;

    for(int i=0;i<n;i++)
    {
        if(top>=0 && s[top]==s[i])
            top--;
        else
            s[++top]=s[i];
    }
    s[top+1]='\0';
}

void EC_Str_W2_34()
{
    char s[]="azxxzy";
    removeDup(s);
    printf("%s",s);
}


//35
void EC_Str_W2_35()
{
    char s[]="aabbcc";
    int freq[256]={0};

    for(int i=0;s[i];i++) freq[s[i]]++;

    for(int i=0;i<2;i++)
        for(int j=0;j<256;j++)
            if(freq[j]>0)
            {
                printf("%c",j);
                freq[j]--;
            }
}


//36
void EC_Str_W2_36()
{
    char s[]="aabababa";
    int freq[256]={0};

    for(int i=0;s[i];i++) freq[s[i]]++;

    int max=0,smax=0;
    char ch=' ';

    for(int i=0;i<256;i++)
    {
        if(freq[i]>max)
        {
            smax=max;
            max=freq[i];
        }
        else if(freq[i]>smax && freq[i]!=max)
        {
            smax=freq[i];
            ch=i;
        }
    }
    printf("%c",ch);
}

int main()
{
    //EC_Str_W2_1();
    //EC_Str_W2_2();
    //EC_Str_W2_3();
    //EC_Str_W2_4();
    //EC_Str_W2_5();
    //EC_Str_W2_6();
    //EC_Str_W2_7();
    //EC_Str_W2_8();
    //EC_Str_W2_9();
    //EC_Str_W2_10();
    //EC_Str_W2_11();
    //EC_Str_W2_12();
    //EC_Str_W2_13();
    //EC_Str_W2_14();

}