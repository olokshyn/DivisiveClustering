#ifndef DENDOGRAMVIEW_H
#define DENDOGRAMVIEW_H

#include <memory>
#include <vector>

#include <QWidget>
#include <QImage>
#include <QPixmap>

#include "Tree.hpp"

Q_DECLARE_METATYPE(std::shared_ptr<Tree<size_t>>)

class DendogramView : public QWidget
{
    Q_OBJECT
public:
    explicit DendogramView(QWidget *parent = nullptr);

signals:
    void tree_drawn();

public slots:
    void draw_tree(const std::shared_ptr<Tree<size_t>>& indices_tree);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void update();
    void draw_dendogram();
    void draw_node(QPainter& painter,
                   const TreeNode<size_t>* node,
                   size_t level,
                   const std::vector<size_t>& levels_width,
                   std::vector<size_t>& nodes_drawn,
                   int node_width, int node_height,
                   int parent_node_x = -1, int parent_node_y = -1);

private:
    std::shared_ptr<Tree<size_t>> m_indices_tree;
    const std::vector<std::vector<double>>* m_data;
    QImage m_canvas;
    QPixmap m_framebuffer;
    bool m_framebuffer_is_invalid;
};

#endif // DENDOGRAMVIEW_H
