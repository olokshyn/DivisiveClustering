#ifndef HASH_HPP
#define HASH_HPP

#include <functional>
#include <vector>

namespace std
{
template<>
class hash<std::vector<double>>
{
public:
    size_t operator()(const std::vector<double>& data) const
    {
        size_t result = 0;
        auto hash = std::hash<double>();
        for (size_t i = 0; i != data.size(); ++i)
        {
            result ^= hash(data[i]) << (i % sizeof(size_t));
        }
        return result;
    }
};
}

#endif
