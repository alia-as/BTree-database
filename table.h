#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include <iostream>
#include "BTree.h"
#include "hashing.h"
using namespace std;
bool debug_table = false;
class table
{
    public:
    string name;
    int *types; // A list of types, 0 for int, 1 for string, 2 for timestamp. if 3 that's undefined
    string *tree_names;
    btree *bjungle;
    unsigned int field_count;
    table(string, int, string[]);
    void push(long long[]);
    vec<btree_node_section*> nodes_with_condition(string, string, string);
    void print_with_conditions(string, string, string, string[], int);
    void update(string, string, string, string[]);
    void deleteee(string, string, string);


};
void table::deleteee(string which, string sign, string val)
{
    vec<btree_node_section*> nodes = nodes_with_condition(which, sign, val);
    for(int q = 0; q < nodes.len; q++)
    {
        btree_node_section *now = nodes.inpos(q);
        for(int w = 0; w < field_count; w++)
        {
            bjungle[w].del(now->data);
            now = now->nextField;
        }
    }
}
void table::update(string which, string sign, string val, string fields[])
{
    long long datas[field_count - 1];
    for(int w = 0; w < field_count - 1; w++)
    {
        if(types[w + 1] == 0)
        {
            datas[w] = sint2int(fields[w]);
        }
        else if(types[w + 1] == 1)
        {
            datas[w] = string2int(fields[w]);
        }
        else if(types[w + 1] == 2)
        {
            datas[w] = timestamp2int(fields[w]);
        }
    }
    vec<btree_node_section*> nodes = nodes_with_condition(which, sign, val);
    for(int i = 0; i < nodes.len; i++)
    {
        btree_node_section* now = nodes.inpos(i);
        now = now->nextField;
        for(int q = 0; q < field_count - 1; q++)
        {
            now->data = datas[q];
            now = now->nextField;
        }
    }
}
void table::print_with_conditions(string which, string sign, string val, string fields[], int counts)
{
    vec<btree_node_section*> nodes = nodes_with_condition(which, sign, val);
    if(debug_table)
    {
        nodes.print();

    }
    bool needed[field_count];
    if(counts == field_count)
    {
        for(int i = 0; i < field_count; i++)
        {
            needed[i] = true;
        }
    }
    else
    {
        for(int q = 0; q < field_count; q++)
        {
            needed[q] = false;
            for(int w = 0; w < counts; w++)
            {
                if(tree_names[q] == fields[w])
                {
                    needed[q] = true;
                    break;
                }
            }
        }
    }
    if(debug_table)
    {
        cout << "Needing: ";
        for(int e = 0; e < field_count; e++)
        {
            cout << needed[e];
        }
        cout << "\n";
    }
    for(int r = 0; r < nodes.len; r++)
    {
        btree_node_section *now = nodes.inpos(r);
        for(int pos = 0; pos < field_count; pos++)
        {
            if(needed[pos])
            {
                if(types[pos] == 0)
                {
                    cout << now->data << " ";
                }
                else if(types[pos] == 1)
                {
                    cout << int2string(now->data) << " ";
                }
                else if(types[pos] == 2)
                {
                    cout << int2timestamp(now->data) << " ";
                }

            }
            now = now->nextField;
        }
        cout << "\n";
    }
}
vec<btree_node_section*> table::nodes_with_condition(string which, string sign, string val)
{
    int i;
    for(i = 0; i < field_count; i++)
    {
        if(tree_names[i] == which)
        {
            break;
        }
    }
    // Now i is the tree which we set rules to that
    // find int of given value
    long long valint;
    if(types[i] == 0)
    {
        valint = sint2int(val);
    }
    else if(types[i] == 1)
    {
        valint = string2int(val);
    }
    else if(types[i] == 2)
    {
        valint = timestamp2int(val);
    }
    btree tree = bjungle[i];
    vec<btree_node_section*> ans, that_tree_nodes = tree.nodes_with_condition(valint, sign);
    for(int q = 0; q < that_tree_nodes.len; q++)
    {
        btree_node_section* t = that_tree_nodes.inpos(q);

    }

    for(int q = 0; q < that_tree_nodes.len; q++)
    {
        btree_node_section* t = that_tree_nodes.inpos(q);
        for(int w = 0; w < field_count - i; w++)
        {
            t = t->nextField;

        }
        ans.sorted_pushback(t);

    }
    return ans;


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
    if(debug_table)
    {
        cout << "Table " << name << " created!\n";
        for(int i = 0; i < field_count; i++)
        {
            cout << tree_names[i] << ": " << types[i] << "\n";
        }
    }

}
void table::push(long long datas[])
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
