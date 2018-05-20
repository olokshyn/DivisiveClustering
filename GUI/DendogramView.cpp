#include "DendogramView.h"

#include <algorithm>

#include <QPainter>

#include "Tree.hpp"
#include "TreeUtils.hpp"

using namespace TreeUtils;

const int g_offset = 30;
const int g_node_min_width = 50;
const int g_node_max_width = 150;
const int g_node_min_height = 50;
const int g_node_max_height = 150;

DendogramView::DendogramView(QWidget *parent) :
    QWidget(parent),
    m_indices_tree(nullptr),
    m_data(nullptr),
    m_framebuffer_is_invalid(false)
{
    update();
}

void DendogramView::draw_tree(const std::shared_ptr<Tree<size_t> >& indices_tree)
{
    m_indices_tree = indices_tree;
    update();
}

void DendogramView::paintEvent(QPaintEvent* event)
{
    if (m_framebuffer_is_invalid)
    {
        m_framebuffer = QPixmap::fromImage(std::move(m_canvas));
        m_framebuffer_is_invalid = false;
    }

    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.drawPixmap(0, 0, m_framebuffer);
}

void DendogramView::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    update();
}

void DendogramView::update()
{
    m_canvas = QImage(width(), height(), QImage::Format_RGBA8888);
    m_canvas.fill(Qt::white);
    if (m_indices_tree)
    {
        draw_dendogram();
    }
    m_framebuffer_is_invalid = true;
    repaint();
}

void DendogramView::draw_dendogram()
{
    std::vector<size_t> levels_width = get_levels_width(*m_indices_tree);
    Q_ASSERT(!levels_width.empty());
    size_t max_level_width = *std::max_element(levels_width.begin(),
                                               levels_width.end());
    int node_width = (width() - 2 * g_offset) / static_cast<int>(max_level_width);
    int node_height = (height() - 2 * g_offset) / static_cast<int>(levels_width.size());
    node_width = std::max(std::min(node_width, g_node_max_width), g_node_min_width);
    node_height = std::max(std::min(node_height, g_node_max_height), g_node_min_height);
    setMinimumWidth(static_cast<int>(max_level_width) * g_node_min_width + 2 * g_offset);
    setMinimumHeight(static_cast<int>(levels_width.size()) * g_node_min_height + 2 * g_offset);

    std::vector<size_t> nodes_drawn(levels_width.size());

    QPainter painter(&m_canvas);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

    draw_node(painter,
              m_indices_tree->root(),
              0,
              levels_width,
              nodes_drawn,
              node_width, node_height);
}

void DendogramView::draw_node(QPainter& painter,
                              const TreeNode<size_t>* node,
                              size_t level,
                              const std::vector<size_t>& levels_width,
                              std::vector<size_t>& nodes_drawn,
                              int node_width, int node_height,
                              int parent_node_x, int parent_node_y)
{
    int block_hor_offset = (width() - 2 * g_offset) / levels_width[level] - node_width;
    int block_vert_offset = (height() - 2 * g_offset) / levels_width.size() - node_height;

    int node_offset_x = g_offset + (block_hor_offset + node_width) * nodes_drawn[level] + block_hor_offset / 2;
    int node_offset_y = g_offset + (block_vert_offset + node_height) * level + block_vert_offset / 2;

    int node_x = node_offset_x + node_width / 2;
    int node_y = node_offset_y + node_height / 2;
    if (parent_node_x >= 0 && parent_node_y >= 0)
    {
    //        const int width_diff = parent_node_x <= node_x ? node_width / 2 : -node_width / 2;
    //        painter.drawLine(parent_node_x + width_diff, parent_node_y,
    //                         node_x, parent_node_y);
    //        painter.drawLine(node_x, parent_node_y,
    //                         node_x, node_y - node_height / 2);
        painter.drawLine(parent_node_x, parent_node_y + node_height / 2, node_x, node_y - node_height / 2);
    }

    painter.drawRect(
                node_offset_x,
                node_offset_y,
                node_width, node_height);
    ++nodes_drawn[level];

    QString title;
    for (size_t index : node->data())
    {
        title += QString::number(index) + " ";
    }
    painter.drawText(node_offset_x, node_offset_y,
                     node_width, node_height,
                     Qt::AlignCenter, title);

    if (node->left())
    {
        draw_node(painter,
                  node->left(),
                  level + 1,
                  levels_width,
                  nodes_drawn,
                  node_width, node_height,
                  node_x, node_y);
    }
    if (node->right())
    {
        draw_node(painter,
                  node->right(),
                  level + 1,
                  levels_width,
                  nodes_drawn,
                  node_width, node_height,
                  node_x, node_y);
    }
}
