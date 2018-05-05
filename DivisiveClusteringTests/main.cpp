#include <QTest>

#include "TreeNodeTest.hpp"
#include "TreeTest.hpp"
#include "ClusteringTest.hpp"

int main(int argc, char* argv[])
{
    int status = 0;
    status |= QTest::qExec(new TreeNodeTest, argc, argv);
    status |= QTest::qExec(new TreeTest, argc, argv);
    status |= QTest::qExec(new ClusteringTest, argc, argv);

    return status;
}
