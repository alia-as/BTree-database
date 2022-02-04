#include<iostream>
using namespace std;
const unsigned int max_degree = 4;
// A simple vector
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
// Building the tree
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
class table
{
    public:
    string name;
    int *types; // A list of types, 0 for int, 1 for string, 2 for timestamp. if 3 that's undefined
    string *tree_names;
    btree *bjungle;
    unsigned int field_count;
    table(string, int, string[]);
    void push(long long[]);
    vec<btree_node_section*> nodes_with_condition(string, string, string);
    vec<btree_node_section*> nodes_with_2condition(string[], string);
    void print_with_conditions(string[], string*, int, string sign = "");
    void update(string[], string[], string sign = "");
    void deleteee(string[], string sign = "");


};
void query_analizer(string);
string *tokenize(string, int&);
bool is_letter(int);
table **tables = new table*[1];
int table_count = 0, table_size = 1;
table *find_table(string);
string* tokenize_and_check_syntax(string, int&);
string to_capital(string);
int sint2int(string num );
string int2sint(int num);
int timestamp2int(string timestamp);
string int2timestamp(int date);
long long string2int(string name);
string int2string(long long num);


int main()
{
    string query = "";
    int queries = 0, lim;
    cin >> lim;
    while(queries <= lim)
    {
        getline(cin, query);
        try
        {
            if(query != "")
            {
                query_analizer(query);
            }
        }
        catch(char const* msg)
        {
            cout << msg;
        }
        catch(string msg)
        {
            cout << msg;
        }
        queries++;
    }
}




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

