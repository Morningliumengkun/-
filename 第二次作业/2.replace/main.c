#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char lower(char c){
    if(c>='a'&&c<='z'){
        return c;
    }
    if(c>='A'&&c<='Z'){
        return c-'A'+'a';
    }
    return c;
}


int main()
{
    FILE *in,*out;
    in=fopen("filein.txt","r");
    out=fopen("fileout.txt","w");
    char s[1024]={'\0'},t[1024]={'\0'},m[1024]={'\0'};
    gets(s);
    gets(t);
    int k=0,j;
    while((fgets(m,50,in))!=NULL){
        int i=0;
        while(m[i]!='\0'){
            for( j=i,k=0;m[j]!='\0'&&s[k]!='\0';j++,k++){
                if(lower(m[j])!=s[k]){
                    break;
                }
            }
            if(s[k]=='\0'){
                i=j;
                fputs(t,out);
            }else{
                fprintf(out,"%c",m[i]);
                i++;}
        }

    }

    fclose(in);
    fclose(out);

    return 0;
}