#ifndef DISTANCEPOLICY_HPP
#define DISTANCEPOLICY_HPP

#include <vector>
#include <unordered_set>

template <typename T, typename DistanceNorm>
class MiddleLinkDistancePolicy
{
public:
    explicit MiddleLinkDistancePolicy(const DistanceNorm& d, const std::vector<T>& data)
    {}

    double operator()(const DistanceNorm& d, size_t obj_index, const std::unordered_set<size_t>& cluster) const
    {
        return distances_sum(d, obj_index, cluster) / cluster.size();
    }

    double operator()(const DistanceNorm& d, std::unordered_set<size_t> cluster_a, std::unordered_set<size_t> cluster_b) const
    {
        double sum = 0.0;
        for (auto index : cluster_a)
        {
            sum += distances_sum(d, index, cluster_b);
        }
        return sum / cluster_a.size() / cluster_b.size();
    }

private:
    double distances_sum(const DistanceNorm& d, size_t obj_index, const std::unordered_set<size_t>& cluster) const
    {
        double sum = 0.0;
        for (auto index : cluster)
        {
            sum += d(obj_index, index);
        }
        return sum;
    }
};

#endif
