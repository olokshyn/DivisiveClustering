#ifndef DISTANCENORM_HPP
#define DISTANCENORM_HPP

#include <cassert>
#include <cmath>

#include <vector>

template <typename T, size_t p>
class MinkowskiDistanceNorm
{
public:
    explicit MinkowskiDistanceNorm(const std::vector<T>& data)
        : m_data(data)
    {}

    double operator()(const T& a, const T& b) const
    {
        double result = 0.0;
        for (size_t i = 0; i != a.size(); ++i)
        {
            result += pow(fabs(a[i] - b[i]),
                          static_cast<double>(p));
        }

        return pow(result, 1 / static_cast<double>(p));
    }

    double operator()(size_t index_i, size_t index_j) const
    {
        assert(index_i < m_data.size());
        assert(index_j < m_data.size());
        assert(m_data[index_i].size() == m_data[index_j].size());

        return operator()(m_data[index_i], m_data[index_j]);
    }

    const std::vector<T>& data() const
    {
        return m_data;
    }

private:
    const std::vector<T>& m_data;
};

template <typename T>
using ManhattanDistanceNorm = MinkowskiDistanceNorm<T, 1>;

template <typename T>
using EuclideanDistanceNorm = MinkowskiDistanceNorm<T, 2>;

template <typename T>
class SquaredEuclideanDistanceNorm
{
public:
    explicit SquaredEuclideanDistanceNorm(const std::vector<T>& data)
        : m_norm(data)
    {}

    double operator()(const T& a, const T& b)
    {
        return pow(m_norm(a, b), 2.0);
    }

    double operator()(size_t index_i, size_t index_j) const
    {
        return pow(m_norm(index_i, index_j), 2.0);
    }

    const std::vector<T>& data() const
    {
        return m_norm.data();
    }

private:
    MinkowskiDistanceNorm<T, 2> m_norm;
};

template <typename T, typename DistanceNorm>
class CachingDistanceNorm
{
public:
    explicit CachingDistanceNorm(const std::vector<T>& data)
        : m_norm(data),
          m_cache(data.size(),
                  std::vector<double>(data.size(), -1.0))
    {}

    double operator()(const T& a, const T& b) const
    {
        return m_norm(a, b);
    }

    double operator()(size_t index_i, size_t index_j) const
    {
        if (m_cache[index_i][index_j] < 0)
        {
            m_cache[index_i][index_j]
                    = m_cache[index_j][index_i]
                      = m_norm(index_i, index_j);
        }
        return m_cache[index_i][index_j];
    }

    const std::vector<T>& data() const
    {
        return m_norm.data();
    }

private:
    DistanceNorm m_norm;
    mutable std::vector<std::vector<double>> m_cache;
};

template <typename T, size_t p>
using CachingMinkowskiDistanceNorm = CachingDistanceNorm<T, MinkowskiDistanceNorm<T, p>>;

template <typename T>
using CachingManhattanDistanceNorm = CachingDistanceNorm<T, ManhattanDistanceNorm<T>>;

template <typename T>
using CachingEuclideanDistanceNorm = CachingDistanceNorm<T, EuclideanDistanceNorm<T>>;

template <typename T>
using CachingSquaredEuclideanDistanceNorm = CachingDistanceNorm<T, SquaredEuclideanDistanceNorm<T>>;

#endif
