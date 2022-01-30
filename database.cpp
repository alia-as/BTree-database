#include<iostream>
#include "table.h"
#include "hashing.h"
using namespace std;
int query_analizer(string);
bool debug_database = true;
string *tokenize(string, int&);
bool is_letter(int);
table **tables = new table*[1];
int table_count = 0, table_size = 1;
int main()
{
    string query = "";
    int c = 0;
    while(true)
    {
        getline(cin, query);
        c = 0;
        query_analizer(query);
    }
}
int query_analizer(string query)
{
    int counts = 0;
    string* query_tokens = tokenize(query, counts);
    if(debug_database)
    {
        for(int i = 0; i < counts; i++)
        {
            cout << query_tokens[i] << "&";
        }
        cout << "\n";
    }
    string command = query_tokens[0];
    if(command == "CREATE")
    {
        string table_name = query_tokens[2];
        for(int i = 0; i < table_count; i++)
        {
            if(tables[i]->name == table_name)
            {
                cout << "Table already exist!\n";
                return 1;
            }
        }
        int fc = ((counts - 5) + 1) / 3, controller = 0;
        string f[fc * 2];
        for(int i = 4; i < counts; i++)
        {
            if(i % 3)
            {
                f[controller] = query_tokens[i];
                controller++;
            }
        }
        if(table_count < table_size)
        {
            tables[table_count] = new table(table_name, controller / 2, f);

        }
        else
        {
            table **temp = new table*[2 * table_size];
            for(int i = 0; i < table_count; i++)
            {
                temp[i] = tables[i];
            }
            temp[table_count] = new table(table_name, controller / 2, f);
            tables = temp;
        }
        table_count++;


    }
    else if(command == "INSERT")
    {
        string table_name = query_tokens[2];
        table *right_one = 0;
        for(int i = 0; i < table_count; i++)
        {
            if(tables[i]->name == table_name)
            {
                right_one = tables[i];
            }
        }
        if(!right_one)
        {
            cout << "Table does not exist!\n";
            return 2;
        }
        int datas[right_one->field_count - 1], ind = 0;
        for(int i = 5; ind < right_one->field_count - 1; i += 2)
        {
            int type = right_one->types[ind + 1];
            if(type == 0) // int
            {
                datas[ind] = sint2int(query_tokens[i]);
                ind++;
            }
            else if(type == 1) // string
            {
                datas[ind] = 123;
                ind++;
            }
            else if(type == 2) // time stamp
            {
                datas[ind] = timestamp2int(query_tokens[i]);
                ind++;
            }

        }
        if(debug_database)
        {
            for(int i = 0; i < right_one->field_count - 1; i++)
            {
                cout << datas[i] << " ";
            }
            cout << "\n";
        }
        right_one->push(datas);

    }
    else if(command == "UPDATE")
    {
        cout << 3 << endl;
    }
    else if(command == "SELECT")
    {
        cout << 4 << endl;
    }
    else if(command == "DELETE")
    {
        cout << 5 << endl;
    }
    else
    {
        cout << 6 << endl;
    }
}
string *tokenize(string text, int &counts)
{
    string *ans = new string[1], *temp;
    counts = 0;
    int ans_size = 1;
    string word = "";
    bool is_let = true, is_name = false;
    int i = -1;
    for(i = 0; i < text.size(); i++)
    {
        int now = (int)text[i];
        if(text[i] == '"')
        {
            if(counts == ans_size)
            {
                temp = new string[2 * ans_size];
                for(int j = 0; j < 2 * ans_size; j++)
                {
                    temp[j] = "";

                }
                for(int j = 0; j < ans_size; j++)
                {
                    temp[j] = ans[j];

                }
                temp[counts] = word;
                ans = temp;
                ans_size *= 2;
            }
            else
            {
                ans[counts] = word;
            }
            counts++;
            word = text[i];
            i++;
            while(text[i] != '"')
            {
                word += text[i];
                i++;
            }
            word += text[i];
            if(counts == ans_size)
            {
                temp = new string[2 * ans_size];
                for(int j = 0; j < 2 * ans_size; j++)
                {
                    temp[j] = "";

                }
                for(int j = 0; j < ans_size; j++)
                {
                    temp[j] = ans[j];

                }
                temp[counts] = word;
                ans = temp;
                ans_size *= 2;
            }
            else
            {
                ans[counts] = word;
            }
            counts++;
            word = "";
            continue;
        }

        if((!is_letter(now) && is_let) || (!is_let && is_letter(now)))
        {
            if(counts == ans_size)
            {
                temp = new string[2 * ans_size];
                for(int j = 0; j < 2 * ans_size; j++)
                {
                    temp[j] = "";

                }
                for(int j = 0; j < ans_size; j++)
                {
                    temp[j] = ans[j];

                }
                temp[counts] = word;
                ans = temp;
                ans_size *= 2;
            }
            else
            {
                ans[counts] = word;
            }
            if(word != "")
            {
                counts++;
            }
            if(text[i] != ' ')
            {
                word = text[i];
            }
            else
            {
                word = "";
            }
            is_let = !is_let;
        }
        else if(text[i] != ' ')
        {
            word += text[i];
        }
    }
    if(counts == ans_size)
    {
        temp = new string[2 * ans_size];
        for(int j = 0; j < 2 * ans_size; j++)
        {
            temp[j] = "";

        }
        for(int j = 0; j < ans_size; j++)
        {
            temp[j] = ans[j];

        }
        temp[ans_size] = word;
        ans = temp;
        ans_size *= 2;
    }
    else
    {
        ans[counts] = word;
    }
    word = "";
    counts++;
    return ans;
}
bool is_letter(int n)
{
    if((n >= 97 && n <= 122) || (n >= 65 && n <= 90) || (n >= 47 && n <= 57))
    {
        return true;
    }
    else
    {
        return false;
    }
}
