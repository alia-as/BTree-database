#include<iostream>
using namespace std;
template<typename type>
class vec_node
{
public:
    type value;
    vec_node *left_node, *right_node;
    vec_node():
        value(NULL), left_node(0), right_node(0)
        {

        }
};
template<typename type>
class vec
{
public:
    vec():
        first(0)
        {
            current_pos = first;
            len=0;
        }
    void pushback(type);
    void replace_pos(type , int);
    void popback();
    void sortit();
    void print();
    int whereis(type);
    void delete_all();
    void insert_in_pos(type, int);
    int length();
    type start();
    type finish();
    type inpos(int);
    void swapnodes(int,int);
private:
    int len;
    vec_node<type> *current_pos;
    void printhelper(vec_node<type>*);
    void pushbackhelper(type ,vec_node<type>*, vec_node<type>*&);
    int whereishelper(type , vec_node<type>*, int);
    vec_node<type> *first;
    vec_node<type> *nodeinpos(int);

};
//int main()
//{
////    vec<int> thelist;
////    for (int a=10; a>=0; a--)
////    {
////        thelist.pushback(2*a);
////    }
////    thelist.print();
////    cout << "size = " << thelist.length() << endl;
////    thelist.popback();
////    thelist.popback();
////    cout << "After two pop back the list is:\n";
////    thelist.print();
////    cout << "size = " << thelist.length() << endl;
////    printf("8 is in the %d position and 100 is in %d position\n", thelist.whereis(8), thelist.whereis(100));
////    printf("start is %d and finish is %d\n", thelist.start(), thelist.finish());
////    printf("This is %d in pos 2\n", thelist.inpos(2));
////    thelist.sortit();
////    cout << "After Sorting:\n";
////    thelist.print();
////    thelist.insert_in_pos(100, 4);
////    thelist.print();
////    thelist.delete_all();
////    thelist.print();
//}
template<typename type>
void vec<type>::pushback(type what)
{
    pushbackhelper(what,0, first);
//    sortedpushbackhelper(what, 0,sfirst);
}
template <typename type>
void vec<type>::pushbackhelper(type what,vec_node<type> *last, vec_node<type>*& node)
{
    if(!node)
    {
        node = new vec_node<type>;
        node->value = what;
        node->left_node = last;
        current_pos = node;
        len++;
    }
    else
    {
        pushbackhelper(what,node, node->right_node);
    }
}
template<typename type>
void vec<type>::print()
{
    cout << "\nprinting\n";
    printhelper(first);
    cout << "\n\t--------------------------------------------------\n" ;
}
template<typename type>
void vec<type>::printhelper(vec_node<type> *node)
{
    if(node)
    {
        cout << node->value << " ";
        if(node != current_pos)
        {
            printhelper(node->right_node);
        }
    }
}
template<typename type>
void vec<type>::popback()
{
    current_pos = current_pos->left_node;
    current_pos->right_node =0;
    len--;
}
template<typename type>
int vec<type>::whereis(type what)
{
    return whereishelper(what, first, 0);
}
template<typename type>
int vec<type>::whereishelper(type what, vec_node<type>* vecpos, int pos)
{
    if(vecpos->value == what )
    {
        return pos;
    }
    else
    {
        if(vecpos == current_pos)
        {
            return -1;
        }
        else
        {
            return whereishelper(what, vecpos->right_node, pos+1);
        }
    }
}
template<typename type>
type vec<type>::start()
{
    return first->value;
}
template<typename type>
type vec<type>::finish()
{
    return current_pos->value;
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
template<typename type>
void vec<type>::delete_all()
{
    while(current_pos != first)
    {
        popback();
    }
    current_pos=0;
    first =0 ;
    cout << "The inc Vector is destructed!!\n";
}
template<typename type>
void vec<type>::insert_in_pos(type what, int pos)
{
    if(pos >= len)
    {
        cerr << "Out of range!!!\n";
    }
    vec_node<type> *node = current_pos;
    type *templist = new type[len-pos];
    for(int a=0; a<len-pos; a++)
    {
        templist[a] = node->value;
        node = node->left_node;
        popback();
        len++;
    }
    pushback(what);
    len--;
    for(int a=len-pos-1; a>=0; a--)
    {
        pushback(templist[a]);
        len--;
    }
    len++;
}
template<typename type>
void vec<type>::swapnodes(int pos1, int pos2)
{
    type temp = inpos(pos1);
    nodeinpos(pos1)->value = inpos(pos2);
    nodeinpos(pos2)->value = temp;
}
template<typename type>
int vec<type>::length()
{
    return len;
}
template<typename type>
void vec<type>::sortit()
{
    for(int a=0; a<len; a++)
    {
        for(int b=a+1; b<len; b++)
        {
            if(inpos(a) > inpos(b))
            {
                swapnodes(a,b);
            }
        }
    }
}
template<typename type>
void vec<type>::replace_pos(type what, int pos)
{
    nodeinpos(pos)->value = what;
}
