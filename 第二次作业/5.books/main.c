#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char name[51];
    char author[31];
    char publisher[51];
    char date[21];
};
int compare_books(const void *a, const void *b) {
    struct node *bookA = (struct node *)a;
    struct node *bookB = (struct node *)b;
    return strcmp(bookA->name, bookB->name);
}
void insert_book(struct node books[],int *count,char *name,char *author,char *publisher,char *date)
{
    int k=*count;
    strcpy(books[k].name,name);
    strcpy(books[k].author, author);
    strcpy(books[k].publisher, publisher);
    strcpy(books[k].date, date);
    (*count)++;
    qsort(books, *count, sizeof(struct node), compare_books);
}
void find_book(struct node books[],int count,char keyword[])
{
    for (int i=0;i<count;i++)
    {
        if (strstr(books[i].name, keyword)!=NULL)
        {
            printf("%s %s %s %s\n",books[i].name,books[i].author,books[i].publisher,books[i].date);
        }
    }
}
void delete_books(struct node books[], int *count, const char *keyword) {
    int new_count = 0;
    for (int i = 0; i < *count; i++) {
        if (strstr(books[i].name, keyword) == NULL) {
            books[new_count] = books[i];
            new_count++;
        }
    }
    *count = new_count;
    qsort(books, *count, sizeof(struct node), compare_books);
}
int main()
{
    FILE *in,*out;
    in=fopen("books.txt","r");
    out=fopen("ordered.txt","w");
    struct node books[501];
    struct node input;
    int count=0;
    while (fscanf(in,"%50s %30s %50s %20s",input.name,input.author,input.publisher,input.date)!=EOF)
    {
        strcpy(books[count].name,input.name);
        strcpy(books[count].author,input.author);
        strcpy(books[count].publisher,input.publisher);
        strcpy(books[count].date,input.date);
        count++;
    }
    qsort(books,count,sizeof(struct node),compare_books);
    int choice;
    while (1)
    {
        scanf("%d",&choice);
        if (choice==0)
        {
            for (int i=0;i<count;i++)
            {
                fprintf(out,"%-50s%-20s%-30s%-10s\n",books[i].name,books[i].author,books[i].publisher,books[i].date);
            }
            break;
        }
        char name[50]={'\0'},author[30]={'\0'},publisher[50]={'\0'},date[20]={'\0'};
        char keyword[101]={'\0'};
        if (choice==1)
        {
            scanf("%50s %30s %50s %20s",name,author,publisher,date);
            insert_book(books,&count,name,author,publisher,date);
        }
        if (choice==2)
        {
            scanf("%s",keyword);
            find_book(books,count,keyword);
        }
        if (choice==3)
        {
            scanf("%s",keyword);
            delete_books(books,&count,keyword);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
