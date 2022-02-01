#include<iostream>
#include "table.h"
#include "hashing.h"
#include "query_analizer.h"
using namespace std;
int main()
{
    string query = "";
    while(true)
    {
        getline(cin, query);
        try
        {
            if(query != "")
            {
                query_analizer(query);
            }
        }
        catch(char const* msg)
        {
            cout << msg;
        }
    }
}
