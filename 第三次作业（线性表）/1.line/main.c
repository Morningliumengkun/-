#include <stdio.h>
struct dot
{
    int x;
    int y;
};
struct line
{
    struct dot v1;
    struct dot v2;
    struct line *next;
    struct line *pre;
};
int main(void)
{
    int n;
    scanf("%d",&n);
    struct line zu[n];
    for (int i=0;i<n;i++)
    {
        scanf("%d%d",&zu[i].v1.x,&zu[i].v1.y);
        scanf("%d%d",&zu[i].v2.x,&zu[i].v2.y);
        zu[i].next=NULL;
        zu[i].pre=NULL;
    }
    for (int i=0;i<n;i++)
    {
        int index=i;
        for (int j=i+1;j<n;j++)
        {
            if (zu[index].v1.x>zu[j].v1.x)
            {
                index=j;
            }
            if (zu[index].v1.x==zu[j].v1.x)
            {
                if (zu[index].v1.y<zu[j].v1.y)
                {
                    index=j;
                }
            }
        }
        if (index!=i)
        {
            struct line temp=zu[index];
            zu[index]=zu[i];
            zu[i]=temp;
        }
    }
    for (int i=0;i<n;i++)
    {
        for (int j=i+1;j<n;j++)
        {
            if (zu[i].v2.x==zu[j].v1.x&&zu[i].v2.y==zu[j].v1.y)
            {
                zu[i].next=&zu[j];
                zu[j].pre=&zu[i];
                break;
            }
        }
    }
    int sum=0;
    for (int i=0;i<n;i++)
    {
        if (zu[i].next==NULL)
        {
            sum++;
        }
    }
    int a[sum];
    for (int i=0,j=0;i<n;i++)
    {
        if (zu[i].pre==NULL)
        {
            a[j]=i;
            j++;
        }
    }
    int total[sum];
    struct line *p=NULL;
    int m=0;
    int TOT=1;
    for (int i=0;i<sum;i++)
    {
        m=a[i];
        p=zu[m].next;
        while (p!=NULL)
        {
            p=p->next;
            TOT++;
        }
        total[i]=TOT;
        TOT=1;
    }
    int max=total[0],biao=0;
    for (int i=0;i<sum;i++)
    {
        for (int j=i+1;j<sum;j++)
        {
            if (max<total[j])
            {
                max=total[j];
                biao=j;
            }
        }
    }
    m=a[biao];
    printf("%d %d %d",max,zu[m].v1.x,zu[m].v1.y);
    return 0;
}