#ifndef CLUSTERING_HPP
#define CLUSTERING_HPP

#include <vector>
#include <algorithm>

#include "Tree.hpp"

namespace
{
std::unordered_set<size_t> set_of_indexes(size_t size)
{
    std::unordered_set<size_t> temp;
    for (size_t i = 0; i != size; ++i)
    {
        temp.insert(i);
    }
    return temp;
}

template <typename T, typename DistanceNorm, typename DistancePolicy>
void divide_node(TreeNode<size_t>* node, const DistanceNorm& d, const DistancePolicy& d_policy)
{
    if (node->data().size() < 2)
    {
        return;
    }

    auto iter = std::max_element(
                    node->data().begin(),
                    node->data().end(),
                    [node, &d, &d_policy](size_t left, size_t right) -> bool
    {
        return d_policy(d, left, node->data())
                < d_policy(d, right, node->data());
    });

    std::unordered_set<size_t> new_cluster;
    std::unordered_set<size_t> old_cluster(node->data());

    size_t index_to_move = *iter;
    double diff = d_policy(d, index_to_move, node->data());

    while (diff >= 0 && old_cluster.size() > 1)
    {
        old_cluster.erase(index_to_move);
        new_cluster.insert(index_to_move);

        auto iter = std::max_element(
                        old_cluster.begin(),
                        old_cluster.end(),
                        [&old_cluster, &new_cluster, &d, &d_policy](size_t left, size_t right) -> bool
        {
            return (d_policy(d, left, old_cluster) - d_policy(d, left, new_cluster))
                    < (d_policy(d, right, old_cluster) - d_policy(d, right, new_cluster));
        });
        index_to_move = *iter;
        diff = d_policy(d, index_to_move, old_cluster) - d_policy(d, index_to_move, new_cluster);
    }

    node->set_left(std::make_unique<TreeNode<size_t>>(std::move(new_cluster)));
    node->set_right(std::make_unique<TreeNode<size_t>>(std::move(old_cluster)));

    divide_node<T, DistanceNorm, DistancePolicy>(node->left(), d, d_policy);
    divide_node<T, DistanceNorm, DistancePolicy>(node->right(), d, d_policy);
}
}

template <typename T, typename DistanceNorm, typename DistancePolicy>
Tree<size_t> clustering(const std::vector<T>& data)
{
    DistanceNorm d(data);
    DistancePolicy d_policy(d, data);

    Tree<size_t> tree(set_of_indexes(data.size()));

    divide_node<T, DistanceNorm, DistancePolicy>(tree.root(), d, d_policy);

    return tree;
}

#include "DistanceNorm.hpp"
#include "DistancePolicy.hpp"

template <typename T>
constexpr Tree<size_t> (*euclidean_middlelink_clustering)(const std::vector<T>& data) =
        &clustering<T, EuclideanDistanceNorm<T>, MiddleLinkDistancePolicy<T, EuclideanDistanceNorm<T>>>;

#endif
