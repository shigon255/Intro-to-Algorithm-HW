#include <iostream>
#include <vector>
#include <assert.h>

enum class RB_COLOR
{
    BLACK,
    RED
};

class RB_node
{
public:
    RB_node(int new_val)
        : value(new_val), left(nullptr), right(nullptr), parent(nullptr), color(RB_COLOR::BLACK){}

    RB_node* left;
    RB_node* right;
    RB_node* parent;

    // assume that the key value is int type
    int value; 
    RB_COLOR color;
};

class RB_Tree
{
public:
    RB_Tree()
    {
        tree_null = new RB_node(-1);
        tree_null->color = RB_COLOR::BLACK;
        root = tree_null;
        root->parent = tree_null;
    };

    void left_rotate(RB_node* x);
    void right_rotate(RB_node* x);

    void RB_insert(int new_val);
    void RB_insert_fixup(RB_node* z);

    RB_node* find_node(int find_val);
    void RB_transplant(RB_node* u, RB_node* v);
    RB_node* minimum(RB_node* n);
    RB_node* successor(RB_node* n);

    void RB_delete(int del_val);
    void RB_delete_fixup(RB_node* z);

    // for debug
    void inorder(); //left -> middle -> right
    void inorder_rec(RB_node* n);
    void preorder(); //middle -> left -> right
    void preorder_rec(RB_node* n);

    void show()
    {
        inorder();
        preorder();
        std::cout<<std::endl;
    }

    void HW_show();
    void HW_show_rec(RB_node* n, RB_node* parent);

    RB_node* root;
    RB_node* tree_null;
};

void RB_Tree::inorder()
{
    std::cout<<"Inorder: ";
    inorder_rec(root);
    std::cout<<std::endl;
}

void RB_Tree::inorder_rec(RB_node* n)
{
    if(n == tree_null) return;
    inorder_rec(n->left);
    std::cout<<n->value;
    if(n->color == RB_COLOR::BLACK)
        std::cout<<"(BLACK)";
    else
        std::cout<<"(RED)";
    std::cout<<" ";
    inorder_rec(n->right);
    return;
}

void RB_Tree::preorder()
{
    std::cout<<"Preorder: ";
    preorder_rec(root);
    std::cout<<std::endl;
}

void RB_Tree::preorder_rec(RB_node* n)
{
    if(n == tree_null) return;
    std::cout<<n->value;
    if(n->color == RB_COLOR::BLACK)
        std::cout<<"(BLACK)";
    else
        std::cout<<"(RED)";
    std::cout<<" ";
    preorder_rec(n->left);
    preorder_rec(n->right);
    return;
}

