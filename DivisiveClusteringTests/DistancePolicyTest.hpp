#ifndef DISTANCEPOLICYTEST_HPP
#define DISTANCEPOLICYTEST_HPP

#include <QtTest>

class DistancePolicyTest : public QObject
{
    Q_OBJECT

private:
    template <typename T, typename DistanceNorm, typename DistancePolicy>
    void test()
    {
        QFETCH(std::vector<std::vector<double>>, data);
        QFETCH(std::vector<size_t>, indices);
        QFETCH(double, dist);

        DistanceNorm d(data);
        DistancePolicy d_policy(d, data);
    }

private slots:

};

#endif // DISTANCEPOLICYTEST_HPP
