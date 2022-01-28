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
    void shift(int, int, bool);

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
    bool del_val(int);
};
void node_btree::shift(int start, int ending, bool is_right) // Index ending will be deleted in is_right, else index start will be deleted
{
    if(is_right)
    {
        for(int i = ending; i > start; i--)
        {
            datas[i] = datas[i - 1];
            children[i] = children[i - 1];
            if(children[i])
            {
                children[i]->which_child++;
            }
        }
        children[ending + 1] = children[ending];
        datas[start] = 0;

    }
    else
    {
        for(int i = start; i < ending; i++)
        {
            datas[i] = datas[i + 1];
            children[i] = children[i + 1];
            if(children[i])
            {
                children[i]->which_child--;
            }
        }
        children[ending] = children[ending + 1];
        datas[ending] = 0;
        children[ending + 1] = 0;
    }
}
bool btree::del_val(int val)
{
    node_btree *temp = root;
    int i = 0;
    while(true)
    {
        i = 0;
        while(i < temp->how_many && val > temp->datas[i])
        {
            i++;
        }
        if(val == temp->datas[i])
        {
            break;
        }
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
    if(debug_btree){printf("We are going to delete the member no.%d from: ", i);temp->print();}
    if(temp->children[i])
    {
        if(debug_btree){cout << "temp isn't leaf\n";}
        node_btree *temp2 = temp;
        temp = temp->children[i];
        if(debug_btree)
        {
            cout << "finding pre\n---------------\nOne to left: ";
            temp->print();
        }
        while(temp->children[temp->how_many])
        {
            temp = temp->children[temp->how_many];
            if(debug_btree)
            {
                cout << "Sharp right: ";
                temp->print();
            }
        }
        int predecessor = temp->datas[temp->how_many - 1];
        if(debug_btree)
        {
            printf("Finded: %d\n", predecessor);
            cout << "------------------\n";
        }
        temp2->datas[i] = predecessor;
        i = temp->how_many - 1;
    }
    if(debug_btree){cout << "Now temp is leaf\n";}
    // Now temp is leaf
    if(temp->how_many > max_degree / 2)
    {
        if(debug_btree){cout << "It seems that's an easy deletion!\n";}
        // shifting
        temp->shift(i, max_degree - 1, false);
        temp->how_many--;

    }
    else
    {
        node_btree *rs = 0, *ls = 0;
        cout << temp << " && " << temp->parent << endl;
        if(temp->which_child < temp->parent->how_many)
        {
            if(debug_btree){cout << "has right!\n";}
            rs = temp->parent->children[temp->which_child + 1];
        }
        if(temp->which_child > 0)
        {
            if(debug_btree){cout << "has left!\n";}
            ls = temp->parent->children[temp->which_child - 1];

        }
        if(debug_btree){cout << "rs: " << rs << "  ls= " << ls << endl;}
        if(rs && rs->how_many > max_degree / 2)
        {
            if(debug_btree){cout << "right sibling can lend!\n";}
            temp->shift(i, max_degree - 1, false);
            temp->datas[temp->how_many - 1] = temp->parent->datas[temp->which_child];
            temp->parent->datas[temp->which_child] = rs->datas[0];
            rs->shift(0, rs->how_many, false);

        }
        else if(ls && ls->how_many > max_degree / 2)
        {
            if(debug_btree){cout << "left sibling can lend!\n";}
            temp->shift(0, i, true);
            temp->datas[0] = temp->parent->datas[temp->which_child - 1];
            temp->parent->datas[temp->which_child - 1] = ls->datas[ls->how_many - 1];
            ls->datas[ls->how_many - 1] = 0;

        }
        else
        {
            if(ls)
            {
                ls->datas[ls->how_many] = ls->parent->datas[ls->which_child];
                ls->how_many++;
                for(int w = 0; w < temp->how_many - 1; w++)
                {
                    if(w != i)
                    {
                        ls->datas[ls->how_many] = temp->datas[w];
                        ls->how_many++;

                    }

                }
                ls->parent->shift(ls->which_child, max_degree - 1, false);
            }
            else
            {
                temp->shift(i, max_degree - 1, i++);
                temp->datas[temp->how_many - 1] = temp->parent->datas[temp->which_child];
                for(int w = 0; w < rs->how_many; w++)
                {
                    temp->datas[temp->how_many] = rs->datas[w];
                    temp->how_many++;
                }
                temp->parent->shift(temp->which_child, max_degree - 1, false);
                temp->parent->children[temp->which_child] = temp;

            }
        }
    }
    return true;
}
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
//    node->nodes[i] = app_child->nodes[max_degree / 2];
//    node->nodes[i]->self = node;
    node->how_many++;
    // app_child become left child of that strange kid and new 'rightc' node become the right kid of him
    node_btree *rightc = new node_btree;
    rightc->parent = node;
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
    app_child->parent = node;
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