void RB_Tree::left_rotate(RB_node* x)
{
    RB_node* y = x->right;
    x->right = y->left;
    if(y->left != tree_null)
        y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == tree_null) 
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RB_Tree::right_rotate(RB_node* x)
{
    assert(x->left);
    RB_node* y = x->left;
    x->left = y->right;
    if(y->right != tree_null)
        y->right->parent = x;
    y->parent = x->parent;
    if(x->parent == tree_null) 
        root = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RB_Tree::RB_insert(int new_val)
{
    RB_node* y = tree_null;
    RB_node* x = root;

    while(x != tree_null)
    {
        y = x;
        if(new_val < x->value)
            x = x->left;
        else
            x = x->right;
    }

    RB_node* z = new RB_node(new_val);
    z->parent = y;

    if(y == tree_null)
    {
        root = z;
    }
    else if(z->value < y->value)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
        
    z->left = tree_null;
    z->right = tree_null;
    z->color = RB_COLOR::RED;

    //std::cout<<"before_insert_fixup "<<new_val<<std::endl;
    //show();

    RB_insert_fixup(z);
}

void RB_Tree::RB_insert_fixup(RB_node* z)
{
    while(z->parent->color == RB_COLOR::RED)
    {
        //std::cout<<"z: "<<z->value<<std::endl;

        if(z->parent == z->parent->parent->left)
        {
            auto y = z->parent->parent->right;
            if(y->color == RB_COLOR::RED)
            {
                //std::cout<<"Case 1"<<std::endl;
                z->parent->color = RB_COLOR::BLACK;
                y->color = RB_COLOR::BLACK;
                z->parent->parent->color = RB_COLOR::RED;
                z = z->parent->parent;
            }
            else
            {
                //std::cout<<"Case 2 or 3"<<std::endl;
                if(z == z->parent->right)
                {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->color = RB_COLOR::BLACK;
                z->parent->parent->color = RB_COLOR::RED;
                right_rotate(z->parent->parent);
            }            
        }
        else
        {
            auto y = z->parent->parent->left;
            if(y->color == RB_COLOR::RED)
            {
                z->parent->color = RB_COLOR::BLACK;
                y->color = RB_COLOR::BLACK;
                z->parent->parent->color = RB_COLOR::RED;
                z = z->parent->parent;
            }
            else
            {
                if(z == z->parent->left)
                {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = RB_COLOR::BLACK;
                z->parent->parent->color = RB_COLOR::RED;
                left_rotate(z->parent->parent);
            }
        }
    }
    root->color = RB_COLOR::BLACK;
}

RB_node* RB_Tree::find_node(int find_val)
{
    RB_node* ans = tree_null;
    RB_node* itr = root;
    while(itr != tree_null)
    {
        if(itr->value == find_val)
        {
            ans = itr;
            break;
        }
        else if(itr->value < find_val)
        {
            itr = itr->right;
        }
        else
        {
            itr = itr->left;
        }
    }
    return ans;
}

void RB_Tree::RB_transplant(RB_node* u, RB_node* v)
{
    if(u->parent == tree_null)
    {
        root = v;
    }
    else if(u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

RB_node* RB_Tree::minimum(RB_node* n)
{
    while(n->left != tree_null)
        n = n->left;
    return n;
}

RB_node* RB_Tree::successor(RB_node* n)
{
    if(n->right != nullptr)
        return minimum(n->right);
    auto y = n->parent;
    while(y != nullptr && n == y->right)
    {
        n = y;
        y = y->parent;
    }
    return y;
}

void RB_Tree::RB_delete(int del_val)
{
    auto z = find_node(del_val);
    if(z == tree_null)
    {
        std::cout<<"value not found!"<<std::endl;
        return; // val is not in the tree
    }

    RB_node* x = nullptr;
    RB_node* y = nullptr;

    y = z;
    auto y_orig_color = y->color;
    if(z->left == tree_null)
    {
        //std::cout<<"Case 1"<<std::endl;
        x = z->right;
        RB_transplant(z, z->right);
    }
    else if(z->right == tree_null)
    {
        //std::cout<<"Case 2"<<std::endl;
        x = z->left;
        RB_transplant(z, z->left);
    }
    else
    {
        //std::cout<<"Case 3"<<std::endl;
        y = minimum(z->right);
        y_orig_color = y->color;
        x = y->right;
        if(y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            RB_transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_transplant(z, y);
        y->left = z->left;        
        y->left->parent = y;
        y->color = z->color;
    }

    //std::cout<<"before_delete_fixup"<<std::endl;
    //show();

    if(y_orig_color == RB_COLOR::BLACK)
    {
        RB_delete_fixup(x);
    }

    /*
    if(z->left == tree_null && z->right == tree_null)
    {
        y = z;
    }
    else
    {
        y = successor(z);
    }

    if(y->left != tree_null)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }

    x->parent = y->parent;

    if(y->parent == tree_null)
    {
        root = x;
    }
    else if(y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    if(y != z)
    {
        z->value = y->value;
    }

    if(y->color == RB_COLOR::BLACK)
    {
        RB_delete_fixup(x);
    }
    */
    
}

void RB_Tree::RB_delete_fixup(RB_node* x)
{
    while(x != root && x->color == RB_COLOR::BLACK)
    {
        if(x == x->parent->left)
        {
            auto w = x->parent->right;
            if(w->color == RB_COLOR::RED)
            {
                w->color = RB_COLOR::BLACK;
                x->parent->color = RB_COLOR::RED;
                left_rotate(x->parent);
                w = x->parent->right;
            }            
            if(w->left->color == RB_COLOR::BLACK && w->right->color == RB_COLOR::BLACK)
            {
                w->color = RB_COLOR::RED;
                x = x->parent;
            }
            else
            {
                if(w->right->color == RB_COLOR::BLACK)
                {
                    w->left->color = RB_COLOR::BLACK;
                    w->color = RB_COLOR::RED;
                    right_rotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = RB_COLOR::BLACK;
                w->right->color = RB_COLOR::BLACK;
                left_rotate(x->parent);
                x = root;
            }
        }
        else
        {
            auto w = x->parent->left;
            if(w->color == RB_COLOR::RED)
            {
                w->color = RB_COLOR::BLACK;
                x->parent->color = RB_COLOR::RED;
                right_rotate(x->parent);
                w = x->parent->left;
            }
            if(w->right->color == RB_COLOR::BLACK && w->left->color == RB_COLOR::BLACK)
            {
                w->color = RB_COLOR::RED;
                x = x->parent;
            }
            else
            {
                if(w->left->color == RB_COLOR::BLACK)
                {
                    w->right->color = RB_COLOR::BLACK;
                    w->color = RB_COLOR::RED;
                    left_rotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = RB_COLOR::BLACK;
                w->left->color = RB_COLOR::BLACK;
                right_rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = RB_COLOR::BLACK;
}

void RB_Tree::HW_show()
{
    if(root != tree_null)
        HW_show_rec(root, nullptr);
}

void RB_Tree::HW_show_rec(RB_node* n, RB_node* parent)
{
    if(n->left != tree_null)
        HW_show_rec(n->left, n);

    std::cout<<"key: ";
    std::cout<<n->value<<" ";

    std::cout<<"parent: ";
    if(parent && parent != tree_null)
        std::cout<<parent->value<<" ";
    else
        std::cout<<"  ";
    
    std::cout<<"color: ";
    if(n->color == RB_COLOR::BLACK)
        std::cout<<"black";
    else
        std::cout<<"red";
    std::cout<<std::endl;

    if(n->right != tree_null)
        HW_show_rec(n->right, n);
}

int main()
{
    RB_Tree tree;

    int t;
    std::cin>>t; // action times

    for(int _t=0;_t<t;_t++)
    {
        int action, n;
        std::cin>>action>>n;
        assert(action == 1 || action == 2);
        if(action == 1)
        {
            std::vector<int> tmp;
            for(int i=0;i<n;i++)
            {
                int tp;
                std::cin>>tp;
                tmp.push_back(tp);

            }

            for(int i=0;i<n;i++)
            {
                tree.RB_insert(tmp[i]);
            }

            std::cout<<"Insert: ";
            for(int i=0;i<n;i++)
            {
                std::cout<<tmp[i];
                if(i != n-1)
                    std::cout<<", ";
            }
            std::cout<<std::endl;

            tree.HW_show();
        }
        if(action == 2)
        {
            std::vector<int> tmp;
            for(int i=0;i<n;i++)
            {
                int tp;
                std::cin>>tp;
                tmp.push_back(tp);

            }

            for(int i=0;i<n;i++)
            {
                tree.RB_delete(tmp[i]);
            }

            std::cout<<"Delete: ";
            for(int i=0;i<n;i++)
            {
                std::cout<<tmp[i];
                if(i != n-1)
                    std::cout<<", ";
            }
            std::cout<<std::endl;

            tree.HW_show();
        }
        
        
    }

    /* For debugging
    std::vector<int> advance_input_list = 
    {
        2, 8, 25, 33, 89, 74, 18
    };

    for(auto i:advance_input_list)
    {
        tree.RB_insert(i);
        std::cout<<"after insert "<<i<<std::endl;
        tree.show();
    }
    
    char mode;
    std::cout<<"Mode? (Static:S / Dynamic: D): ";
    std::cin>>mode;
    assert(mode == 'S' || mode == 'D');

    std::vector<int> input_list = 
    {
        10, 7, 8, 2, 4, 5, 3, 6, 1
    };

    if(mode == 'S')
    {
        for(auto i:input_list)
        {
            tree.RB_insert(i);
            std::cout<<"after insert "<<i<<std::endl;
            tree.show();
        }
    }
    
    if(mode == 'D')
    {
        int num = 0;
        while(num != -101)
        {
            std::cout<<"insert(I) of delete(D)? ";
            std::cin>>mode;
            assert(mode == 'I' || mode == 'D');
            if(mode == 'I')
            {
                std::cout<<"insert num (-101 to abort): ";
                std::cin>>num;
                tree.RB_insert(num);
                std::cout<<"after insert "<<num<<std::endl;
                tree.show();
            }
            else
            {
                std::cout<<"delete num (-101 to abort): ";
                std::cin>>num;
                tree.RB_delete(num);
                std::cout<<"after delete "<<num<<std::endl;
                tree.show();
            }
        }
    }
    */
}