void table::deleteee(string conditions[], string sign)
{
    vec<btree_node_section*> nodes;
    if(sign == "")
    {
        nodes = nodes_with_condition(conditions[0], conditions[1], conditions[2]);
    }
    else
    {
        nodes = nodes_with_2condition(conditions, sign);
    }
    for(int q = 0; q < nodes.len; q++)
    {
        btree_node_section *now = nodes.inpos(q);
        for(int w = 0; w < field_count; w++)
        {
            bjungle[w].del(now->data);
            now = now->nextField;
        }
    }
}
void table::update(string conditions[], string fields[], string sign)
{
    long long datas[field_count - 1];
    for(int w = 0; w < field_count - 1; w++)
    {
        if(types[w + 1] == 0)
        {
            datas[w] = sint2int(fields[w]);
        }
        else if(types[w + 1] == 1)
        {
            datas[w] = string2int(fields[w]);
        }
        else if(types[w + 1] == 2)
        {
            datas[w] = timestamp2int(fields[w]);
        }
    }
    vec<btree_node_section*> nodes;
    if(sign == "")
    {
        nodes = nodes_with_condition(conditions[0], conditions[1], conditions[2]);
    }
    else
    {
        nodes = nodes_with_2condition(conditions, sign);
    }
    for(int i = 0; i < nodes.len; i++)
    {
        btree_node_section* now = nodes.inpos(i);
        now = now->nextField;
        for(int q = 0; q < field_count - 1; q++)
        {
            now->data = datas[q];
            now = now->nextField;
        }
    }
}
void table::print_with_conditions(string conditions[], string *fields, int counts, string sign)
{
    vec<btree_node_section*> nodes;
    if(sign == "")
    {
        nodes = nodes_with_condition(conditions[0], conditions[1], conditions[2]);

    }
    else
    {
        nodes = nodes_with_2condition(conditions, sign);

    }
    bool needed[field_count];
    if(counts == field_count)
    {
        for(int i = 0; i < field_count; i++)
        {
            needed[i] = true;
        }
    }
    else
    {
        for(int q = 0; q < field_count; q++)
        {
            needed[q] = false;
            for(int w = 0; w < counts; w++)
            {
                if(tree_names[q] == fields[w])
                {
                    needed[q] = true;
                    break;
                }
            }
        }
    }
    for(int r = 0; r < nodes.len; r++)
    {
        btree_node_section *now = nodes.inpos(r);
        for(int pos = 0; pos < field_count; pos++)
        {
            if(needed[pos])
            {
                if(types[pos] == 0)
                {
                    cout << now->data << " ";
                }
                else if(types[pos] == 1)
                {
                    cout << int2string(now->data) << " ";
                }
                else if(types[pos] == 2)
                {
                    cout << int2timestamp(now->data) << " ";
                }

            }
            now = now->nextField;
        }
        cout << "\n";
    }
}
vec<btree_node_section*> table::nodes_with_2condition(string conditions[], string andor)
{
    vec<btree_node_section*> first = nodes_with_condition(conditions[0], conditions[1], conditions[2]);
    vec<btree_node_section*> second = nodes_with_condition(conditions[3], conditions[4], conditions[5]);
    vec<btree_node_section*> ans;
    int a = 0, b = 0;
    while(a < first.len || b < second.len)
    {
            while(a < first.len && (b >= second.len || first.inpos(a)->data < second.inpos(b)->data))
            {
                if(andor == "|")
                {
                    ans.pushback(first.inpos(a));

                }
                a++;
            }
            while(b < second.len && (a >= first.len || first.inpos(a)->data > second.inpos(b)->data))
            {
                if(andor == "|")
                {
                    ans.pushback(second.inpos(b));

                }
                b++;
            }
            if(a < first.len && b < second.len && first.inpos(a)->data == second.inpos(b)->data)
            {
                ans.pushback(first.inpos(a));
                a++;
                b++;
            }

    }
    return ans;
}
vec<btree_node_section*> table::nodes_with_condition(string which, string sign, string val)
{
    int i;
    for(i = 0; i < field_count; i++)
    {
        if(tree_names[i] == which)
        {
            break;
        }
    }
    // Now i is the tree which we set rules to that
    // find int of given value
    long long valint;
    if(types[i] == 0)
    {
        valint = sint2int(val);
    }
    else if(types[i] == 1)
    {
        valint = string2int(val);
    }
    else if(types[i] == 2)
    {
        valint = timestamp2int(val);
    }
    btree tree = bjungle[i];
    vec<btree_node_section*> ans, that_tree_nodes = tree.nodes_with_condition(valint, sign);
    for(int q = 0; q < that_tree_nodes.len; q++)
    {
        btree_node_section* t = that_tree_nodes.inpos(q);

    }

    for(int q = 0; q < that_tree_nodes.len; q++)
    {
        btree_node_section* t = that_tree_nodes.inpos(q);
        for(int w = 0; w < field_count - i; w++)
        {
            t = t->nextField;

        }
        ans.sorted_pushback(t);

    }
    return ans;


}
table::table(string the_name, int fields, string fields_names[]) // Len of fields_names is 2 * fields
{
    name = the_name;
    bjungle = new btree[fields + 1];
    types = new int[fields + 1];
    tree_names = new string[fields + 1];
    field_count = fields + 1;
    types[0] = 0;
    tree_names[0] = "ID";
    for(int i = 0; i < fields; i++)
    {
        string type = fields_names[2 * i + 1];
        types[i + 1] = (type == "int") ? 0 : (type == "string") ? 1 : (type == "timestamp") ? 2 : 3;
        tree_names[i + 1] = fields_names[2 * i];
    }

}
void table::push(long long datas[])
{
    int first_id = bjungle[0].puny();
    btree_node_section *now = bjungle[0].push(first_id), *temp, *first;
    first = now;
    for(int i = 1; i < field_count; i++)
    {
        temp = now;
        now = bjungle[i].push(datas[i - 1]);
        temp->nextField = now;

    }
    now->nextField = first;

}

