#include <fstream>
using namespace std;
ifstream in("z.in");
ofstream out("z.out");
int divempera(int x,int y,int n)
{
    if(n == 0)
        return 1;
    int mid = 1 << (n-1);
    int arie = mid*mid;
    int delV = 0;
    if(x <= mid)
    {
        if(y <= mid)
            delV = 0;
        else
            delV = 2 * arie, y -= mid;
    }
    else
    {
        x -= mid;
        if(y <= mid)
            delV = arie;
        else
            delV = 3 * arie, y -= mid;
    }
    return delV + divempera(x,y,n-1);
}

int main()
{
    int n,t,x,y;
    in >> n >> t;
    while(t--)
    {
        in >> x >> y;
        out << divempera(y,x,n) << "\n";
    }
    return 0;
}
