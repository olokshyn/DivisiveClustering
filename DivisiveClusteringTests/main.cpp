#include <QTest>

#include "TreeNodeTest.hpp"
#include "TreeTest.hpp"
#include "ClusteringTest.hpp"
#include "DistanceNormTest.hpp"

int main(int argc, char* argv[])
{
    int status = 0;
    status |= QTest::qExec(new TreeNodeTest, argc, argv);
    status |= QTest::qExec(new TreeTest, argc, argv);
    status |= QTest::qExec(new ClusteringTest, argc, argv);
    status |= QTest::qExec(new DistanceNormTest, argc, argv);

    return status;
}