void query_analizer(string query)
{
    int counts = 0;
    string* query_tokens = tokenize_and_check_syntax(query, counts);
    string command = query_tokens[0];
    if(command == "CREATE")
    {
        string table_name = query_tokens[2];
        for(int i = 0; i < table_count; i++)
        {
            if(tables[i]->name == table_name)
            {
                throw ("Table already exist!\n");

            }
        }
        int fc = ((counts - 5) + 1) / 3, controller = 0;
        string f[fc * 2];
        for(int i = 4; i < counts; i++)
        {
            if(i % 3)
            {
                f[controller] = query_tokens[i];
                controller++;
            }
        }
        if(table_count < table_size)
        {
            tables[table_count] = new table(table_name, controller / 2, f);

        }
        else
        {
            table **temp = new table*[2 * table_size];
            for(int i = 0; i < table_count; i++)
            {
                temp[i] = tables[i];
            }
            temp[table_count] = new table(table_name, controller / 2, f);
            tables = temp;
        }
        table_count++;


    }
    else if(command == "INSERT")
    {
        string table_name = query_tokens[2];
        table *right_one;
        try
        {
            right_one = find_table(table_name);
        }
        catch(char const* msg)
        {
            cout << msg;
            return;
        }
        long long datas[right_one->field_count - 1], ind = 0;
        for(int i = 5; ind < right_one->field_count - 1; i += 2)
        {
            int type = right_one->types[ind + 1];
            if(type == 0) // int
            {
                datas[ind] = sint2int(query_tokens[i]);
                ind++;
            }
            else if(type == 1) // string
            {
                datas[ind] = string2int(query_tokens[i]);
                ind++;
            }
            else if(type == 2) // time stamp
            {
                datas[ind] = timestamp2int(query_tokens[i]);
                ind++;
            }

        }
        right_one->push(datas);

    }
    else if(command == "UPDATE")
    {
        table * t = find_table(query_tokens[1]);
        string fields[t->field_count - 1];
        int index = 0, pos = 4;
        for(pos = 4; index < t->field_count - 1; pos += 2)
        {
            fields[index] = query_tokens[pos];
            index++;
        }
        if(counts > pos + 5)
        {
            string cons[6] = {query_tokens[pos + 1], query_tokens[pos + 2], query_tokens[pos + 3],
            query_tokens[pos + 5], query_tokens[pos + 6], query_tokens[pos + 7]};
            t->update(cons, fields, query_tokens[pos + 4]);
        }
        else
        {
            string cons[3] = {query_tokens[pos + 1], query_tokens[pos + 2], query_tokens[pos + 3]};
            t->update(cons, fields);
        }

    }
    else if(command == "SELECT")
    {
        int how_many = 0, pos = 1, needed_fields;
        table* t = 0;
        string *fields = 0;
        if(query_tokens[1] == "*")
        {
            string q[0];
            t = find_table(query_tokens[3]);
            needed_fields = t->field_count;

        }
        else
        {
            pos = 2;
            int index = 0;
            while(query_tokens[pos] != ")")
            {
                pos++;
            }
            needed_fields = (pos - 1) / 2;
            fields = new string[needed_fields];
            pos = 2;
            while(query_tokens[pos] != ")")
            {
                if(query_tokens[pos] == ",")
                {
                    index++;
                }
                else
                {
                    fields[index] = query_tokens[pos];
                }
                pos++;
            }
            t = find_table(query_tokens[pos + 2]);

        }
        if(counts < pos + 5)
        {
            string cons[3] = {"ID", ">", "0"};
            t->print_with_conditions(cons, fields, needed_fields);
        }
        if(counts < pos + 8)
        {
            string cons[3] = {query_tokens[pos + 4], query_tokens[pos + 5], query_tokens[pos + 6]};
            t->print_with_conditions(cons, fields, needed_fields);
        }
        else
        {
            string cons[6] = {query_tokens[pos + 4], query_tokens[pos + 5], query_tokens[pos + 6],
            query_tokens[pos + 8], query_tokens[pos + 9], query_tokens[pos + 10]};
            t->print_with_conditions(cons, fields, needed_fields, query_tokens[pos + 7]);
        }
    }
    else if(command == "DELETE")
    {
        table *thet = find_table(query_tokens[2]);
        if(counts > 8)
        {
            string cons[6] = {query_tokens[4], query_tokens[5], query_tokens[6],
            query_tokens[8], query_tokens[9], query_tokens[10]};
            thet->deleteee(cons, query_tokens[7]);
        }
        else
        {
            string cons[3] = {query_tokens[4], query_tokens[5], query_tokens[6]};
            thet->deleteee(cons);
        }

    }

}
string *tokenize(string text, int &counts)
{
    string *ans = new string[1], *temp;
    counts = 0;
    int ans_size = 1;
    string word = "";
    bool is_let = true, is_name = false;
    int i = -1;
    for(i = 0; i < text.size(); i++)
    {
        int now = (int)text[i];
        if(text[i] == '"')
        {
            if(counts == ans_size)
            {
                temp = new string[2 * ans_size];
                for(int j = 0; j < 2 * ans_size; j++)
                {
                    temp[j] = "";

                }
                for(int j = 0; j < ans_size; j++)
                {
                    temp[j] = ans[j];

                }
                temp[counts] = word;
                ans = temp;
                ans_size *= 2;
            }
            else
            {
                ans[counts] = word;
            }
            counts++;
            word = text[i];
            i++;
            while(text[i] != '"')
            {
                word += text[i];
                i++;
            }
            word += text[i];
            if(counts == ans_size)
            {
                temp = new string[2 * ans_size];
                for(int j = 0; j < 2 * ans_size; j++)
                {
                    temp[j] = "";

                }
                for(int j = 0; j < ans_size; j++)
                {
                    temp[j] = ans[j];

                }
                temp[counts] = word;
                ans = temp;
                ans_size *= 2;
            }
            else
            {
                ans[counts] = word;
            }
            counts++;
            word = "";
            continue;
        }

        if((!is_letter(now) && is_let) || (!is_let && is_letter(now)))
        {
            if(counts == ans_size)
            {
                temp = new string[2 * ans_size];
                for(int j = 0; j < 2 * ans_size; j++)
                {
                    temp[j] = "";

                }
                for(int j = 0; j < ans_size; j++)
                {
                    temp[j] = ans[j];

                }
                temp[counts] = word;
                ans = temp;
                ans_size *= 2;
            }
            else
            {
                ans[counts] = word;
            }
            if(word != "")
            {
                counts++;
            }
            if(text[i] != ' ')
            {
                word = text[i];
            }
            else
            {
                word = "";
            }
            is_let = !is_let;
        }
        else if(text[i] != ' ')
        {
            word += text[i];
        }
    }
    if(counts == ans_size)
    {
        temp = new string[2 * ans_size];
        for(int j = 0; j < 2 * ans_size; j++)
        {
            temp[j] = "";

        }
        for(int j = 0; j < ans_size; j++)
        {
            temp[j] = ans[j];

        }
        temp[ans_size] = word;
        ans = temp;
        ans_size *= 2;
    }
    else
    {
        ans[counts] = word;
    }
    word = "";
    counts++;
    return ans;
}
table *find_table(string table_name)
{
    table *right_one = 0;
    for(int i = 0; i < table_count; i++)
    {
        if(tables[i]->name == table_name)
        {
            right_one = tables[i];
        }
    }
    if(!right_one)
    {
        throw ("Table does not exist!\n");
    }
    else
    {
        return right_one;
    }
}
bool is_letter(int n)
{
    if((n >= 97 && n <= 122) || (n >= 65 && n <= 90) || (n >= 47 && n <= 57) || (n == 95))
    {
        return true;
    }
    else
    {
        return false;
    }
}
string* tokenize_and_check_syntax(string query, int& counts)
{
    string *ans = tokenize(query, counts);
    string comcheck = to_capital(ans[0]);
    if(comcheck == "INSERT" || comcheck == "SELECT" || comcheck == "DELETE" || comcheck == "UPDATE" || comcheck == "CREATE")
    {
        if(comcheck != ans[0])
        {

            cerr << "We capitalize it but keep attention to write statements with capital letters!\n";
            ans[0] = comcheck;
        }
    }
    else
    {
        throw("The statement is invalid :(\n");
    }
    if(ans[0] == "CREATE")
    {
        if(to_capital(ans[1]) != "TABLE")
        {
            throw("Creating table format must be like this:\nCREATE TABLE {table name} (column1 type,column2 type,...)\n");
        }
        for(int i = 6; ans[i] != ")"; i+=3)
        {
            if(ans[i] != ",")
            {
                throw("Maybe you forgot to put comma or parenthesis!\n");
            }
            if((ans[i - 1] != "int") && (ans[i - 1] != "string") && (ans[i - 1] != "timestamp"))
            {
                throw("Types must be int, string or timestamp!\n");
            }
        }
    }
    else if(ans[0] == "INSERT")
    {
        if(ans[1] != "INTO" || ans[3] != "VALUES")
        {
            throw("Insertion format must be like this:\nINSERT INTO {table name} VALUES (field1,field2,...)\n");
        }
        for(int i = 6; ans[i] != ")"; i+=2)
        {
            if(ans[i] != ",")
            {
                throw("Maybe you forgot to put comma or parenthesis!\n");
            }
        }
    }
    else if(ans[0] == "SELECT")
    {
        if(ans[1] == "*")
        {
            if(ans[2] != "FROM")
            {
                throw("Maybe you forgot to write FROM!\n");
            }
        }
        else if(ans[1] == "(")
        {
            int i;
            for(i = 3; ans[i] != ")"; i+=2)
            {
                if(ans[i] != ",")
                {
                    throw("Maybe you forgot to put comma or parenthesis!\n");
                }
            }
            if(ans[i + 1] != "FROM")
            {
                throw("Maybe you forgot to write FROM!\n");
            }

        }
        else
        {
            throw("Selection format has just 2 formats:\n1. SELECT * FROM {table name} WHERE {condition}\nor\n2. SELECT (column1,column2,...) FROM {table name} WHERE {condition}\n");
        }
    }
    else if(ans[0] == "DELETE")
    {
        if(ans[1] != "FROM")
        {
            throw("Deletion format must be like this:\nDELETE FROM {table name} WHERE {condition}\n");
        }
        if(ans[3] != "WHERE")
        {
            throw("Deletion must have some conditions specifies with WHERE!\n");
        }
    }
    else if(ans[0] == "UPDATE")
    {
        if(ans[2] != "SET")
        {
            throw("Update format must be like this:\nUPDATE {table name} SET (field1,field2,...) WHERE {condition}\n");
        }
        for(int i = 5; ans[i] != ")"; i+=2)
        {
            if(ans[i] != ",")
            {
                throw("Maybe you forgot to put comma or parenthesis!\n");
            }
        }
    }

    return ans;
}
string to_capital(string text)
{
    string woo = "";
    for(int i = 0; i < text.size(); i++)
    {
        if(text[i] >= 'a' && text[i] <= 'z')
        {
            woo = woo + (char)((int)text[i] - 32);
        }
        else
        {
            woo = woo + text[i];
        }
    }
    return woo;
}

