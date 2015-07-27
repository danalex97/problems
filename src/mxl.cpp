#include <fstream>
#include <vector>
#include <iostream>
#include <cctype>

using namespace std;

int const MAX_N = 100000 + 1;

vector< int > G [MAX_N];

int depth       [MAX_N];
int highest     [MAX_N];


bool special    [MAX_N];
bool viz        [MAX_N];

int n,m;

void showVector( vector < int    > const , ofstream & );

vector< int > * findRoots();

vector< int > * findArticulationPoints();

void DFS(int const);

struct inputReader ;


void showVector( vector < int > * const what, ofstream & out)
{
    int const len = (int)what->size();

    out << len << "\n";

    for(int i = 0 ; i < len ; ++i)
        out << what->at(i) << " ";

    out << "\n";

    what->clear();
}

vector< int > * findRoots()
{
    vector< int > * roots = new vector< int >;

    roots->reserve(n);

    for(int i = 1 ; i <= n ; ++i)
    {
        if(!viz[i])
        {
            DFS(i);
            roots->push_back(i);
        }
    }

    return roots;
}

vector< int > * findArticulationPoints()
{
    vector< int > * points = new vector< int >;

    points->reserve(n);

    for(int i = 1 ; i <= n ; ++i)
    {
        if(special[i])
            points->push_back(i);
    }

    return points;
}

void DFS(int const node)
{
    viz[node] = 1;
    highest[node] = depth[node];

    int branches = 0;
    int separatedSons = 0;

    for(int i = 0 ; i < (int)G[node].size() ; ++i)
    {
        int const son = G[node][i];

        if(!viz[son])
        {
            ++branches;

            depth[son] = depth[node] + 1;
            DFS(son);

            if(highest[son] >= depth[node])
            {//son has to go thru node to get to higher parts of the tree
                ++separatedSons;
            }

            if(highest[son] < highest[node])
                highest[node] = highest[son];
        }
        else if( depth[son] < highest[node])
            highest[node] = depth[son];
    }

    if (separatedSons > 0
            && (branches > 1 // if it's a root, it has to have more than 1 son
            || depth[node] > 0)) // or it's not a root
        special[node] = 1;
}


struct inputReader
{
    static int const BUFF_SIZE = 2048;
    char buff[BUFF_SIZE];
    int at;
    ifstream in;

    inputReader()
    {
        cerr << "Please specify an input file!\n";
    }

    inputReader(string name)
    {
        in.open(name.c_str());
        readNextBlock();
    }

    void close()
    {
        if(in.is_open())
            in.close();
    }

    ~inputReader()
    {
        close();
    }


    void readNextBlock()
    {
        at = 0;
        in.read(buff, BUFF_SIZE);
    }

    char const nextChar()
    {
        if(at == BUFF_SIZE)
            readNextBlock();

        char const ret = buff[at];
        ++at;

        return ret;
    }

    int const nextInt()
    {
        char now = nextChar();

        while(!isdigit(now))
            now = nextChar();

        int ret = 0;

        while(isdigit(now))
        {
            ret = ret * 10 + now - '0';
            now = nextChar();
        }

        return ret;

    }

    inputReader & operator >> (int & val)
    {
        val = nextInt();
        return *this;
    }


};

int main()
{
    inputReader in("pamant.in");

    in >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int node1, node2;
        in >> node1 >> node2;

        G[node1].push_back(node2);
        G[node2].push_back(node1);

    }

    in.close();


    ofstream out("pamant.out");

    showVector(findRoots(), out);

    showVector(findArticulationPoints(), out);

    out.close();

    return 0;
}
