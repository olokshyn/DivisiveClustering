#include "MainWindow.h"

#include <QGridLayout>
#include <QPushButton>

#include "DendogramView.h"
#include "Tree.hpp"
#include "TreeUtils.hpp"

using namespace TreeUtils;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_dendogram_view(new DendogramView(this))
{
    setGeometry(0, 0, 800, 600);

    auto layout = new QGridLayout(this);
    auto button = new QPushButton(this);
    button->setText("Draw dendogram");
    connect(button, SIGNAL(clicked(bool)), SLOT(draw_tree()));
    layout->addWidget(button, 1, 1);

    layout->addWidget(m_dendogram_view, 2, 1, 1, 4);
}

void MainWindow::draw_tree()
{
    std::shared_ptr<Tree<size_t>> tree(
                new Tree<size_t>(
                    convert_to_indices({
                                           {1.0, 1.0, 1.0}, // 0
                                           {3.0, 3.0, 3.0}, // 1
                                           {8.0, 8.0, 8.0}, // 2
                                           {5.0, 5.0, 5.0}, // 3
                                           {9.0, 9.0, 9.0}, // 4
                                           {7.0, 7.0, 7.0}, // 5
                                       })));
    tree->root()->set_left(indices_to_TreeNode(2ul, 3ul, 4ul, 5ul));
    tree->root()->set_right(indices_to_TreeNode(0ul, 1ul));

    tree->root()->left()->set_left(indices_to_TreeNode(2ul, 4ul, 5ul));
    tree->root()->left()->set_right(indices_to_TreeNode(3ul));

    tree->root()->right()->set_left(indices_to_TreeNode(0ul));
    tree->root()->right()->set_right(indices_to_TreeNode(1ul));

    tree->root()->left()->left()->set_left(indices_to_TreeNode(2ul, 5ul));
    tree->root()->left()->left()->set_right(indices_to_TreeNode(4ul));

    tree->root()->left()->left()->left()->set_left(indices_to_TreeNode(2ul));
    tree->root()->left()->left()->left()->set_right(indices_to_TreeNode(5ul));

    m_dendogram_view->draw_tree(tree);
}
