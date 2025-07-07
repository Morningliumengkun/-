#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int same_string(char *str,int index)
{
    for (int i=0;i<index;i++)
    {
        if (str[i]==str[index])
        {
            return 1;
        }
    }
    return 0;
}

int same(char *str,char *code,int index)
{
    int len=strlen(str);
    for (int i=0;i<len;i++)
    {
        if (code[index]==str[i])
        {
            return 1;
        }
    }
    return 0;
}

struct node
{
    char c;
    struct node *next;
    struct node *pre;
    int n;
};

struct node *find_node(struct node zu[],int circle,struct node *head)
{
    for (int i=0;i<circle-1;i++)
    {
        head=head->next;
    }
    return head;
}
int main()
{
    char str[96]={'\0'};
    fgets(str,96,stdin);
    int len=strlen(str);
    str[len-1]='\0';
    for (int i=0;str[i]!='\0';i++)
    {
        if (same_string(str,i))
        {
            for (int j=i;str[j]!='\0';j++)
            {
                str[j]=str[j+1];
            }
            i--;
        }
    }
    char code[96]={'\0'},final[96]={'\0'};
    for (int i=32;i<127;i++)
    {
        code[i-32]=i;
    }
    for (int i=0;i<95;i++)
    {
        if (same(str,code,i))
        {
            for (int j=i;code[j]!='\0';j++)
            {
                code[j]=code[j+1];
            }
            i--;
        }
    }
    strcat(str,code);
    struct node zu[95];
    for (int i=0;i<95;i++)
    {
        zu[i].c=str[i];
        zu[i].n=1;
    }
    for (int i=0;i<94;i++)
    {
        zu[i].next=&zu[i+1];
    }
    for (int i=94;i>0;i--)
    {
        zu[i].pre=&zu[i-1];
    }
    zu[94].next=&zu[0];
    zu[0].pre=&zu[94];
    struct node *head=&zu[0];
    struct node *temp,*q;
    int index=0,circle=0;
    for (int i=0;i<94;i++)
    {
        index=head->c-' ';
        circle=head->c;
        temp=head;
        head=head->next;
        q=temp->pre;
        q->next=head;
        head->pre=q;
        head=find_node(zu,circle,head);
        final[index]=head->c;
        head->n=0;
    }
    final[head->c-' ']=zu[0].c;
    FILE *in,*out;
    in=fopen("in.txt","r");
    out=fopen("in_crpyt.txt","w");
    char tem[512]={'\0'};
    while (fgets(tem,512,in)!=NULL)
    {
        for (int i=0;tem[i]!='\0';i++)
        {
            if (tem[i]>=32&&tem[i]<=126)
            {
                int k=tem[i]-32;
                fprintf(out,"%c",final[k]);
            }else
            {
                fprintf(out,"%c",tem[i]);
            }
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}