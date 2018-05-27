#include "DistanceNormTest.hpp"

#define DEFINE_COLUMNS \
    QTest::addColumn<std::vector<double>>("a"); \
    QTest::addColumn<std::vector<double>>("b"); \
    QTest::addColumn<double>("dist")

#define TEST_EQUAL_POINST(RESULT) QTest::newRow("EqualPoints") \
    << std::vector<double>({1.0, 1.0, 1.0}) \
    << std::vector<double>({1.0, 1.0, 1.0}) \
    << RESULT

#define TEST_ZERO_ONE_POINTS(RESULT) QTest::newRow("ZeroOnePoints") \
    << std::vector<double>({0.0, 0.0, 0.0}) \
    << std::vector<double>({1.0, 1.0, 1.0}) \
    << RESULT

#define TEST_CASUAL_POINTS(RESULT) QTest::newRow("CasualPoints") \
    << std::vector<double>({-13.0, 4.7, 2.07}) \
    << std::vector<double>({0.2, -3.2, 2.3}) \
    << RESULT

void DistanceNormTest::MinkowskiDistanceNormTest()
{
    test<MinkowskiDistanceNorm<std::vector<double>, 4>>();
}

void DistanceNormTest::MinkowskiDistanceNormTest_data()
{
    DEFINE_COLUMNS;

    TEST_EQUAL_POINST(0.0);
    TEST_ZERO_ONE_POINTS(1.3161);
    TEST_CASUAL_POINTS(13.6044);
}

void DistanceNormTest::ManhattanDistanceNormTest()
{
    test<ManhattanDistanceNorm<std::vector<double>>>();
}

void DistanceNormTest::ManhattanDistanceNormTest_data()
{
    DEFINE_COLUMNS;

    TEST_EQUAL_POINST(0.0);
    TEST_ZERO_ONE_POINTS(3.0);
    TEST_CASUAL_POINTS(-5.53);
}

void DistanceNormTest::EuclideanDistanceNormTest()
{
    test<EuclideanDistanceNorm<std::vector<double>>>();
}

void DistanceNormTest::EuclideanDistanceNormTest_data()
{
    DEFINE_COLUMNS;

    TEST_EQUAL_POINST(0.0);
    TEST_ZERO_ONE_POINTS(1.7321);
    TEST_CASUAL_POINTS(15.3852);
}

void DistanceNormTest::SquaredEuclideanDistanceNormTest()
{
    test<SquaredEuclideanDistanceNorm<std::vector<double>>>();
}

void DistanceNormTest::SquaredEuclideanDistanceNormTest_data()
{
    DEFINE_COLUMNS;

    TEST_EQUAL_POINST(0.0);
    TEST_ZERO_ONE_POINTS(3.0);
    TEST_CASUAL_POINTS(236.7029);
}

template <typename T>
class TestDistanceNorm
{
public:
    explicit TestDistanceNorm(const std::vector<T>& data)
        : m_norm(data),
          m_in_cache(data.size(),
                     std::vector<bool>(false, data.size()))
    {}

    double operator()(size_t index_i, size_t index_j) const
    {
        if (m_in_cache[index_i][index_j])
        {
            throw std::runtime_error("Value must be taken from the cache");
        }
        m_in_cache[index_i][index_j] = true;
        m_in_cache[index_j][index_i] = true;
        return m_norm(index_i, index_j);
    }

    const std::vector<T>& data() const
    {
        return m_norm.data();
    }

private:
    EuclideanDistanceNorm<T> m_norm;
    mutable std::vector<std::vector<bool>> m_in_cache;
};

template <typename T>
using CachingTestDistanceNorm = CachingDistanceNorm<T, TestDistanceNorm<T>>;

void DistanceNormTest::CachingDistanceNormTest()
{
    test<CachingTestDistanceNorm<std::vector<double>>>();
}

void DistanceNormTest::CachingDistanceNormTest_data()
{
    DEFINE_COLUMNS;

    TEST_EQUAL_POINST(0.0);
    TEST_ZERO_ONE_POINTS(1.7321);
    TEST_CASUAL_POINTS(15.3852);
}
