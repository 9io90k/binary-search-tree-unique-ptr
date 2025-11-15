#include <iostream>
#include <memory>
class BinaryTree
{
    struct Node
    {
        int val;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node* parent;
        Node(int v, Node* p = nullptr) : val(v), parent(p), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root = nullptr;

    void inorder(Node* node) const
    {
        if(!node) return;
        inorder(node->left.get());
        std::cout << node->val << " ";
        inorder(node->right.get());
    }

    Node* min_node(Node* node) const
    {
        while(node && node->left) { node = node->left.get();}
        return node;
    }
    Node* max_node(Node* node) const
    {
        while(node && node->right) { node = node->right.get();}
        return node;
    }

    void transplant(Node* a, std::unique_ptr<Node> b)
    {
        if(a->parent == nullptr)
        { 
            root = std::move(b);
            if(root) { root->parent = nullptr;}
        }
        else if(a == a->parent->left.get()) 
        { 
            a->parent->left = std::move(b);
            if(a->parent->left) 
            { 
                a->parent->left->parent = a->parent;
            }
        }
        else 
        { 
            a->parent->right = std::move(b);
            if(a->parent->right)
            {
                a->parent->right->parent = a->parent;
            }
        }
    }

public:

    BinaryTree() = default;
    ~BinaryTree() = default;
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;
    BinaryTree(BinaryTree&&) noexcept = default;
    BinaryTree& operator =(BinaryTree&&) noexcept = default;

    void insert(int v)
    {
        auto z = std::make_unique<Node>(v);
        Node* y = nullptr;
        Node* x = root.get();
        while(x)
        {
            y = x;
            if(z->val < x->val) { x = x->left.get();}
            else x = x->right.get();
        }

        z->parent = y;
        if(y == nullptr) { root = std::move(z);}
        else if (z->val < y->val) { y->left = std::move(z);}
        else { y->right = std::move(z);}
    }
    Node* successor(Node* node) const
    {
        if(node->right) { return min_node(node->right.get());}
        Node* y = node->parent;
        while(y && y->right.get() == node)
        {
            node = y;
            y = y->parent;
        }
        return y;
    }

    Node* predecessor(Node* node) const
    {
        if(node->left) { return max_node(node->left.get());}
        Node* y = node->parent;
        while(y && y->left.get() == node)
        {
            node = y;
            y = y->parent;
        }
        return y;
    }

    void print_inorder() const
    {
        inorder(root.get());
        std::cout << "\n";
    }

    Node* get_root() const { return root.get(); }
};

int main()
{
    BinaryTree tree;

    tree.insert(15);
    tree.insert(10);
    tree.insert(20);
    tree.insert(8);
    tree.insert(12);
    tree.insert(17);
    tree.insert(25);

    std::cout << "Inorder traversal: ";
    tree.print_inorder();
    return 0;
}
