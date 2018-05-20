#ifndef TREEUTILS_HPP
#define TREEUTILS_HPP

#include <vector>

#include "Tree.hpp"

namespace TreeUtils
{

static std::unordered_set<size_t> convert_to_indices(const std::vector<std::vector<double>>& data)
{
    std::unordered_set<size_t> result;
    result.reserve(data.size());
    for (size_t i = 0; i != data.size(); ++i)
    {
        result.insert(i);
    }
    return result;
}

template <typename ...Args>
inline std::unique_ptr<TreeNode<size_t>> indices_to_TreeNode(Args ...args)
{
    return std::make_unique<TreeNode<size_t>>(std::unordered_set<size_t>{args...});
}

namespace __
{

template <typename T>
void get_levels_width(const TreeNode<T>* root,
                      size_t level, std::vector<size_t>& levels_width)
{
    Q_ASSERT(level < levels_width.size());
    ++levels_width[level];
    if (root->left())
    {
        get_levels_width<T>(root->left(), level + 1, levels_width);
    }
    if (root->right())
    {
        get_levels_width<T>(root->right(), level + 1, levels_width);
    }
}

}

template <typename T>
size_t get_levels_count(const TreeNode<T>* root)
{
    size_t left_levels_count = root->left() ? get_levels_count<T>(root->left()) : 0;
    size_t right_levels_count = root->right() ? get_levels_count<T>(root->right()) : 0;
    return 1 + std::max(left_levels_count, right_levels_count);
}

template <typename T>
inline std::vector<size_t> get_levels_width(const Tree<T>& tree)
{
    size_t levels_count = get_levels_count<T>(tree.root());
    std::vector<size_t> levels_width(levels_count);
    __::get_levels_width<T>(tree.root(), 0, levels_width);
    return levels_width;
}

}

#endif // TREEUTILS_HPP
