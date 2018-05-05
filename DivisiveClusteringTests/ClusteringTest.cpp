#include "ClusteringTest.hpp"

#include <vector>

#include <QtTest>

void ClusteringTest::ClusteringOnePoint()
{
    std::vector<std::vector<double>> data;
    data.push_back({ 1.0, 1.0, 1.0 });

    auto tree = euclidean_middlelink_clustering<std::vector<double>>(data);
    QCOMPARE(1ul, tree.root()->data().size());
    QCOMPARE(0ul, *tree.root()->data().begin());
    QVERIFY(tree.root()->left() == nullptr);
    QVERIFY(tree.root()->right() == nullptr);
}
