#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
字符串编辑距离(Edit Distance)，是俄罗斯科学家Vladimir Levenshtein提出的概念。两个字符串之间的最小距离就是指把一个字符串转换为另一个字符串时，所需要的最小编辑操作(插入、删除、替换)的次数。
编辑操作包含以下3种：
替换（substitution），将一个字符替换为另一个字符
插入（insertion），插入一个字符
删除（deletion），删除一个字符
下面给出了一个基于动态规划算法的编辑距离计算函数editdistDP 的C语言实现，该函数参数为2个字符串，返回值为2个字符串的编辑距离，函数实现如下：
*/
#define max2(a,b) ((a)>(b)?(a):(b))
int **Dp, MaxDP=3300;								//for dynamic programming
int min3(int a, int b, int c)
{
    int min = a < b ? a : b;
    return min < c ? min : c;
}
int error2(char *s)
{
    fprintf(stderr,"%s\n",s);
    exit(-1);
}
int initDP()
{
    int i;
    Dp = (int **)malloc(MaxDP*sizeof(int *));
    for(i=0; i<MaxDP; i++)
    Dp[i] = (int *)malloc(MaxDP*sizeof(int));
	return 0;
}
int editdistDP(char *str1, char *str2)
{
    int i,j;
    int len1, len2;
    static int flag=0;

    (flag++) ? 1 : initDP();
    len1 = strlen(str1)+1; len2 = strlen(str2)+1;
    (max2(len1,len2)>=MaxDP) ? error2("DP memory error!") : len1;
    for (i=0; i<=len1; i++) {
        for (j=0; j<=len2; j++) {
            if (i==0)
                Dp[i][j] = j;
            else if (j==0)
                Dp[i][j] = i;
            else if (str1[i-1] == str2[j-1])
                Dp[i][j] = Dp[i-1][j-1];
            else
                Dp[i][j] = 1 + min3(Dp[i][j-1], Dp[i-1][j], Dp[i-1][j-1]);
        }
    }
    return Dp[len1][len2];
}
#define MAX_DICT_SIZE 500000
#define MAX_LEN 30
#define MAX_WORD_NUM 100000
char dictionary[MAX_DICT_SIZE][MAX_LEN];//存储字典
typedef struct _node
{
    char s[512];
    struct _node *next;
    int dis;
}node;

