#ifndef DISTANCEPOLICY_HPP
#define DISTANCEPOLICY_HPP

#include <vector>
#include <unordered_set>

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
                      std::unordered_set<size_t> cluster_a,
                      std::unordered_set<size_t> cluster_b) const
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

#endif
