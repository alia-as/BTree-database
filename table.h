#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include <iostream>
#include "BTree.h"
using namespace std;
unsigned int field_count;
btree *bjungle;
//class node
//{
//public:
//    int data;
//    node *nextField = 0;
//    node_btree *self = 0;
//};
class record
{
    friend class table;
    node_table *id;
    void push(int[]);
    void push_helper(int[], int, node_table*);
    void print();
};
class table
{
    string name;
    int how_many = 0;
    record **records;
    int *types; // A list of types, 0 for int, 1 for string, 2 for timestamp. if 3 that's undefined

public:
    table(string, int, string[]);
    void push(int[]);
    void print(int);
};
table::table(string the_name, int fields, string fields_names[]) // Len of fields_names is 2 * fields
{
    name = the_name;
    bjungle = new btree[fields];
    types = new int[fields];
    field_count = fields;
    for(int i = 0; i < fields; i++)
    {
        bjungle[i].set_name(fields_names[2 * i]);
        string type = fields_names[2 * i + 1];
        types[i] = (type == "int") ? 0 : (type == "string") ? 1 : (type == "timestamp") ? 2 : 3;
    }
    records = new record*[field_count];

}
void table::push(int datas[])
{
    records[how_many] = new record;
    records[how_many]->push(datas);
    how_many++;
}
void record::push(int datas[])
{
    id = new node_table;
    push_helper(datas, 0, id);
}
void record::push_helper(int datas[], int at_field, node_table *current)
{
    if(at_field >= field_count)
    {
        return;
    }
    current->self = bjungle[at_field].push(datas[at_field]);
//    current->self->nodes[current->self->how_many - 1] = current;
    current->data = datas[at_field];
    current->nextField = new node_table;
    push_helper(datas, at_field + 1, current->nextField);

}
void table::print(int which)
{
    node_table *temp = records[which]->id;
    for(int i = 0; i < field_count; i++)
    {
        cout << temp->data << " ";
        temp = temp->nextField;
    }
    cout << "\n";
}
#endif // TABLE_H_INCLUDED
