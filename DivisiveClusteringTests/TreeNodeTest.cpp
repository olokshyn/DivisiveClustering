#include "TreeNodeTest.hpp"

#include <QtTest>

#include "Staff.hpp"

void TreeNodeTest::OneTreeNode()
{
    TreeNode<data_t> tree_node(generate_data1());

    QCOMPARE(generate_data1(), tree_node.data());
    QVERIFY(nullptr == tree_node.left());
    QVERIFY(nullptr == tree_node.right());
}

void TreeNodeTest::TwoTreeNodes()
{
    TreeNode<data_t> tree_node(generate_data1());
    tree_node.set_left(std::make_unique<TreeNode<data_t>>(generate_data2()));

    QCOMPARE(generate_data1(), tree_node.data());
    QVERIFY(nullptr != tree_node.left());
    QVERIFY(nullptr == tree_node.right());
    QCOMPARE(generate_data2(), tree_node.left()->data());
}

void TreeNodeTest::ThreeTreeNodes()
{
    TreeNode<data_t> tree_node(generate_data1());
    tree_node.set_left(std::make_unique<TreeNode<data_t>>(generate_data2()));
    tree_node.set_right(std::make_unique<TreeNode<data_t>>(generate_data3()));

    QCOMPARE(generate_data1(), tree_node.data());
    QVERIFY(nullptr != tree_node.left());
    QVERIFY(nullptr != tree_node.right());
    QCOMPARE(generate_data2(), tree_node.left()->data());
    QCOMPARE(generate_data3(), tree_node.right()->data());
}
