#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
static const int n = 6;
static const int m  = 5;
static string T = "+*";
static string L1, L2;


string find_rool(string g[],string s)
{
    for(int i = 0; i < n; i++)
        if( g[i].substr(0,2) == s)
            return g[i].substr(2);
    return "\0";
}


string find_alter(string g[],string s)
{
    for(int i = 0; i < n; i++)
        if(s == g[i].substr(0,2))
            for(int j = i + 1; j < n; j++)
                if(s.substr(0,1) == g[j].substr(0,1))
                    return g[j].substr(2);
    return "\0";
}

int find(string g[],string s)
{
    for(int i = 0; i < n; i++)
        if(s == g[i].substr(0,s.size()))
            return i;
    return -1;
}

bool term(string s)
{
    for(int i = 0; i < T.size(); i++)
        if(s == T.substr(i,1) || ( (s >= "a") && (s <= "z")) )
            return true;
    return false;
}

void cout_h(string L, string g[])
{
    int i = 0;
    while(i < L.length()) //поиск по L1
    {
        if( term(L.substr(i,1)) )
        {
            i++;
            continue;
        }
        cout<<find(g, L.substr(i,2))+1;
        i += 2;
    }
    cout<<endl;
}


int down_an(string w, string g[], string S)
{
/*
    (s,i,alfa,beta) конфигурация алгоритма
    q - сост. норм. работы
    b - сост.возврата
    t - закл.(норм.заверш)
    i - указат.на стр
    alfa - содерж.L1(истор.продел.перестан)
    beta - содерж.L2(текущ.цеп.вывода)
*/
    int i = 0;
    char SOS = 'q';
    L2 = S;
    int flag = 35;
    while(true)
    {
        cout<<"L1   "<<L1;
        cout<<"     L2   "<<L2;
        cout<<"     i    "<<i;
        cout<<"     SOS  "<<SOS<<endl<<endl;
        switch(SOS)
        {
            case 't': {
                        cout<<"Успешно"<<endl;
                        cout_h(L1,g);
                        //cout<<L1<<endl;
                        return 1;
                  }  ;
            case 'b': {
                    //cout<<"78"<<endl;
                    if( term(L1.substr(L1.size()-1)) )
                    {
                        L2 = L1.substr(L1.size() - 1) + L2;
                        L1 = L1.substr(0, L1.size() - 1);
                        //cout<<"L1   "<<L1<<endl;
                        //cout<<"L2   "<<L2<<endl<<endl<<endl;
                        i--;
                        continue;
                    }
                    else
                    {
                        string l = find_alter(g, L1.substr(L1.size()-2));
                        if( l != "\0" )
                        {
                            string num = L1.substr(L1.size()-1);
                            string str = find_rool(g,L1.substr(L1.size()-2,2));
                            int q = stoi(num.c_str());
                            q++;
                            string p = to_string(q);
                            L1 = L1.substr(0,L1.size() - 1) + p;
                            L2 = l + L2.substr(str.size());
                            SOS = 'q';
                            continue;
                        }
                        else
                        {
                            if( i == 0 && (L1.substr(L1.size()-2,1) == S))
                            {
                                cout<<"Неудача"<<endl;
                                cout<<"str !E L(G)"<<endl;
                                return 0;
                            }
                            else
                            {
                                string str = find_rool(g,L1.substr(L1.size()-2,2));
                                L2 = L1.substr(L1.size()-2,1) + L2.substr(str.size());
                                L1 = L1.substr(0, L1.size()-2);
                                continue;
                            }
                        }
                    }

              }  ;
            case 'q': {
                        if( term( L2.substr(0,1) ) == false)
                        {
                            int number = find(g, L2.substr(0,1));
                            //cout<<"number   "<<number<<endl;
                            L1 = L1 + g[number].substr(0,2);
                            L2 = g[number].substr(2) + L2.substr(1);
                        }
                        else
                        {
                            if( L2.substr(0,1) == w.substr(i,1) )
                            {
                                L1 = L1 + L2.substr(0,1);
                                L2 = L2.substr(1);
                                i++;
                                if(L2.empty() || i == w.size())
                                    if(L2.empty() && i == w.size())
                                        SOS = 't';
                                    else
                                        SOS = 'b';
                            }
                            else
                                SOS = 'b';
                        }
                    }  ;
        }
    }
    return 1;
}


void full_gr(string g[])
{
// номер альтернативы, правило
    g[0] = "B1T+B";
    g[1] = "B2T";
    g[2] = "T1M";
    g[3] = "T2M*T";
    g[4] = "M1a";
    g[5] = "M2b";
//    g[6] = "M3c";
}


void print_G(string g[])
{
    for(int i = 0; i < n; i++)
        cout<<g[i]<<endl;
}

int main()
{
    cout<<"******************************************************"<<endl<<endl;
    string  w = "a+b*";
    string *G = new string[n];
    string S = "B";
    full_gr(G);
    //print_G(G);
    down_an(w,G,S);
    delete [] G;
}
