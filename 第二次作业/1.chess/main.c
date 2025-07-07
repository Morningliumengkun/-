#include <stdio.h>
int judge(int chess[][19],int num)
{
    int i,j;
    int flag=0;
    for (i=0;i<19;i++)
    {
        for (j=0;j<16;j++)
        {
            if (chess[i][j]==num&&chess[i][j+1]==num&&chess[i][j+2]==num&&chess[i][j+3]==num)
            {
                if (j!=0&&chess[i][j-1]==0)
                {
                    flag=1;
                    printf("%d:%d,%d\n",num,i+1,j+1);
                    break;
                }
                if (j!=15&&chess[i][j+4]==0)
                {
                    flag=1;
                    printf("%d:%d,%d\n",num,i+1,j+1);
                    break;
                }
            }
        }
    }

    for (j=0;j<19;j++)
    {
        for (i=0;i<16;i++)
        {
            if (chess[i][j]==num&&chess[i+1][j]==num&&chess[i+2][j]==num&&chess[i+3][j]==num)
            {
                if (i!=0&&chess[i-1][j]==0)
                {
                    flag=1;
                    printf("%d:%d,%d\n",num,i+1,j+1);
                    break;
                }
                if (i!=15&&chess[i+4][j]==0)
                {
                    flag=1;
                    printf("%d:%d,%d\n",num,i+1,j+1);
                    break;
                }
            }
        }
    }

    for (i=0;i<16;i++)
    {
        for (j=0;j<16;j++)
        {
            if (chess[i][j]==num&&chess[i+1][j+1]==num&&chess[i+2][j+2]==num&&chess[i+3][j+3]==num)
            {
                if (i!=0&&j!=0&&chess[i-1][j-1]==0)
                {
                    flag=1;
                    printf("%d:%d,%d\n",num,i+1,j+1);
                    break;
                }
                if (i!=15&&j!=15&&chess[i+4][j+4]==0)
                {
                    flag=1;
                    printf("%d:%d,%d\n",num,i+1,j+1);
                    break;
                }
            }
        }
    }

    for (j=18;j>2;j--)
    {
        for (i=0;i<16;i++)
        {
            if (chess[i][j]==num&&chess[i+1][j-1]==num&&chess[i+2][j-2]==num&&chess[i+3][j-3]==num)
            {
                if (i!=0&&j!=18&&chess[i-1][j+1]==0)
                {
                    flag=1;
                    printf("%d:%d,%d\n",num,i+1,j+1);
                    break;
                }
                if (i!=15&&j!=3&&chess[i+4][j-4]==0)
                {
                    flag=1;
                    printf("%d:%d,%d\n",num,i+1,j+1);
                    break;
                }
            }
        }
    }

    if (flag==1)
    {
        return 1;
    }else
    {
        return 0;
    }
}
int main(void)
{
    int chess[19][19]={0};
    for (int i=0;i<19;i++)
    {
        for (int j=0;j<19;j++)
        {
            scanf("%d",&chess[i][j]);
        }
    }
    int judge1=judge(chess,1);
    int judge2=judge(chess,2);
    if (judge1==0&&judge2==0)
    {
        printf("No\n");
    }
    return 0;
}