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
        cout << temp->value << " ";
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
        cerr << "Out of range!!!\n";
    }
    else
    {
        return nodeinpos(pos)->value;
    }
}

