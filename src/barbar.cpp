#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    char k;
    int len = 0;
    int cuv = 0;
    bool cuvant = 0;
    freopen("text.in","r",stdin);
    freopen("text.out","w",stdout);
    while(scanf("%c",&k)!=EOF)
    {
        if((k>='a' && k <= 'z') || (k>='A' && k<='Z'))
        {
            ++len;
            if(cuvant==0)
            {
                cuvant=1;
                ++cuv;
            }
        }
        else
            cuvant=0;
    }
    cout << len/cuv;
    return 0;
}
