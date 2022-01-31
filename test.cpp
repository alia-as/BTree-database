#include "BTree.h"
#include "table.h"
#include <iostream>
#include "hashing.h"
using namespace std;
int main()
{
    int datas[5] = {55000, 20000, 70000, 40000, 67000};
    btree tree;
    cout << tree.do_we_have(1) << "\n";
    for(int i = 0; i < 5; i++)
    {
        tree.push(datas[i]);
        cout << tree.puny() << endl;
        tree.preorder_print();
    }
    for(int i = 0; i < 5; i++)
    {
        cout << tree.do_we_have(datas[i]);
    }
    cout << "\n------------------\n";
    vec<btree_node_section*> woo = tree.nodes_with_condition(45000, "<");
    for(int i = 0; i < woo.len; i++)
    {
        cout << woo.inpos(i)->data << endl;
    }
    cout << "\n------------------\n";
    woo = tree.nodes_with_condition(45000, ">");
    for(int i = 0; i < woo.len; i++)
    {
        cout << woo.inpos(i)->data << endl;
    }
    cout << "\n------------------\n";
    woo = tree.nodes_with_condition(45000, "==");
    for(int i = 0; i < woo.len; i++)
    {
        cout << woo.inpos(i)->data << endl;
    }




//    string fields[6] = {"name", "string", "joinDate", "timestamp", "income", "int"};
//    int inp[3] = {200, 400, 1000};
//    int inp1[3] = {1, 53, 5556};
//    int inp2[3] = {97, 455, 112};
//    int inp3[3] = {-5, 0, 65};
//    table thet("WOw", 3, fields);
//    thet.push(inp);
//    thet.print(0);
//    thet.push(inp1);
//    thet.push(inp2);
//    thet.push(inp3);
//    for(int i = 0; i < 4; i++)
//    {
//        thet.print(i);
//    }
//

}
