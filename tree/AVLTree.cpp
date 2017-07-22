#include <iostream>
#include "Tools/ReadDataFromFile.h"

using namespace std;

enum ShowType
{
    pre,
    in,
    post
};

//T 要实现comprable接口
template <typename T>
class AVLTree
{
  public:
    AVLTree()
    {
        this->node = NULL;
    }
    AVLTree(T t)
    {
        this->node = new Node(t);
    }

    bool isExist(T t)
    {
        if (node == NULL)
            return false;
        Node *root = node;
        while (root != NULL)
        {
            if (root->t == t)
                return true;
            else if (root->t > t)
                root = root->left;
        }
    }

    T findMax()
    {
        return maxNode(node);
    }

    T findMin()
    {
        return minNode(node);
    }

    void insert(T t)
    {
        insert(node, t);
    }

    void remove(T t)
    {
        remove(node, t);
    }

    void showTree(ShowType type)
    {
        switch (type)
        {
        case ShowType::pre:
            preOrder(node);
            cout << endl;
            break;
        case ShowType::in:
            inOrder(node);
            cout << endl;
            break;
        case ShowType::post:
            postOrder(node);
            cout << endl;
            break;
        default:
            break;
        }
    }

  private:
    class Node
    {
      public:
        Node()
        {
            height = 1;
            this->left = NULL;
            this->right = NULL;
        }
        Node(T t)
        {
            this->t = t;
            height = 1;
            this->left = NULL;
            this->right = NULL;
        }
        ~Node()
        {
        }
        T t;
        Node *left;
        Node *right;
        int height;
    };
    Node *node;
    Node *insert(Node *&pnode, T t)
    {
        if (pnode == NULL)
        {
            pnode = new Node(t);
            return pnode;
        }
        else if (pnode->t < t)
        { //往右子树插入
            insert(pnode->right, t);
            // if (height(pnode->right) - height(pnode->left) >= 2)
            // {
            //     pnode = RR(pnode);
            // }
            if (height(pnode->right) - height(pnode->left) >= 2)
            {
                if (height(pnode->right->right) >= height(pnode->right->left))
                    pnode = RR(pnode);
                else
                    pnode = RL(pnode);
            }
        }
        else if (pnode->t > t)
        { //往左子树插入
            insert(pnode->left, t);
            // if (height(pnode->right) - height(pnode->right) >= 2)
            // {
            //     pnode = LR(pnode);
            // }
            if (height(pnode->left) - height(pnode->right) >= 2)
            {
                // pnode = LL(pnode);
                if (height(pnode->left->left) >= height(pnode->left->right))
                    pnode = LL(pnode);
                else
                    pnode = LR(pnode);
            }
        }
        pnode->height = max(height(pnode->right), height(pnode->left)) + 1;
        return pnode;
    }
    Node *remove(Node *&pnode, T t)
    {
        if (pnode == NULL)
            return NULL;
        if (pnode->t == t)
        { //找到删除的节点
            if (pnode->left != NULL && pnode->right != NULL)
            {
                if (height(pnode->left) > height(pnode->right))
                {
                    Node *lmax = maxNode(pnode->left);
                    pnode->t = lmax->t;
                    pnode->left = remove(pnode->left, lmax->t);
                }
                else
                {
                    Node *rmin = minNode(pnode->right);
                    pnode->t = rmin->t;
                    pnode->right = remove(pnode->right, rmin->t);
                }
            }
            else
            {
                Node *tmp = pnode;
                if (pnode->left != NULL)
                    pnode = pnode->left;
                else if (pnode->right != NULL)
                    pnode = pnode->right;
                else
                    pnode = NULL;
                delete tmp;
                return pnode;
            }
        }
        else if (pnode->t > t)
        { //删除的节点在左边
            pnode->left = remove(pnode->left, t);
            if (height(pnode->right) - height(pnode->left) >= 2)
            {
                if (height(node->right->right) < height(node->right->left))
                {
                    pnode = RL(pnode);
                }
                else
                {
                    pnode = RR(pnode);
                }
            }
        }
        else
        { //删除的节点在右点
            pnode->right = remove(pnode->right, t);
            if (height(pnode->left) - height(pnode->right) >= 2)
            {
                if (height(node->left->right) > height(node->left->left))
                {
                    pnode = LR(pnode);
                }
                else
                {
                    pnode = LL(pnode);
                }
            }
        }
        return pnode;
    }
    Node *maxNode(Node *pnode)
    {
        while (pnode->right != NULL)
            pnode = pnode->right;
        return pnode;
    }
    Node *minNode(Node *pnode)
    {
        while (pnode->left != NULL)
            pnode = pnode->left;
        return pnode;
    }
    int height(Node *node)
    {
        if (node == NULL)
            return 0;
        return node->height;
    }
    //左-左
    Node *LL(Node *pnode)
    {
        if (pnode == NULL)
            return NULL;
        Node *plchild = pnode->left;
        pnode->left = plchild->right;
        plchild->right = pnode;
        pnode->height = max(height(pnode->right), height(pnode->left)) + 1;
        plchild->height = max(height(plchild->left), height(plchild->right)) + 1;
        return plchild;
    }
    //左-右
    Node *LR(Node *pnode)
    {
        if (pnode == NULL)
            return NULL;
        pnode->left = RR(pnode->left);
        return LL(pnode);
    }
    //右-左
    Node *RL(Node *pnode)
    {
        if (pnode == NULL)
            return NULL;
        pnode->right = LL(pnode->right);
        return RR(pnode);
    }
    //右-右
    Node *RR(Node *pnode)
    {
        if (pnode == NULL)
            return NULL;
        Node *prchild = pnode->right;
        pnode->right = prchild->left;
        prchild->left = pnode;
        pnode->height = max(height(pnode->right), height(pnode->left)) + 1;
        prchild->height = max(height(prchild->left), height(prchild->right)) + 1;
        return prchild;
    }

    void preOrder(Node *pnode)
    {
        if (pnode == NULL)
            return;
        cout << pnode->t << " ";
        preOrder(pnode->left);
        preOrder(pnode->right);
    }

    void inOrder(Node *pnode)
    {
        if (pnode == NULL)
            return;
        inOrder(pnode->left);
        cout << pnode->t << " ";
        inOrder(pnode->right);
    }

    void postOrder(Node *pnode)
    {
        if (pnode == NULL)
            return;
        postOrder(pnode->left);
        postOrder(pnode->right);
        cout << pnode->t << " ";
    }

  public:
#ifdef _DEBUG
    Node *getNode()
    {
        return node;
    }
#endif
};

int main(int argc, char **argv)
{
    int n;
    cin >> n;
    AVLTree<int> tree;
#ifndef _DEBUG
    int k;
    for (int i = 0; i < n; i++)
    {
        cin >> k;
        tree.insert(k);
    }
    tree.showTree(ShowType::pre);
    for (int i = 0; i < n / 2; i++)
    {
        cin >> k;
        tree.remove(k);
    }
    tree.showTree(ShowType::in);
#else
    ReadFile readFile("../data/avlInput.input");
    auto input = readFile.readData()[0];
    for (int i = 0; i < input.size(); i++)
    {
        tree.insert(input[i]);
    }
    tree.showTree(ShowType::pre);
    for (int i = 0; i < input.size() / 2; i++)
    {
        tree.remove(input[i]);
    }
    tree.showTree(ShowType::in);
#endif
    return 0;
}