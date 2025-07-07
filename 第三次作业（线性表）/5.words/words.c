#include <stdio.h>
#include<ctype.h>
#include<string.h>
#define MAX 1024
int N=0;
struct lnode
{
    char word[32];
    int count;
};
int getWord(FILE *in,char w[])
{
    int c,i=0;
    while (!isalpha(c=fgetc(in))){
        if (c==EOF)
            return c;
}
        do
        {
            w[i++]=tolower(c);
        }while (isalpha(c=fgetc(in)));
    w[i]='\0';
    return 1;
}

int insertWord(struct lnode list [],int pos,char *w)
{
    int i;
    if (N==MAX)
        return -1;
    for (i=N-1;i>=pos;i--)
    {
        list[i+1]=list[i];
    }
    strcpy(list[pos].word,w);
    list[pos].count=1;
    N++;
    return 1;
}

int searchWord(struct lnode list[],char w[])
{
    int low=0,high=N-1,mid=0;
    while (low<=high)
    {
        mid=(low+high)/2;
        if (strcmp(w,list[mid].word)<0)
            high=mid-1;
        else if (strcmp(w,list[mid].word)>0)
            low=mid+1;
        else
        {
            list[mid].count++;
            return 0;
        }
    }
    return insertWord(list,low,w);
}

int main(void)
{
struct lnode wordlist[1024],word[32];
    FILE *in=fopen("article.txt","r");
    while (getWord(in,word)!=EOF)
        if (searchWord(wordlist,word)==-1)
        {
            return -1;
        }
    for (int i=0;i<N;i++)
    {
        printf("%s %d\n",wordlist[i].word,wordlist[i].count);
    }
    fclose(in);
    return 0;
}
