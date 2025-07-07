#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct book {
    char name[23];
    char num[12];
};
int main()
{
    int n;
    scanf("%d",&n);
    struct book people[n];
    for(int i=0;i<n;i++){
        for(int j=0;j<23;j++){
            people[i].name[j]='\0';
        }
        for(int j=0;j<12;j++){
            people[i].num[j]='\0';
        }
    }
    for(int i=0;i<n;i++){
        scanf("%s",people[i].name);
        scanf("%s",people[i].num);
    }
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(strcmp(people[i].name,people[j].name)==0){
                if(strcmp(people[i].num,people[j].num)==0){
                    people[j].name[0]='\0';
                }
            }
        }
    }
    char index='1';
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(strcmp(people[i].name,people[j].name)==0){
                int g=strlen(people[j].name);
                people[j].name[g]='_';
                people[j].name[g+1]=index;
                index++;
            }
        }
        index='1';
    }

    for(int i=0;i<n-1;i++){
        int p=i;
        for(int j=i+1;j<n;j++){
            if(strcmp(people[j].name,people[p].name)<0){
                p=j;
            }
        }
        if(p!=i){
            struct book temp;
            strcpy(temp.name,people[i].name);
            strcpy(temp.num,people[i].num);

            strcpy(people[i].name,people[p].name);
            strcpy(people[i].num,people[p].num);

            strcpy(people[p].name,temp.name);
            strcpy(people[p].num,temp.num);
        }
    }
    for(int i=0;i<n;i++){
        if(people[i].name[0]!='\0'&&people[i].name[0]!='_'){
            printf("%s %s\n",people[i].name,people[i].num);
        }
    }


    return 0;
}