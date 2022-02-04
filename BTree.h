#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include<iostream>
#include<string>
#include "vector.h"
using namespace std;
bool debug_btree = false;
const unsigned int max_degree = 4;
class btree_node;
class btree_node_section
{
public:
    long long data = 0;
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
    btree_node_section* push(long long);
    void del(long long);
    void split(btree_node*);
    void preorder_print();
    void preorder_print_helper(btree_node*);
    bool do_we_have(long long);
    int puny();
    vec<btree_node_section*> nodes_with_condition(long long, string);
    vec<btree_node_section*> equalsto(long long);
    vec<btree_node_section*> lessthan(long long);
    vec<btree_node_section*> morethan(long long);
    vec<btree_node_section*> equalsto_helper(long long, btree_node*, int);
    vec<btree_node_section*> lessthan_helper(long long, btree_node*, int);
    vec<btree_node_section*> morethan_helper(long long, btree_node*, int);


};
void btree::del(long long item)
{
    if(!root)
    {
        return;
    }
    btree_node *temp = root;
    int i = 0;
    while(true)
    {
        i = 0;
        while(temp->nodes[i] && temp->nodes[i]->data < item)
        {
            i++;
        }
        if(temp->nodes[i] && temp->nodes[i]->data == item)
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
                return;
            }
        }
    }
    // Now we find that item, it is in temp at position i
    if(temp->children[i]) // If it is not a leaf change it by its predecessor
    {
        btree_node *prefinder = temp->children[i];
        while(prefinder->children[prefinder->how_many])
        {
            prefinder = prefinder->children[prefinder->how_many];
        }
        btree_node_section *predecessor = prefinder->nodes[prefinder->how_many - 1];
        prefinder->nodes[prefinder->how_many - 1] = temp->nodes[i];
        temp->nodes[i] = predecessor;
        temp = prefinder;
        i = temp->how_many - 1;
    }
    // Now temp is a leaf
    temp->shifting(true, i);
    if(temp->how_many > max_degree / 2 || temp == root) // easy deletion
    {
        temp->how_many--;
        return;
    }
    else
    {
        btree_node *rs = (temp->which_child < temp->parent->how_many) ? temp->parent->children[temp->which_child + 1] : 0; // Right sibling
        btree_node *ls = (temp->which_child > 0) ? temp->parent->children[temp->which_child - 1] : 0; // Left sibling
        if(ls && ls->how_many > max_degree / 2)
        {
            temp->shifting(false, 0);
            temp->nodes[0] = temp->parent->nodes[temp->which_child - 1];
            temp->parent->nodes[temp->which_child - 1] = ls->nodes[ls->how_many - 1];
            ls->nodes[ls->how_many - 1] = 0;
            ls->how_many--;

        }
        else if(rs && rs->how_many > max_degree / 2)
        {
            temp->nodes[temp->how_many - 1] = temp->parent->nodes[temp->which_child];
            temp->parent->nodes[temp->which_child] = rs->nodes[0];
            rs->shifting(true, 0);
            rs->how_many--;

        }
        else // We have to merge temp
        {
            if(ls)
            {
                ls->nodes[ls->how_many] = ls->parent->nodes[ls->which_child];
                ls->how_many++;
                for(int q = 0; q < temp->how_many - 1; q++)
                {
                    ls->nodes[ls->how_many] = temp->nodes[q];
                    ls->how_many++;

                }
                ls->parent->shifting(true, ls->which_child);
                ls->parent->how_many--;
                if(ls->parent->how_many == 0)
                {
                    if(ls->parent == root)
                    {
                        root = ls;
                    }
                    else
                    {
                        ls->parent->parent->children[ls->parent->which_child] = ls;
                        ls->which_child = ls->parent->which_child;
                    }
                }

            }
            else if(rs)
            {
                temp->nodes[temp->how_many - 1] = temp->parent->nodes[temp->which_child];
                for(int q = 0; q < rs->how_many; q++)
                {
                    temp->nodes[temp->how_many] = rs->nodes[q];
                    temp->how_many++;
                }
                temp->parent->shifting(true, temp->which_child);
                temp->parent->how_many--;
                if(temp->parent->how_many == 0)
                {
                    if(temp->parent == root)
                    {
                        root = temp;
                    }
                    else
                    {
                        temp->parent->parent->children[temp->parent->which_child] = temp;
                        temp->which_child = temp->parent->which_child;
                    }
                }

            }
        }

    }

}
vec<btree_node_section*> btree::nodes_with_condition(long long val, string sign)
{
    vec<btree_node_section*> ans;
    if(sign == "<")
    {
        ans = lessthan(val);
    }
    else if(sign == "==")
    {
        ans = equalsto(val);
    }
    else if(sign == ">")
    {
        ans = morethan(val);
    }
    return ans;
}
vec<btree_node_section*> btree::equalsto(long long val)
{
    return equalsto_helper(val, root, 0);
}
vec<btree_node_section*> btree::equalsto_helper(long long val, btree_node *node, int pos)
{
    vec<btree_node_section*> ans, temp;
    while(node->nodes[pos] && node->nodes[pos]->data < val)
    {
        pos++;
    }
    if(node->nodes[pos])
    {
        if(node->nodes[pos]->data == val)
        {
            ans.pushback(node->nodes[pos]);
            if(node->children[pos])
            {
                temp = equalsto_helper(val, node->children[pos], 0);
                ans.concat_with(temp);
            }
            if(node->children[pos + 1])
            {
                temp = equalsto_helper(val, node->children[pos + 1], 0);
                ans.concat_with(temp);
            }
        }
        else if(node->children[pos])
        {
            return equalsto_helper(val, node->children[pos], 0);
        }
    }
    return ans;
}
vec<btree_node_section*> btree::lessthan(long long val)
{
    return lessthan_helper(val, root, 0);
}
vec<btree_node_section*> btree::lessthan_helper(long long val, btree_node *node, int pos)
{
    vec<btree_node_section*> ans, temp;
    while(node->nodes[pos] && node->nodes[pos]->data < val)
    {
        ans.pushback(node->nodes[pos]);
        if(node->children[pos])
        {
            temp = lessthan_helper(val, node->children[pos], 0);
            ans.concat_with(temp);
        }
        pos++;

    }
    if(!node->nodes[pos] && node->children[pos])
    {
        temp = lessthan_helper(val, node->children[pos], 0);
        ans.concat_with(temp);

    }
    if(node->nodes[pos] && node->nodes[pos]->data >= val && node->children[pos])
    {
        temp = lessthan_helper(val, node->children[pos], 0);
        ans.concat_with(temp);

    }

    return ans;
}
vec<btree_node_section*> btree::morethan(long long val)
{
    return morethan_helper(val, root, 0);
}
vec<btree_node_section*> btree::morethan_helper(long long val, btree_node *node, int pos)
{
    vec<btree_node_section*> ans;
    while(node->nodes[pos] && node->nodes[pos]->data <= val)
    {
        pos++;
    }
    if(node->nodes[pos])
    {
        for(int i = pos; i < node->how_many; i++)
        {
            ans.pushback(node->nodes[i]);
        }
        for(int i = pos; i < node->how_many + 1; i++)
        {
            if(node->children[i])
            {
                vec<btree_node_section*> temp = morethan_helper(val, node->children[i], 0);
                ans.concat_with(temp);

            }
        }
    }
    else if(node->children[node->how_many])
    {
        return morethan_helper(val, node->children[node->how_many], 0);
    }
    return ans;
}
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
btree_node_section* btree::push(long long val)
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

    }
    btree_node *temp = root;
    while(temp->children[0])
    {
        i = 0;
        while(temp->nodes[i] && temp->nodes[i]->data < val)
        {
            i++;
        }
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
    i = 0;
    while(temp->nodes[i] && temp->nodes[i]->data < val)
    {
        i++;
    }

    temp->shifting(false, i);
    temp->nodes[i] = new btree_node_section;
    temp->nodes[i]->data = val;
    temp->nodes[i]->self = temp;
    temp->how_many++;
    return temp->nodes[i];


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
bool btree::do_we_have(long long val)
{
    if(!root)
    {
        return false;
    }
    btree_node *temp = root;
    int i = 0;
    while(true)
    {
        i = 0;
        while(temp->nodes[i] && temp->nodes[i]->data < val)
        {
            i++;
        }
        if(temp->nodes[i] && temp->nodes[i]->data == val)
        {
            return true;
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
}
int btree::puny()
{
    int i = 1;
    while(true)
    {
        if(do_we_have(i))
        {
            i++;
        }
        else
        {
            return i;
        }
    }
}
#endif // BTREE_H_INCLUDED
