#ifndef DISTANCEPOLICY_HPP
#define DISTANCEPOLICY_HPP

#include <cassert>

#include <vector>
#include <unordered_set>
#include <algorithm>

template <typename T, typename DistanceNorm>
class MiddleLinkDistancePolicy
{
public:
    explicit MiddleLinkDistancePolicy(const DistanceNorm& d,
                                      const std::vector<T>& data)
    {}

    double operator()(const DistanceNorm& d,
                      size_t obj_index,
                      const std::unordered_set<size_t>& cluster) const
    {
        size_t distances_in_sum = 0;
        double sum = distances_sum(d, obj_index, cluster, distances_in_sum);
        return sum / distances_in_sum;
    }

    double operator()(const DistanceNorm& d,
                      const std::unordered_set<size_t>& cluster_a,
                      const std::unordered_set<size_t>& cluster_b) const
    {
        double sum = 0.0;
        size_t distances_in_sum = 0;
        for (auto index : cluster_a)
        {
            sum += distances_sum(d, index, cluster_b, distances_in_sum);
        }
        return sum / distances_in_sum;
    }

private:
    double distances_sum(const DistanceNorm& d,
                         size_t obj_index,
                         const std::unordered_set<size_t>& cluster,
                         size_t& distances_in_sum) const
    {
        double sum = 0.0;
        for (auto index : cluster)
        {
            if (obj_index != index)
            {
                sum += d(obj_index, index);
                ++distances_in_sum;
            }
        }
        return sum;
    }
};

template <typename T, typename DistanceNorm>
class DistantNeighborDistancePolicy
{
public:
    explicit DistantNeighborDistancePolicy(const DistanceNorm& d,
                                           const std::vector<T>& data)
    {}

    double operator()(const DistanceNorm& d,
                      size_t obj_index,
                      const std::unordered_set<size_t>& cluster) const
    {
        return d(obj_index, max_distance_index(d, obj_index, cluster));
    }

    double operator()(const DistanceNorm& d,
                      const std::unordered_set<size_t>& cluster_a,
                      const std::unordered_set<size_t>& cluster_b) const
    {
        auto iter = std::max_element(cluster_a.begin(), cluster_a.end(),
                                     [&d, &cluster_b](size_t left, size_t right) ->
                                     bool { return max_distance_index(d, left, cluster_b)
                    < max_distance_index(d, right, cluster_b); });
        assert(iter);
        return max_distance_index(d, *iter, cluster_b);
    }

private:
    size_t max_distance_index(const DistanceNorm& d,
                              size_t obj_index,
                              const std::unordered_set<size_t>& cluster) const
    {
        auto iter = std::max_element(cluster.begin(), cluster.end(),
                                     [&d, obj_index](size_t left, size_t right) ->
                                     bool { return d(obj_index, left) < d(obj_index, right); });
        assert(iter != cluster.end());
        return *iter;
    }
};

template <typename T, typename DistanceNorm>
class MedianDistancePolicy
{
public:
    explicit MedianDistancePolicy(const DistanceNorm& d,
                                  const std::vector<T>& data)
    {}

    double operator()(const DistanceNorm& d,
                      size_t obj_index,
                      const std::unordered_set<size_t>& cluster) const
    {
        return d(d.data()[obj_index], get_cluster_center(d.data(), cluster, obj_index));
    }

    double operator()(const DistanceNorm& d,
                      const std::unordered_set<size_t>& cluster_a,
                      const std::unordered_set<size_t>& cluster_b) const
    {
        return d(get_cluster_center(d.data(), cluster_a),
                 get_cluster_center(d.data(), cluster_b));
    }

private:
    std::vector<double> get_cluster_center(const std::vector<T>& data,
                                           const std::unordered_set<size_t>& cluster,
                                           size_t skip_obj_index = -1) const
    {
        assert(!data.empty());
        size_t components_count = data.front().size();
        std::vector<double> center(components_count, 0.0);

        size_t cluster_size = 0;
        for (size_t index : cluster)
        {
            if (skip_obj_index >= 0 && skip_obj_index == index)
            {
                continue;
            }
            for (size_t i = 0; i != components_count; ++i)
            {
                center[i] += data[index][i];
            }
            ++cluster_size;
        }
        if (cluster_size == 0)
        {
            return std::vector<double>(components_count, 0.0);
        }
        for (size_t i = 0; i != components_count; ++i)
        {
            center[i] /= cluster_size;
        }

        return center;
    }
};

#endif
