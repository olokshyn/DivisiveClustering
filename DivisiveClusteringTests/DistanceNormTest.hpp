#ifndef DISTANCENORMTEST_H
#define DISTANCENORMTEST_H

#include <QtTest>

#include "DistanceNorm.hpp"

class DistanceNormTest : public QObject
{
    Q_OBJECT

private:
    template <typename DistanceNorm>
    void test()
    {
        QFETCH(std::vector<double>, a);
        QFETCH(std::vector<double>, b);
        QFETCH(double, dist);

        std::vector<std::vector<double>> data({a, b});
        DistanceNorm d_norm(data);
        qFuzzyCompare(dist, d_norm(0 ,1));
        qFuzzyCompare(dist, d_norm(1, 0));
    }

private slots:
    void MinkowskiDistanceNormTest();
    void MinkowskiDistanceNormTest_data();

    void ManhattanDistanceNormTest();
    void ManhattanDistanceNormTest_data();

    void EuclideanDistanceNormTest();
    void EuclideanDistanceNormTest_data();

    void SquaredEuclideanDistanceNormTest();
    void SquaredEuclideanDistanceNormTest_data();

    void CachingDistanceNormTest();
    void CachingDistanceNormTest_data();
};

#endif // DISTANCENORMTEST_H
