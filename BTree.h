#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include<iostream>
#include<string>
using namespace std;
bool debug_btree = true;
const unsigned int max_degree = 4;
class btree_node_section
{
public:
    int data = 0;
    btree_node_section *nextField = 0;
    btree_node *self = 0;
};
class btree_node
{
public:
    btree_node_section *nodes[max_degree];
    btree_node *children[max_degree + 1], *parent;
    int how_many = 0;
    int which_child = -1;
    void print();
    void shifting(int, int ending = max_degree - 1, bool);
    btree_node();
    void split();
};
class btree
{
public:
    btree_node *root = 0;
    void push(int);

};
void btree::push(int val)
{
    if(!root)
    {
        root = new btree_node;
    }
    btree_node *temp = root;
    int i = 0;
    // Finding right place for that
    while(temp->children[0])
    {
        i = 0;
        while(temp->nodes[i] && temp->nodes[i]->data < val)
        {
            i++;
        }
        if(temp->nodes[i])
        {
            temp = temp->children[i];
        }
    }


}
void btree_node::shifting(int start, int ending, bool is_left)
{
    if(is_left) // index start will be replaced and ending will be deleted
    {
        for(int i = start; i < ending; i++)
        {
            nodes[i] = nodes[i + 1];
            children[i + 1] = children[i + 2];
            if(children[i + 1])
            {
                children[i + 1]->which_child--;
            }
        }
        nodes[ending] = 0;
        children[ending + 1] = 0;
    }
    else // index ending will be replaced and start will be deleted
    {
        for(int i = ending; i > start; i--)
        {
            nodes[i] = nodes[i - 1];
            children[i + 1] = children[i];
            if(children[i + 1])
            {
                children[i + 1]->which_child++;
            }
        }
        nodes[start] = 0;
        children[start + 1] = 0;

    }
}
void btree_node::print()
{
    btree_node_section *temp = nodes[0];
    int i = 0;
    while(temp)
    {
        cout << temp->data;
        i++;
        temp = nodes[i];
    }
    cout << "\n";
}
void btree_node::btree_node()
{
    for(int i = 0; i < max_degree; i++)
    {
        nodes[i] = 0;
        children[i] = 0;
    }
    children[max_degree] = 0;
    parent = 0;
}
#endif // BTREE_H_INCLUDED
