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
#pragma once
    TreeNode<T>* root()
    {
        return m_root.get();
    }

private:
    std::unique_ptr<TreeNode<T>> m_root;
};

#endif
