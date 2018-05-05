#include "TreeTest.hpp"

#include <QtTest>

#include "Staff.hpp"
#include "Tree.hpp"

void TreeTest::OneNode()
{
    Tree<data_t> tree(generate_data1());

    QVERIFY(tree.root() != nullptr);
    QCOMPARE(generate_data1(), tree.root()->data());
    QVERIFY(tree.root()->left() == nullptr);
    QVERIFY(tree.root()->right() == nullptr);
}

void TreeTest::TwoNodes()
{
    Tree<data_t> tree(generate_data1());
    tree.root()->set_left(std::make_unique<TreeNode<data_t>>(generate_data2()));

    QVERIFY(tree.root() != nullptr);
    QCOMPARE(generate_data1(), tree.root()->data());
    QVERIFY(tree.root()->left() != nullptr);
    QVERIFY(tree.root()->right() == nullptr);
    QCOMPARE(generate_data2(), tree.root()->left()->data());
    QVERIFY(tree.root()->left()->left() == nullptr);
    QVERIFY(tree.root()->left()->right() == nullptr);
}

void TreeTest::ThreeNodes()
{
    Tree<data_t> tree(generate_data1());
    tree.root()->set_left(std::make_unique<TreeNode<data_t>>(generate_data2()));
    tree.root()->set_right(std::make_unique<TreeNode<data_t>>(generate_data3()));

    QVERIFY(tree.root() != nullptr);
    QCOMPARE(generate_data1(), tree.root()->data());
    QVERIFY(tree.root()->left() != nullptr);
    QVERIFY(tree.root()->right() != nullptr);
    QCOMPARE(generate_data2(), tree.root()->left()->data());
    QCOMPARE(generate_data3(), tree.root()->right()->data());
    QVERIFY(tree.root()->left()->left() == nullptr);
    QVERIFY(tree.root()->left()->right() == nullptr);
    QVERIFY(tree.root()->right()->left() == nullptr);
    QVERIFY(tree.root()->right()->right() == nullptr);
}