node right_gram[100000];
node wrong_gram[10000];
int is_punctutation(char c)
{
    if ((c>=33&&c<=47)||(c>=58&&c<=64)||(c>=91&&c<=96)||(c>=123&&c<=126))
    {
        return 1;
    }
    return 0;
}
int isInDictionary(char word[],int Snum) {
    int left=0,right=Snum-1,mid;
    while (left<=right)
    {
        mid=(left+right)/2;
        int cmp=strcmp(word,dictionary[mid]);
        if (cmp==0)return 1;
        else if (cmp<0)right=mid-1;
        else left=mid+1;
    }
    return 0;
}
int right_gram_num=0,wrong_gram_num=0;
int find_right_gram(char word[])
{
   for (int i=0;i<right_gram_num;i++)
   {
       if (strcmp(right_gram[i].s,word)==0)
       {
           return i;
       }
   }
    return -1;
}
void insert_right_gram(char pre_word[],char word[])
{
    int index=find_right_gram(pre_word);
    if (index==-1)
    {
        strcpy(right_gram[right_gram_num].s,pre_word);
        node *p=(node *)malloc(sizeof(node));
        strcpy(p->s,word);p->next=NULL;
        right_gram[right_gram_num].next=p;
        right_gram_num++;
        return;
    }else
    {
        node *p=(node *)malloc(sizeof(node));
        strcpy(p->s,word);p->next=NULL;
        node *q=right_gram[index].next;
        if (strcmp(q->s,word)==0)return;
        if (strcmp(q->s,word)>0)
        {
            right_gram[index].next=p;
            p->next=q;
            return;
        }
        while (q->next!=NULL)
        {
            if (strcmp(q->s,word)==0)return;
            if (strcmp(q->s,word)>0)
            {
                node *temp;
                for (temp=right_gram[index].next;temp!=q&&temp->next!=q;temp=temp->next)
                {
                    ;
                }
                p->next=temp->next;
                temp->next=p;
                return;
            }
            q=q->next;
        }
        if (strcmp(q->s,word)<0)
        {
            q->next=p;return;
        }
        if (strcmp(q->s,word)==0)return;
        node *temp;
        for (temp=right_gram[index].next;temp->next!=q;temp=temp->next)
        {
            ;
        }
        p->next=temp->next;
        temp->next=p;
        return;
    }
}
void insert_wrong_gram(char pre_word[],char word[])
{
    if (word[0]=='\0')return;
    for (int i=0;i<wrong_gram_num;i++)
    {
        if (strcmp(wrong_gram[i].s,pre_word)==0&&strcmp(wrong_gram[i].next->s,word)==0)return;
    }
    strcpy(wrong_gram[wrong_gram_num].s,pre_word);
    node *p=(node *)malloc(sizeof(node));
    strcpy(p->s,word);p->next=NULL;
    wrong_gram[wrong_gram_num].next=p;
    wrong_gram_num++;
}
typedef struct no
{
    char s[512];
    int dis;
}wor;
int main(void)
{
    char s[1024]={'\0'},word[MAX_LEN]={'\0'};
    int Snum=0;//Snum记录字典行数
    FILE *fp=fopen("in.txt","r");
    FILE *dic=fopen("dict.txt","r");
    while (fscanf(dic,"%s",word)!=EOF)
    {
        for (int i=0;word[i]!='\r'&&word[i]!='\0'&&word[i]!='\n';i++)
        {
            dictionary[Snum][i]=word[i];
        }
        Snum++;
    }
    while (fgets(s,1024,fp)!=NULL)
{
    int i = 0;
    node *cur_head = NULL, *cur_tail = NULL;
    while (1) {
        // 跳过所有连续的空格
        while (s[i] == ' ') i++;
        // 读单词
        char temp[512] = {'\0'};
        int j = 0;
        while (isalpha(s[i])) {
            temp[j++] = tolower(s[i]);
            i++;
        }
        temp[j] = '\0';

        // 若读到了单词则建节点
        if (j > 0) {
            node *p = (node *)malloc(sizeof(node));
            strcpy(p->s, temp);
            p->next = NULL;
            if (cur_head == NULL) cur_head = cur_tail = p;
            else { cur_tail->next = p; cur_tail = p; }
        }

        // 若遇到标点（非字母且非空格），则处理2-gram并清空链表
        if (s[i] != '\0' && s[i] != ' ' && !isalpha(s[i])) {
            // 处理2-gram
            for (node *t = cur_head; t && t->next; t = t->next) {
                node *w = t->next;
                if (isInDictionary(t->s, Snum)) {
                    if (isInDictionary(w->s, Snum))
                        insert_right_gram(t->s, w->s);
                    else
                        insert_wrong_gram(t->s, w->s);
                }
            }
            // 清空链表
            node *tmp;
            while (cur_head) {
                tmp = cur_head;
                cur_head = cur_head->next;
                free(tmp);
            }
            cur_tail = NULL;
            i++;
            continue;
        }

        // 行结束
        if (s[i] == '\0' || s[i] == '\r' || s[i] == '\n') {
            // 处理2-gram
            for (node *t = cur_head; t && t->next; t = t->next) {
                node *w = t->next;
                if (isInDictionary(t->s, Snum)) {
                    if (isInDictionary(w->s, Snum))
                        insert_right_gram(t->s, w->s);
                    else
                        insert_wrong_gram(t->s, w->s);
                }
            }
            // 清空链表
            node *tmp;
            while (cur_head) {
                tmp = cur_head;
                cur_head = cur_head->next;
                free(tmp);
            }
            cur_tail = NULL;
            break;
        }
        i++;
    }
}
    for (int i=0;i<wrong_gram_num;i++)
      {
        char print_word[1000][30]={'\0'};
        int index=find_right_gram(wrong_gram[i].s),number=0;
        if (index==-1)
        {
            printf("%s: %s -> ",wrong_gram[i].s,wrong_gram[i].next->s);
            printf("No suggestion\n");
            continue;
        }
        char word_temp[MAX_LEN]={'\0'};strcpy(word_temp,wrong_gram[i].next->s);
        int j=0,g=0;
        for (node *k=right_gram[index].next;k!=NULL;k=k->next)
        {
            k->dis=editdistDP(word_temp,k->s);
            j++;
        }
        int min=right_gram[index].next->dis;
        for (node *k=right_gram[index].next;k!=NULL&&g<j;k=k->next,g++)
        {
            if (min>k->dis)min=k->dis;
        }
        printf("%s: %s -> ",wrong_gram[i].s,word_temp);
        g=0;
        for (node *k=right_gram[index].next;k!=NULL&&g<j;k=k->next,g++)
        {
            if (min==k->dis)
            {
                strcpy(print_word[number],k->s);
                number++;
            }
        }
        for (int k=0;k<number-1;k++)
        {
            printf("%s,",print_word[k]);
        }
        printf("%s\n",print_word[number-1]);
      }
    return 0;
}
