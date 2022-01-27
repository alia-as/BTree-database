#include "BTree.h"
#include "table.h"
#include <iostream>
using namespace std;
int main()
{
    int datas[11] = {10, 1, 3, 2, 50, 6, 5, 5, 4, 7, 8};
    btree tree;
    for(int i = 0; i < 11; i++)
    {
        tree.push(datas[i]);
        tree.preorder_print();
    }
    for(int i = 0; i < 11; i++)
    {
        cout << tree.do_we_have(datas[i]);
    }
    cout << "\n" << tree.do_we_have(100) << "\n";
    cout << tree.puny() << "\n";



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


}
