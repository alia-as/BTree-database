#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include<iostream>
#include<string>
using namespace std;
bool debug_btree = true;
const unsigned int max_degree = 4;
class node_btree;
class node_table
{
public:
    int data;
    node_table *nextField = 0;
    node_btree *self = 0;
};
class node_btree
{
    friend class btree;
    friend class record;
    int datas[max_degree];
    int how_many = 0; // How many numbers are here in this node
    node_btree *children[max_degree + 1]; // Pointer to node's children
    node_btree *parent = 0; // Pointer to node's parent
    node_btree();
    int which_child = -1; // the order of this child according to his parent
//    node_table *nodes[max_degree];
    void print(string ending = "\n");
};
class btree
{
    string name;
    node_btree *root = 0;
    void preorder_print_helper(node_btree*);
    void split_child(node_btree*, int);
public:
    void set_name(string the_name = "");
    node_btree *push(int); // return the pointer to the cell it has saved
    void preorder_print();
    bool do_we_have(int);
    int puny();
};
int btree::puny()
{
    int i = 1;
    while(true)
    {
        if(!do_we_have(i))
        {
            return i;
        }
        else
        {
            i++;
        }
    }
}
bool btree::do_we_have(int val)
{
    node_btree *temp = root;
    while(true)
    {
        int i = 0;
        while(i < temp->how_many && val > temp->datas[i])
        {
            i++;
        }
        if(val == temp->datas[i]){return true;}
        else
        {
            if(temp->children[i])
            {
                temp = temp->children[i];
            }
            else
            {
                return false;
            }
        }
    }

}
node_btree::node_btree()
{
    for(int i = 0; i < max_degree; i++)
    {
        datas[i] = 0;
        children[i] = 0;
    }
    children[max_degree] = 0;

}
void btree::split_child(node_btree* node, int i)
{
    node_btree *app_child = node->children[i];
    int par_child = app_child->datas[max_degree / 2]; // The child that will become his dad!!!!
    if(debug_btree){printf("Strange kid is %d!\n", par_child); }
    // Find position of this strange kid
    for(int q = max_degree - 1; q > i; q--)
    {
        node->datas[q] = node->datas[q - 1];
    }
    node->datas[i] = par_child;
    if(debug_btree){printf("1\n", par_child); }
//    node->nodes[i] = app_child->nodes[max_degree / 2];
//    node->nodes[i]->self = node;
    node->how_many++;
    // app_child become left child of that strange kid and new 'rightc' node become the right kid of him
    node_btree *rightc = new node_btree;
    for(int q = 0; q < max_degree - max_degree / 2 - 1; q++)
    {
        rightc->datas[q] = app_child->datas[q + max_degree / 2 + 1];
        rightc->children[q] = app_child->children[q + max_degree / 2 + 1];
        if(rightc->children[q]){rightc->children[q]->which_child = q;}
//        rightc->nodes[q] = app_child->nodes[q + max_degree / 2 + 1];
//        rightc->nodes[q]->self = rightc;
    }
    if(debug_btree){printf("1\n", par_child); }
    rightc->children[max_degree - max_degree / 2 - 1] = app_child->children[max_degree];
    if(rightc->children[max_degree - max_degree / 2 - 1])
    {
        rightc->children[max_degree - max_degree / 2 - 1]->which_child = max_degree - max_degree / 2 - 1;

    }
    rightc->how_many = max_degree - max_degree / 2 - 1;
    if(debug_btree){printf("Right completed: "); rightc->print();}
    for(int q = max_degree / 2; q < max_degree; q++)
    {
        app_child->datas[q] = 0;
        app_child->children[q + 1] = 0;
//        app_child->nodes[q] = 0;
    }
    app_child->how_many = max_degree / 2;
    if(debug_btree){printf("Left completed: "); app_child->print();}
    // Putting the new child in its place
    for(int q = max_degree; q > i + 1; q--)
    {
        node->children[q] = node->children[q - 1];
        if(node->children[q])
        {
            node->children[q]->which_child = q;
        }

    }
    node->children[i + 1] = rightc;
    if(node->children[i + 1])
    {
        node->children[i + 1]->which_child = i + 1;

    }
    if(debug_btree){printf("Splitted, And new is\n"); preorder_print();}

}
node_btree* btree::push(int val)
{
    if(!root)
    {
        root = new node_btree;
        if(debug_btree){cout << "root created!\n";}

    }
    if(root->datas[max_degree - 1])
    {
        if(debug_btree){printf("Root is full\n"); }
        node_btree *newroot = new node_btree;
        newroot->children[0] = root;
        newroot->children[0]->which_child = 0;
        root = newroot;
        split_child(newroot, 0);

    }
    node_btree *node = root;
    while(node->children[0]) // Check if it is not leave
    {
        if(debug_btree){cout << "Node is: "; node->print();}
        int i = 0;
        while(node->datas[i] && node->datas[i] < val)
        {
            i++;
        }
        if(debug_btree)
        {
            printf("appropriate child is the children number %d\n", i);
        }
        node_btree *app_child = node->children[i];
        if(app_child->datas[max_degree - 1])
        {
            split_child(node, i);
            node = (val > node->datas[i]) ? node->children[i + 1] : node->children[i];
        }
        else
        {

            node = app_child;

        }
    }

    int i  = 0;
    while(node->datas[i] && node->datas[i] < val)
    {
        i++;
    }
    if(node->datas[i])
    {
        for(int j = max_degree - 1; j > i; j--)
        {
            node->datas[j] = node->datas[j - 1];
        }
        if(debug_btree){printf("i = %d\n", i); }
        node->datas[i] = val;
        node->how_many++;
        return node;
    }
    else
    {
        if(debug_btree){printf("i = %d\n", i); }
        node->datas[i] = val;
        node->how_many++;
        return node;
    }

}
void node_btree::print(string ending)
{
    for(int i = 0; i < max_degree && datas[i]; i++)
    {
        cout << datas[i] << " ";
    }
    cout << "how many? " << how_many << " &which child = " << which_child << ending;
}
void btree::preorder_print()
{
    preorder_print_helper(root);
    cout << "\n\t*********\n";
}
void btree::preorder_print_helper(node_btree *node)
{
    if(!node)
    {
        cout << "Tree is empty!";
        return;
    }
    node->print();
    for(int i = 0; i < max_degree + 1; i++)
    {
        if(node->children[i])
        {

            preorder_print_helper(node->children[i]);
        }
        else
        {
            return;
        }
    }
}
void btree::set_name(string the_name)
{
    name = the_name;
    if(debug_btree){cout << the_name << " created!\n";}
}
#endif // BTREE_H_INCLUDED
