#include "Staff.hpp"

std::unordered_set<data_t> generate_data1()
{
    std::unordered_set<data_t> data;
    data.insert({ 1.0, 1.0, 1.0 });
    data.insert({ 2.0, 2.0, 2.0 });
    data.insert({ 3.0, 3.0, 3.0 });
    data.insert({ 1.5, 1.5, 1.5 });
    data.insert({ 2.5, 2.5, 2.5 });
    data.insert({ 3.5, 3.5, 3.5 });

    return data;
}

std::unordered_set<data_t> generate_data2()
{
    std::unordered_set<data_t> data;
    data.insert({ 1.0, 1.0, 1.0 });
    data.insert({ 2.0, 2.0, 2.0 });

    return data;
}

std::unordered_set<data_t> generate_data3()
{
    std::unordered_set<data_t> data;
    data.insert({ 1.0, 1.0, 1.0 });
    data.insert({ 2.0, 2.0, 2.0 });
    data.insert({ 3.0, 3.0, 3.0 });

    return data;
}
