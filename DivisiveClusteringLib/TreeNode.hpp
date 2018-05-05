#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <memory>
#include <unordered_set>

template <typename T>
class TreeNode
{
public:
    explicit TreeNode(std::unordered_set<T> data)
        : m_data(std::move(data)),
          m_right(nullptr),
          m_left(nullptr)
    {}

    const std::unordered_set<T>& data() const
    {
        return m_data;
    }

    TreeNode* right()
    {
        return m_right.get();
    }
    TreeNode* left()
    {
        return m_left.get();
    }

    void set_right(std::unique_ptr<TreeNode> right)
    {
        m_right = std::move(right);
    }
    void set_left(std::unique_ptr<TreeNode> left)
    {
        m_left = std::move(left);
    }

private:
    std::unordered_set<T> m_data;
    std::unique_ptr<TreeNode> m_right;
    std::unique_ptr<TreeNode> m_left;
};

#endif