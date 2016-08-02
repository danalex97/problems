#include <cstdio>
#include <cstring>
using namespace std;


int N[2010];
int C[2010];
int REZ[20010];
char s[1005];

void mul()
{
    int i,j,t;
    for(i=1;i<=N[0];++i)
    {
        for(t=0,j=1;j<=C[0] || t;j++,t/=10)
            REZ[i+j-1] = (t+= REZ[i+j-1] + N[i] * C[j])%10;
        if(i+j-2 > REZ[0])
            REZ[0] = i+j-2;
    }
}

int main()
{
    freopen("sosete.in","r",stdin);
    freopen("sosete.out","w",stdout);
    //((N-2)*2-1)*C+1;
    scanf("%s",s);
    int len = strlen(s);
    N[0] = len;
    int i;
    for(i=len;i>=1;--i)
        N[i] = s[len-i]-'0';
    scanf("%s",s);
    len = strlen(s);
    C[0] = len;
    for(i=len;i>=1;--i)
        C[i] = s[len-i]-'0';
    if(N[1] >= 2)
        N[1]-=2;
    else
    {
        N[1] += 8;
        for(i=2;!N[i] && i <= N[0];N[i]=9,++i);
        --N[i];
        if(!N[i])
            --N[0];
    }
    int t;
    for(i=1,t=0;i<=N[0] || t;i++,t/=10)
        N[i] = (t+= (N[i]<<1))%10;
    N[0]=i-1;
    if(N[1] >= 1)
        N[1]-=1;
    else
    {
        N[1] += 9;
        for(i=2;!N[i] && i <= N[0];N[i]=9,++i);
        --N[i];
        if(!N[i])
            --N[0];
    }




    mul();
    if(REZ[1] <= 8)
        ++REZ[1];
    else
    {
        REZ[1]=0;
        for(i=2;REZ[i]==9;REZ[i]=0,++i);
        ++REZ[i];
        if(i > REZ[0])
            REZ[0]=i;
    }
    for(i=REZ[0];i;--i)
        printf("%d",REZ[i]);
    return 0;
}
