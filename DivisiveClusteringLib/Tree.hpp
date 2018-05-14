#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include <unordered_set>

#include "TreeNode.hpp"

template <typename T>
class Tree
{
public:
    explicit Tree(std::unordered_set<T> data)
        : m_root(new TreeNode<T>(std::move(data)))
    {}

    TreeNode<T>* root()
    {
        return m_root.get();
    }
    const TreeNode<T>* root() const
    {
        return m_root.get();
    }

    friend bool operator==(const Tree& left, const Tree& right)
    {
        return !left.m_root && !right.m_root
                || (left.m_root && right.m_root
                    && *left.m_root == *right.m_root);
    }

private:
    std::unique_ptr<TreeNode<T>> m_root;
};

#endif
