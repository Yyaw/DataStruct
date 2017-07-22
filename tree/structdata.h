#ifndef _STRUCT_DATA
#define _STRUCT_DATA

template<typename T>
struct TreeNode
{
    T t;
    TreeNode<T> *left = nullptr;
    TreeNode<T> *right = nullptr;
};

#endif