#ifndef TREETEST_HPP
#define TREETEST_HPP

#include <QObject>

class TreeTest : public QObject
{
    Q_OBJECT

private slots:
    void OneNode();
    void TwoNodes();
    void ThreeNodes();
};


#endif // TREETEST_HPP
