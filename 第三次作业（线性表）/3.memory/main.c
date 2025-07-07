#include <stdio.h>
#include <stdlib.h>
struct node
{
    int place;
    int space;
    struct node *next;
};

struct node *find(struct node *first,int spa)
{
    struct node *p,*temp;
    for (p=first;p->next!=first&&p->space<spa;p=p->next)
    {
        ;
    }
    if (p->next==first)
    {
        if (p->space>=spa)
        {
            return p;
        }else
        {
            return NULL;
        }
    }
    for (temp=p->next;temp!=first;temp=temp->next)
    {
        if (temp->space>=spa&&temp->space<p->space)
        {
            p=temp;
        }
    }
    return p;
}

void freelist(struct node *first)
{
    struct node *current=first,*net;
    do
    {
        net=current->next;
        free(current);
        current=net;
    }while (current!=first);
}

int main(void)
{
    int n;
    scanf("%d",&n);
    struct node *head=NULL,*tail,*q,*first;
    for (int i=0;i<n;i++)
    {
        q=(struct node *)malloc(sizeof(struct node));
        scanf("%d %d",&q->place,&q->space);
        q->next=NULL;
        if (head==NULL)
        {
            head=tail=q;
        }else
        {
            tail->next=q;
            tail=q;
        }
    }
    tail->next=head;
    int application;
    first=head;
    while (1)
    {
        scanf("%d",&application);
        if (application==-1)
        {
            break;
        }
        q=find(first,application);
        if (q==NULL)
        {
            continue;
        }
        if (q->space==application)
        {
            if (q->next==q)
            {
                head=NULL;
                break;
            }
            first=q->next;
            for (tail=first;tail->next!=q;tail=tail->next)
            {
                ;
            }
            tail->next=first;
            free(q);
        }
        if (q->space>application)
        {
            first=q;
            first->space-=application;
        }
    }
    if (head!=NULL)
    {
        for (q=first;q->next!=first;q=q->next)
        {
            printf("%d %d\n",q->place,q->space);
        }
        if (q->next==first)
        {
            printf("%d %d\n",q->place,q->space);
            free(q);
            return 0;
        }
    }
    freelist(first);
    return 0;
}