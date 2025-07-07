#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int coe;
    int pow;
    struct Node *next;
};
struct fx
{
    int coe;
    int pow;
    int index;
};
int main()
{
    int a,n,sum1=0,sum2=0;
    char c;
    struct Node *p,*head1,*q,*head2;
    head1=p=head2=NULL;
    do
    {
        scanf("%d%d%c",&a,&n,&c);
        q=(struct Node*)malloc(sizeof(struct Node));
        q->coe=a,q->pow=n;
        q->next=NULL;
        if (head1==NULL)
        {
            head1=p=q;
        }else{
            p->next=q;
            p=p->next;
        }
        sum1++;
    }while (c!='\n');
    p=NULL;
    do
    {
        scanf("%d%d%c",&a,&n,&c);
        q=(struct Node*)malloc(sizeof(struct Node));
        q->coe=a,q->pow=n;
        q->next=NULL;
        if (head2==NULL)
        {
            head2=p=q;
        }else{
            p->next=q;
            p=p->next;
        }
        sum2++;
    }while (c!='\n');
    int len=sum1*sum2,total=0;
    struct  fx zu[len];
    int k=0;
    for (p=head1;p!=NULL;p=p->next)
    {
        for (q=head2;q!=NULL;q=q->next)
        {
            zu[k].coe=p->coe*q->coe;
            zu[k].pow=(p->pow)+(q->pow);
            zu[k].index=1;
            k++;
        }
    }
    for (int i=0;i<len;i++)
    {
        for (int j=i+1;j<len;j++)
        {
            if (zu[i].pow==zu[j].pow)
            {
                zu[j].index=0;
            }
        }
    }
    for (int i=0;i<len;i++)
    {
        if (zu[i].index==1)
        {
            total++;
        }
    }
    struct fx result[total];
    for (int i=0;i<total;i++)
    {
        for (int j=i;j<len;j++)
        {
            if (zu[j].index==1)
            {
                result[i].coe=zu[j].coe;
                result[i].pow=zu[j].pow;
                zu[j].index=-1;
                break;
            }
            if (zu[j].index==0)
            {
                for (int k=0;k<total;k++)
                {
                    if (result[k].pow==zu[j].pow)
                    {
                        result[k].coe=result[k].coe+zu[j].coe;
                        break;
                    }
                }
                zu[j].index=-1;
            }
        }
    }
     for (int i=0;i<total;i++)
     {
         int kom=i;
         for (int j=i+1;j<total;j++)
         {
             if (result[kom].pow<result[j].pow)
             {
                 kom=j;
             }
         }
         if (i!=kom)
         {
           struct fx temp=result[kom];
           result[kom]=result[i];
             result[i]=temp;
        }
     }
    for (int i=0;i<total;i++)
    {
        printf("%d %d ",result[i].coe,result[i].pow);
    }
    return 0;
}
