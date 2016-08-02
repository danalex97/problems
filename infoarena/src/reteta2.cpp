#include <fstream>
using namespace std;
long long int S;
long long v[1005];
long long maxM,max1,max2;
int       indM,ind1,ind2;
int n;
ifstream in("expresie.in");
ofstream out("expresie.out");
int main()
{
    int i;
    in >> n;
    for(i=1;i<=n;++i)
    {
        in >> v[i];
        S += v[i];
        if(i >= 2)
        {
            if(v[i] * v[i-1] > max1)
            {
                if(max1 > max2)
                {
                    max2 = max1;
                    ind2 = ind1;
                }
                max1 = v[i] * v[i-1];
                ind1 = i;
            }
            else if(v[i] * v[i-1] > max2)
            {
                max2 = v[i]*v[i-1];
                ind2 = i;
            }
            if(i >= 3)
            {
                if(v[i] * v[i-1] * v[i-2] > maxM)
                {
                    maxM = v[i] * v[i-1] * v[i-2];
                    indM = i;
                }
            }
        }
    }
    long long S1,S2;
    S1 = S - v[indM] - v[indM-1] - v[indM-2] + maxM;
    S2 = S - v[ind1] - v[ind1-1] - v[ind2] - v[ind2-1] + max1 + max2;
    if(S2 > S1)
        S1 = S2;
    out << S1 << "\n";
    return 0;
}
