#include <cstdio>

using namespace std;

int n;

int mat[260][260];
int longest[260][260];

const inline int max(const int &a,const int &b)
{
    return a >= b ? a : b;
}

void show(int what[260][260])
{
    int i,j;
    for(i=1;i<=n;++i,printf("\n"))
        for(j=1;j<=n;++j)
            printf("%d ",what[i][j]);
}

int main()
{
    int i,j,k;

    freopen("rf.in","r",stdin);
    freopen("rf.out","w",stdout);

    scanf("%d",&n);

    for(i=1;i<=n;++i)
        for(j=1;j<=n;++j)
        {
            scanf("%d",&mat[i][j]);
            if(i!=j)
                longest[i][j]=1;
        }

    for(k=1;k<=n;++k)
    {
        for(i=1;i<=n;++i)
        {
            for(j=1;j<=n;++j)
            {
                if(mat[i][k] && mat[k][j] && i != j)
                {
                    if(mat[i][k] + mat[k][j] < mat[i][j] || !mat[i][j])
                    {
                        mat[i][j] = mat[i][k] + mat[k][j];
                        longest[i][j] = longest[i][k] + longest[k][j] ;
                    }
                    else if(mat[i][k] + mat[k][j] == mat[i][j])
                        longest[i][j] = max(longest[i][j],longest[i][k] + longest[k][j] );
                }
            }
        }
    }
    show(mat);
    show(longest);
    return 0;
}
