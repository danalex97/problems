#include <fstream>
#include <string>

using namespace std;

class Mstack{
public:
    Mstack():
        left(0),
        right(0),
        aux(0),
        out("mstack.out"){}
    void push()
    {
        out << "push 2\n";
        ++right;
        balance();
    }
    void pop()
    {
        if(right == 0)
            resize(1,left,2,right);
        if(right){
            out << "pop 2\n";
            --right;
        } else {
            out << "pop 3\n";
            --aux;
        }
        balance();
    }
    void top()
    {

        if(right)
            out << "top 2\n";
        else {
            resize(1,left,2,right);
            if(right)
                out << "top 2\n";
            else out << "top 3\n";
        }
    }
    void mid()
    {
        out << "top 3\n";
    }
private:
    void balance()
    {
        int each = ( left + right + aux ) ;
        if(each == 0)
            return;
        each = 1 + each/2;

        while(aux < each){
            if(left == 0)
                resize(2,right,1,left);
            out << "move 1 3\n";
            --left,++aux;
        }

        while(aux > each){
            out << "move 3 1\n";
            --aux,++left;
        }
    }

    void resize(const int &from, int &from_size, const int &to, int &to_size)
    {

        int mv = from_size - from_size / 2;

        for(int i = from_size - mv ; i ; -- i)
            out << "move " << from << " 3\n";
        for(int i = mv ; i ; -- i)
            out << "move " << from << " " << to << "\n";
        for(int i = from_size - mv ; i ; -- i)
            out << "move 3 " << from << "\n";
        from_size -= mv;
        to_size += mv;

    }

    int left,right,aux;
    ofstream out;
}T;

int main()
{
    ifstream in("mstack.in");
    string op;
    int n;
    in >> n;
    while(n--){

        in >> op;
        if(op == "push")
            T.push();
        else if(op == "pop")
            T.pop();
        else if(op == "top")
            T.top();
        else if(op == "middle")
            T.mid();
    }

    return 0;
}
