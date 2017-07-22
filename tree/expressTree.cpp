#include <iostream>
#include "structdata.h"
#include <string>
#include <vector>
#include <stack>

using namespace std;

TreeNode<string> createExpressTree(vector<string> express)
{
    stack<TreeNode<string>> _tmp;
    for (string e : express)
    {

        if (e == ("+") || e == ("-") || e == ("*") || e == ("/"))
        {
            if (_tmp.size() < 2)
                throw 0;
            TreeNode<string> right = _tmp.top();
            _tmp.pop();
            TreeNode<string> left = _tmp.top();
            _tmp.pop();
            TreeNode<string> node;
            node.t = e;
            node.left = &left;
            node.right = &right;
            _tmp.push(node);
        }
        else
        {
            for (char c : e)
                if (c - '0' >= 0 && c - '0' <= 9)
                    continue;
                else
                    throw 1;
            TreeNode<string> node;
            node.t = e;
            _tmp.push(node);
        }
    }
    if (_tmp.size() != 1)
        throw 1;
    else
        return _tmp.top();
}

void preShow(TreeNode<string> *tree)
{
    if (tree == NULL)
        return;
    if (tree->left != NULL)
        preShow(tree->left);
    cout << tree->t.c_str() << " ";
    if (tree->right != NULL)
        preShow(tree->right);
}

int main()
{
    vector<string> c = vector<string>({"1", "2", "+", "3", "4", "5", "+", "*", "*"});
    TreeNode<string> tree = createExpressTree(c);
    preShow(&tree);
    return 0;
}