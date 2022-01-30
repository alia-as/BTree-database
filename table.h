#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include <iostream>
#include "BTree.h"
#include "hashing.h"
using namespace std;
bool debug_table = true;
class table
{
    public:
    string name;
    int how_many = 0;
    int *types; // A list of types, 0 for int, 1 for string, 2 for timestamp. if 3 that's undefined
    string *tree_names;
    btree *bjungle;
    unsigned int field_count;
    table(string, int, string[]);
    void push(int[]);
    void find_where(string*, int, string, string, int);

};
void table::find_where(string *fields, int how_many, string which, string val, int sign)
{
    int i;
    for(i = 0; i < field_count; i++)
    {
        if(tree_names[i] == which)
        {
            break;
        }
    }
    // find int of given value
    int valint;
    if(types[i] == 0)
    {
        valint = sint2int(val);
    }
    else if(types[i] == 1)
    {
        valint = 123;
    }
    else if(types[i] == 2)
    {
        valint = timestamp2int(val);
    }
    btree tree = bjungle[i];


}
table::table(string the_name, int fields, string fields_names[]) // Len of fields_names is 2 * fields
{
    name = the_name;
    bjungle = new btree[fields + 1];
    types = new int[fields + 1];
    tree_names = new string[fields + 1];
    field_count = fields + 1;
    types[0] = 0;
    tree_names[0] = "ID";
    for(int i = 0; i < fields; i++)
    {
        string type = fields_names[2 * i + 1];
        types[i + 1] = (type == "int") ? 0 : (type == "string") ? 1 : (type == "timestamp") ? 2 : 3;
        tree_names[i + 1] = fields_names[2 * i];
    }
    cout << "Table " << name << " created!\n";
    for(int i = 0; i < field_count; i++)
    {
        cout << tree_names[i] << ": " << types[i] << "\n";
    }

}
void table::push(int datas[])
{
    int first_id = bjungle[0].puny();
    if(debug_table)
    {
        printf("puny is %d\n", first_id);
    }
    btree_node_section *now = bjungle[0].push(first_id), *temp, *first;
    first = now;
    for(int i = 1; i < field_count; i++)
    {
        temp = now;
        now = bjungle[i].push(datas[i - 1]);
        temp->nextField = now;

    }
    now->nextField = first;

}
#endif // TABLE_H_INCLUDED