int sint2int(string num )
{
    int k = 1;
    int n= num.size();
    // For handling negative numbers
    if (num.substr(0,1) == "-")
    {
        k=-1;
        n--;
        num = num.substr(1);
    }
    int ans=0;
    for (int r=0 ; r<n ; r++)
    {
        if(num[r] < '0' || num[r] > '9')
        {
            throw("It seems that's not a integer here!\n");
        }
        ans = ans*10 + ((int)num[r] - 48);
    }
    return ans*k;
}
string int2sint(int num)
{
	string ans;
	string sign = "";
	if(num < 0){sign = "-";}
	while( num>0)
	{
		int a = num%10;
		ans = (char)(a+48) + ans;
		num /= 10;
	}
	if (ans.size() == 0){ans = "0";}
	ans = sign + ans;
	return ans;
}
int timestamp2int(string timestamp)
{
    string year = "", month = "", day = "";
    int mode = 0;
    for(int i = 0; i < timestamp.size(); i++)
    {
        if(timestamp[i] == '/')
        {
            mode++;
            continue;
        }
        if(mode == 0)
        {
            year += timestamp[i];
        }
        else if(mode == 1)
        {
            month += timestamp[i];
        }
        else if(mode == 2)
        {
            day += timestamp[i];
        }
    }
    int y = sint2int(year), m = sint2int(month), d = sint2int(day);
    if(m > 12)
    {
        throw("I've never seen month no." + month + " in a year!!\n");
    }
    else if(m < 1)
    {
        throw("Maybe you forgot to write a month?!\n");
    }
    if(d > 31)
    {
        throw("A month has just 31 days, so day " + day + " is invalid!! :(\n");
    }
    else if(d < 1)
    {
        throw("Maybe you forgot to write a day?!\n");
    }
    return 372 * y + 31 * (m - 1) + d - 1;

}
string int2timestamp(int date)
{
    int year = date / 372;
    date = date % 372;
    int month = date / 31 + 1, day = date % 31 + 1;
    return int2sint(year) + "/" + int2sint(month) + "/" + int2sint(day);


}
long long string2int(string name)
{
    long long ans = 0, temp;
    if(name[0] != '"' || name[name.size() - 1] != '"')
    {
        throw("It seems this is not a string or you forgot to put quotation marks!\n");
    }
    name = name.substr(1, name.size() - 2);
    for(int i = 0; i < name.size(); i++)
    {
        temp = (int)name[i];
        if(temp >= 48 && temp <= 57)
        {
            temp -= 48;
        }
        else if(temp >= 97 && temp <= 122)
        {
            temp -= 87;
        }
        else
        {
            throw("String has unusual characters!!\n");
        }
        ans *= 36;
        ans += temp;
    }
    return ans;
}
string int2string(long long num)
{
    string name = "";
    char temp;
    while(num > 0)
    {
        if(num % 36 < 10)
        {
            temp = (num % 36 + 48);
        }
        else
        {
            temp = (num % 36 + 87);
        }
        name = temp + name;
        num /= 36;
    }
    return name;
}
