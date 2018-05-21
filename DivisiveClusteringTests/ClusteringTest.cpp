#include "ClusteringTest.hpp"

#include <vector>
#include <memory>

#include <QtTest>
#include <QMetaType>

#include "Tree.hpp"
#include "TreeUtils.hpp"

Q_DECLARE_METATYPE(std::shared_ptr<Tree<size_t>>)

using namespace TreeUtils;

void ClusteringTest::Clustering()
{
    QFETCH(std::vector<std::vector<double>>, data);
    QFETCH(std::shared_ptr<Tree<size_t>>, expected_tree);

    auto tree = euclidean_middlelink_clustering<std::vector<double>>(data);
    QCOMPARE(*expected_tree, tree);
}

void ClusteringTest::Clustering_data()
{
    QTest::addColumn<std::vector<std::vector<double>>>("data");
    QTest::addColumn<std::shared_ptr<Tree<size_t>>>("expected_tree");

    std::vector<std::vector<double>> data;
    std::shared_ptr<Tree<size_t>> tree;

    data.assign({
                    {1.0, 1.0, 1.0}
                });
    tree.reset(new Tree<size_t>(convert_to_indices(data)));
    QTest::newRow("OnePoint") << data << tree;

    data.assign({
                    {1.0, 1.0, 1.0},
                    {2.0, 2.0, 2.0}
                });
    tree.reset(new Tree<size_t>(convert_to_indices(data)));
    tree->root()->set_left(indices_to_TreeNode(0ul));
    tree->root()->set_right(indices_to_TreeNode(1ul));
    QTest::newRow("TwoPoints") << data << tree;

    data.assign({
                    {1.0, 1.0, 1.0},
                    {3.0, 3.0, 3.0},
                    {8.0, 8.0, 8.0}
                });
    tree.reset(new Tree<size_t>(convert_to_indices(data)));
    tree->root()->set_left(indices_to_TreeNode(0ul, 1ul));
    tree->root()->set_right(indices_to_TreeNode(2ul));
    tree->root()->left()->set_left(indices_to_TreeNode(1ul));
    tree->root()->left()->set_right(indices_to_TreeNode(0ul));
    QTest::newRow("ThreePoints") << data << tree;

    data.assign({
                    {1.0, 1.0, 1.0}, // 0
                    {3.0, 3.0, 3.0}, // 1
                    {8.0, 8.0, 8.0}, // 2
                    {5.0, 5.0, 5.0}, // 3
                    {9.0, 9.0, 9.0}, // 4
                    {7.0, 7.0, 7.0}, // 5
                });
    tree.reset(new Tree<size_t>(convert_to_indices(data)));

    tree->root()->set_left(indices_to_TreeNode(2ul, 3ul, 4ul, 5ul));
    tree->root()->set_right(indices_to_TreeNode(0ul, 1ul));

    tree->root()->left()->set_left(indices_to_TreeNode(2ul, 4ul, 5ul));
    tree->root()->left()->set_right(indices_to_TreeNode(3ul));

    tree->root()->right()->set_left(indices_to_TreeNode(0ul));
    tree->root()->right()->set_right(indices_to_TreeNode(1ul));

    tree->root()->left()->left()->set_left(indices_to_TreeNode(2ul, 4ul));
    tree->root()->left()->left()->set_right(indices_to_TreeNode(5ul));

    tree->root()->left()->left()->left()->set_left(indices_to_TreeNode(2ul));
    tree->root()->left()->left()->left()->set_right(indices_to_TreeNode(4ul));

    QTest::newRow("SixPoints") << data << tree;
}
