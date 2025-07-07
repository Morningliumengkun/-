#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void delete_char(char s[]){
    int n=strlen(s);
    for(int i=0;i<n&&s[i]!='\0';i++){
        for(int j=i+1;j<n;j++){
            if(s[j]==s[i]){
                for(int k=j;k<n;k++){
                    s[k]=s[k+1];
                }
                j--;
                s[n]='\0';
            }
        }
    }
}

char *new_letter(char s[],char letter[]){
    char *newletter=(char*)malloc(27*sizeof(char));
    for(int i=0;i<27;i++){
        newletter[i]='\0';
    }
    int n=strlen(s);
    strncpy(newletter,s,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<26;j++){
            if(letter[j]==s[i]){
                letter[j]='A';
                break;
            }
        }
    }
    for(int i=n,j=0;i<26&&j<26;j++){
        if(letter[j]!='A'){
            newletter[i++]=letter[j];
        }
    }
    int  index;
    char mid;
    for(int i=n;i<26;i++){
        index=i;
        for(int j=i+1;j<26;j++){
            if(newletter[j]>newletter[i]){
                index=j;
            }
        }
        if(i!=index){
            mid=newletter[i];
            newletter[i]=newletter[index];
            newletter[index]=mid;
        }
    }
    return newletter;
}

int main()
{
    FILE *in,*out;
    in=fopen("encrypt.txt","r");
    out=fopen("output.txt","w");
    char letter[27]={'\0'},s[80]={'\0'};
    for(int i=0;i<26;i++){
        letter[i]='a'+i;
    }
    gets(s);
    delete_char(s);
    char *newlet=new_letter(s,letter);
    int  c;
    while((c=fgetc(in))!=EOF){

        if((c>='a'&&c<='z')){
            char m=c;
            int index=m-'a';
            m=newlet[index];
            fprintf(out,"%c",m);
        }else{
            fprintf(out,"%c",c);
        }


    }
    fclose(in);
    fclose(out);
    return 0;
}