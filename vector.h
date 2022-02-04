#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include<iostream>
using namespace std;
template<typename type>
class vec_node
{
public:
    type value;
    vec_node *right_node = 0;
};
template<typename type>
class vec
{
public:
    void pushback(type);
    void sorted_pushback(type);
    type inpos(int);
    int len = 0;
    void print();
    void concat_with(vec<type>);
private:
    vec_node<type> *last_pos = 0;
    vec_node<type> *first = 0;
    vec_node<type> *nodeinpos(int);

};
template<typename type>
void vec<type>::sorted_pushback(type val)
{
    if(!first)
    {
        first = new vec_node<type>;
        first->value = val;
        last_pos = first;
        len++;
        return;
    }
    else if(first->value->data >= val->data)
    {
        vec_node<type> *newfirst = new vec_node<type>;
        newfirst->value = val;
        newfirst->right_node = first;
        first = newfirst;
        len++;
        return;
    }
    vec_node<type> *temp = first;
    while(temp->right_node && temp->right_node->value->data < val->data)
    {
        temp = temp->right_node;
    }
    if(temp->right_node)
    {
        vec_node<type>* ins = new vec_node<type>;
        ins->value = val;
        ins->right_node = temp->right_node;
        temp->right_node = ins;
    }
    else
    {
        temp->right_node = new vec_node<type>;
        temp->right_node->value = val;
        last_pos = temp->right_node;
    }
    len++;
}
template<typename type>
void vec<type>::concat_with(vec<type> another)
{
    if(!another.first)
    {
        return;
    }
    if(!first)
    {
        first = another.first;
        last_pos = another.last_pos;
        len = another.len;
        return;
    }
    last_pos->right_node = another.first;
    last_pos = another.last_pos;
    len += another.len;
}
template<typename type>
void vec<type>::print()
{
    cout << "Printing: ";
    vec_node<type> *temp = first;
    while(temp)
    {
        cout << temp->value->data << " ";
        temp = temp->right_node;
    }
    cout << "\n";
}
template<typename type>
void vec<type>::pushback(type what)
{
    if(!first)
    {
        first = new vec_node<type>;
        first->value = what;
        last_pos = first;
    }
    else
    {
        last_pos->right_node = new vec_node<type>;
        last_pos->right_node->value = what;
        last_pos = last_pos->right_node;
    }
    len++;

}
template<typename type>
vec_node<type>* vec<type>::nodeinpos(int pos)
{
    vec_node<type> *node = first;
    for(int a=0; a<pos; a++)
    {
        node = node->right_node;
    }
    return node;
}
template<typename type>
type vec<type>::inpos(int pos)
{
    if(pos >= len)
    {
        throw("Out of range!!!\n");
    }
    else
    {
        return nodeinpos(pos)->value;
    }
    return 0;
}




#endif // VECTOR_H_INCLUDED
