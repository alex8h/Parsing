#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
static const int n = 7;
static string N = "ABTM";
static string T = "!()I+*";
static int **num;
static string *G = new string[n];
static string *Lt = new string[N.size()];
static string *Rt = new string[N.size()];


bool term(string s)
{
    if( T.find(s,0) == -1 )
        return 0;
    return 1;
}


void print_marx(int ** s,int k)
{
	for(int i = 0;  i < k; i++)
	{
		for(int j = 0; j < k; j++)
			cout<<s[i][j];
		cout<<endl;
	}
}

int find_index(int m)   // возвращает индекс в num по индексу G
{
    for(int i = 0; i < N.size(); i++)
    {
        for(int j = 0; (j < N.size()) && (num[i][j] > 0) ; j++ )
        {
            if( m == (num[i][j] - 1) )
                return i;
        }
    }
    return -1;
}


bool equal(string a, string b)
{
    for(int i = 0; i < n; i++)
    {
        int t = G[i].find(a,1);
        if(t == -1)
            continue;
        int k = G[i].rfind(b, G[i].size() - 1);
        if(k == -1)
            return false;
        if(t >= k)
            return false;
        return true;
    }
    return true;
}

bool more(string a, string b)
{
    for(int i = 0; i < n; i++)
    {
        int t = G[i].rfind(b,G[i].size()-1);
        if(t == -1)
            continue;
        if( ( (t - 1 <= 0) || ( term(G[i].substr(t-1,1)) ) ) )
            return false;
        int w = N.find(G[i].substr(t-1,1),0);
        int f = Rt[w].find(a,0);
        if(f == -1)
            return false;
        return true;
    }
    return true;
}

bool lness(string a, string b)
{
    for(int i = 0; i < n; i++)
    {
        int t = G[i].find(a,1);
        if(t == -1)
            continue;
        if( ( (t == G[i].size() - 1 ) || ( term(G[i].substr(t+1,1)) ) ) )
            return false;
        int w = N.find(G[i].substr(t+1,1),0);
        int f = Lt[w].find(b,0);
        if(f == -1)
            return false;
        return true;
    }
    return true;
}



int * find(string G[],string s)
{
    int *mass = new int [N.size()];
    for ( int i = 0, j = 0; i < n; i++ )
    {
        if(s == G[i].substr(0,1))
            mass[j++] = i + 1;
    }
    return mass;
}

int ** create(int r)
{
    int **mass = new int* [r];
    for(int i = 0; i < r; i++)
        mass[i] = new int [r];
    return mass;

}

string clear(string str)
{
    string s = str;
    for(int i = 0; i < s.size(); i ++)
        for(int j = i + 1; j < s.size(); j++)
        {
            if(s.substr(i,1) == s.substr(j,1))
                s.erase(j,1);
        }
    return s;
}

void print_G(string M[],int k)
{
    for(int i = 0; i < k; i++)
        cout<<M[i]<<endl;
}


void step2_1(string M[])
{
    for(int i = 0; i < N.size(); i++)
        for(int j = 0; j < N.size(); j++)
            if(i != j)
                for(int k = 0; k < M[j].size(); k++)
                    if(N.substr(i,1) == M[j].substr(k,1))
                    {
                        M[j] = M[j] + M[i];
                        M[j] = clear(M[j]);
                    }

}


void step2_2(string M[],string D[])
{
    for(int i = 0; i < N.size(); i++)
        for(int j = 0; j < N.size(); j++)
            if(i != j)
                for(int k = 0; k < M[j].size(); k++)
                    if(N.substr(i,1) == M[j].substr(k,1))
                    {
                        D[j] = D[j] + D[i];
                        D[j] = clear(D[j]);
                    }

}


bool compare(string K[],string M[])
{
    for(int i = 0; i < N.size(); i++)
        if(K[i] != M[i])
            return false;
    return true;
}



void l_r_simb(string G[], string L[],string R[])
{
    num = create(N.size());
    for(int i = 0; i < N.size(); i++)
        num[i] = find(G,N.substr(i,1));
    print_marx(num,N.size());
    for( int i = 0; i < N.size(); i++)
        for(int j = 0; j < N.size(); j++)
        {
            int l = num[i][j] - 1;
            if(l < 0)
                break;
            string s = G[l].substr(1);
            L[i] = L[i] + s.substr(0,1);
            L[i] = clear(L[i]);
            R[i] = R[i] + s.substr(s.size()-1);
            R[i] = clear(R[i]);
        }
    string *M = new string[N.size()];
    while(!compare(L,M))
    {
        M = L;
        step2_1(L);
    }
    while(!compare(R,M))
    {
        M = R;
        step2_1(R);
    }
}


void lt_rt_simb(string G[], string L[],string R[],string Lt[],string Rt[])
{
    for( int i = 0; i < N.size(); i++)
        for(int j = 0; j < N.size(); j++)
        {

            int l = num[i][j] - 1;
            if(l < 0)
                break;
            for(int k = 0; k < G[l].size(); k++)
                if( term(G[l].substr(k,1)) )
                {
                    Lt[i] = Lt[i] + G[l].substr(k,1);
                    break;
                }
            for(int k = G[l].size() - 1; k >= 0; k--)
                if( term(G[l].substr(k,1)) )
                {
                    Rt[i] = Rt[i] + G[l].substr(k,1);
                    break;
                }
        }


    string *M = new string[N.size()];
    while(!compare(Lt,M))
    {
        M = Lt;
        step2_2(L,Lt);
    }
    while(!compare(Rt,M))
    {
        M = Rt;
        step2_2(L,Rt);
    }




}



void buid_mop(string MOP[])
{
    for(int i = 0;  i < T.size(); i++)
    {
        string a = T.substr(i,1);
        for(int j = 0; j < T.size(); j++)
        {
            string b = T.substr(j,1);
            //cout<<"a    "<<a<<"     b   "<<b<<endl;
            if( equal(a,b) )
            {
                MOP[i].insert(j,"=");
                continue;
            }
            if( more(a,b) )
            {
                MOP[i].insert(j,">");
                continue;
            }
            if( lness(a,b) )
            {
                MOP[i].insert(j,"<");
                continue;
            }
            MOP[i].insert(j," ");
        }
    }
}


string find_rool(string g[],string s )
{
    for(int i = 0; i < n; i++)
        if( g[i].substr(0,1) == s)
            return g[i].substr(1);
    return "\0";
}



void full_gr(string G[])
{
    G[0] = "A!B!";
    G[1] = "BB+T";
    G[2] = "BT";
    G[3] = "TT*M";
    G[4] = "TM";
    G[5] = "MI";
    G[6] = "M(B)";
}



int main()
{
    cout<<"******************************************************"<<endl<<endl;

    full_gr(G);

    string *L = new string[N.size()];
    string *R = new string[N.size()];



    l_r_simb( G, L, R);

    cout<<"L(U):"<<endl;
    print_G(L,N.size());
    cout<<endl<<"R(U):"<<endl;
    print_G(R,N.size());

    lt_rt_simb(G, L, R, Lt, Rt);

    cout<<endl<<"Lt(U):"<<endl;
    print_G(Lt,N.size());
    cout<<endl<<"Rt(U):"<<endl;
    print_G(Rt,N.size());
    cout<<endl<<endl;

    string *MOP = new string[T.size()];
    buid_mop(MOP);
    cout<<T<<endl;
    print_G(MOP,T.size());


    delete [] G;
    delete [] L;
    delete [] R;
    delete [] Lt;
    delete [] Rt;
    delete [] MOP;
    return 0;
}
