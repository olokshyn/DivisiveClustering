#ifndef DISTANCENORM_HPP
#define DISTANCENORM_HPP

#include <cassert>
#include <cmath>

#include <vector>

template <typename T>
class EuclideanDistanceNorm
{
public:
    explicit EuclideanDistanceNorm(const std::vector<T>& data)
        : m_data(data)
    {}

    double operator()(size_t index_i, size_t index_j) const
    {
        assert(index_i < m_data.size());
        assert(index_j < m_data.size());
        assert(m_data[index_i].size() == m_data[index_j].size());

        double result = 0.0;
        for (size_t i = 0; i != m_data[index_i].size(); ++i)
        {
            result += pow(m_data[index_i][i] - m_data[index_j][i], 2.0);
        }

        return sqrt(result);
    }

    const std::vector<T>& data() const
    {
        return m_data;
    }

public:
    const std::vector<T>& m_data;
};

#endif
