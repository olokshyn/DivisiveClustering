#ifndef TREENOTETEST_HPP
#define TREENOTETEST_HPP

#include <QObject>

class TreeNodeTest : public QObject
{
    Q_OBJECT

private slots:
    void OneTreeNode();
    void TwoTreeNodes();
    void ThreeTreeNodes();
};

#endif // TREENOTETEST_HPP
