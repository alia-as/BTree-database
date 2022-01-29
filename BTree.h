#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include<iostream>
#include<string>
using namespace std;
bool debug_btree = true;
const unsigned int max_degree = 4;
class btree_node;
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
    void shifting(bool, int, int ending = max_degree - 1);
    btree_node();

};
class btree
{
public:
    btree_node *root = 0;
    void push(int);
    void split(btree_node*);
    void preorder_print();
    void preorder_print_helper(btree_node*);

};
void btree::split(btree_node *node)
{
    int mid_ind = max_degree / 2;
    btree_node_section *par_child = node->nodes[mid_ind];
    node->nodes[mid_ind] = 0;
    // Building both child nodes
    btree_node *right_child = new btree_node;
    right_child->parent = node->parent;
    right_child->which_child = node->which_child + 1;
    for(int i = 0; i < max_degree - mid_ind - 1; i++)
    {
        right_child->children[i] = node->children[i + mid_ind + 1];
        if(right_child->children[i])
        {
            right_child->children[i]->which_child = i;
        }
        node->children[i + mid_ind + 1] = 0;
        right_child->nodes[i] = node->nodes[i + mid_ind + 1];
        node->nodes[i + mid_ind + 1] = 0;
    }
    right_child->children[max_degree - mid_ind - 1] = node->children[max_degree];

    right_child->how_many = max_degree - mid_ind - 1;
    node->how_many = mid_ind;

    // Building completed
    // Go for putting that child higher

    btree_node *parent;
    if(node == root)
    {
        parent = new btree_node;
        parent->nodes[0] = par_child;
        parent->children[0] = node;
        parent->children[1] = right_child;
        parent->how_many = 1;
        node->parent = parent;
        node->which_child = 0;
        right_child->parent = parent;
        right_child->which_child = 1;
        root = parent;
    }
    else
    {
        node->parent->shifting(false, node->which_child);
        node->parent->nodes[node->which_child] = par_child;
        node->parent->children[node->which_child + 1] = right_child;
        node->parent->how_many++;
    }

}
void btree::push(int val)
{
    if(debug_btree){printf("Going to put %d\n", val); }
    if(!root)
    {
        root = new btree_node;
    }
    int i = 0;
    // Finding right place for that
    if(root->how_many >= max_degree)
    {
        split(root);
        if(debug_btree)
        {
            cout << "After splitting root: ";
            preorder_print();
        }
    }
    btree_node *temp = root;
    while(temp->children[0])
    {
        i = 0;
        while(temp->nodes[i] && temp->nodes[i]->data < val)
        {
            i++;
        }
        if(debug_btree){printf("OK, i = %d\n", i); }
        if(temp->children[i]->how_many >= max_degree)
        {
            split(temp->children[i]);
            if(temp->nodes[i]->data > val)
            {
                temp = temp->children[i];
            }
            else
            {
                temp = temp->children[i + 1];
            }
        }
        else
        {
            temp = temp->children[i];
        }
    }
    if(debug_btree){cout << "We got to this leaf: "; temp->print();}
    i = 0;
    while(temp->nodes[i] && temp->nodes[i]->data < val)
    {
        i++;
    }

    if(debug_btree){printf("OK, i = %d\n", i); }
    temp->shifting(false, i);
    if(debug_btree){cout << "After shifting: "; temp->print();}
    temp->nodes[i] = new btree_node_section;
    temp->nodes[i]->data = val;
    temp->nodes[i]->self = temp;
    temp->how_many++;
    if(debug_btree){cout << "After end: "; temp->print();}


}
void btree_node::shifting(bool is_left, int start, int ending)
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
        cout << temp->data << " ";
        i++;
        temp = nodes[i];
    }
    printf(" & %d nodes & is the children no.%d\n", how_many, which_child);
    cout << "\n";
}
btree_node::btree_node()
{
    for(int i = 0; i < max_degree; i++)
    {
        nodes[i] = 0;
        children[i] = 0;
    }
    children[max_degree] = 0;
    parent = 0;
}
void btree::preorder_print()
{
    preorder_print_helper(root);
}
void btree::preorder_print_helper(btree_node *node)
{
    node->print();
    int i = 0;
    while(node->children[i])
    {
        preorder_print_helper(node->children[i]);
        i++;
    }
}
#endif // BTREE_H_INCLUDED
