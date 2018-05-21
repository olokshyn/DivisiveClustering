#include "DendogramView.h"

#include <cmath>

#include <algorithm>

#include <QPainter>

#include "Tree.hpp"
#include "TreeUtils.hpp"

using namespace TreeUtils;

const int g_offset = 10;
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
    size_t levels_count = get_levels_count(m_indices_tree->root());
    size_t max_level_width = get_tree_max_elements_count(m_indices_tree->root(), levels_count);
    int node_width = (width() - (static_cast<int>(max_level_width) + 1) * g_offset) / static_cast<int>(max_level_width);
    int node_height = (height() - (static_cast<int>(levels_count) + 1) * g_offset) / static_cast<int>(levels_count);
    node_width = std::max(std::min(node_width, g_node_max_width), g_node_min_width);
    node_height = std::max(std::min(node_height, g_node_max_height), g_node_min_height);
    setMinimumWidth(static_cast<int>(max_level_width) * g_node_min_width + (static_cast<int>(max_level_width) + 1) * g_offset);
    setMinimumHeight(static_cast<int>(levels_count) * g_node_min_height + (static_cast<int>(levels_count) + 1) * g_offset);

    std::vector<size_t> nodes_drawn(levels_count);

    QPainter painter(&m_canvas);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
    painter.setBrush(QBrush(QColor::fromRgb(255, 160, 50), Qt::SolidPattern));

    draw_node(painter,
              m_indices_tree->root(),
              0,
              levels_count,
              nodes_drawn,
              node_width, node_height);
}

int DendogramView::get_tree_max_elements_count(const TreeNode<size_t>* root, size_t levels_count)
{
    return pow(2, levels_count - 1);
}

int DendogramView::get_tree_width(const TreeNode<size_t>* root, size_t levels_count, int node_width)
{
    return get_tree_max_elements_count(root, levels_count) * node_width;
}

void DendogramView::draw_node(QPainter& painter,
                              const TreeNode<size_t>* node,
                              size_t level,
                              size_t levels_count,
                              std::vector<size_t>& nodes_drawn,
                              int node_width, int node_height,
                              int parent_node_x, int parent_node_y, bool left)
{
    int node_x = (width() - 2 * g_offset) / 2;
    int node_y = g_offset + node_height / 2;

    if (parent_node_x >= 0 && parent_node_y >= 0)
    {
        int tree_width = get_tree_width(node, levels_count - level, node_width);
        int offset = tree_width / 2 + g_offset;
        node_x = left ? parent_node_x - offset : parent_node_x + offset;
        node_y = parent_node_y + node_height + g_offset;
        const int width_diff = left ? -node_width / 2 : node_width / 2;
        painter.drawLine(parent_node_x + width_diff, parent_node_y,
                         node_x, parent_node_y);
        painter.drawLine(node_x, parent_node_y,
                         node_x, node_y - node_height / 2);
    }

    int node_offset_x = node_x - node_width / 2;
    int node_offset_y = node_y - node_height / 2;

    painter.drawRect(
                node_offset_x,
                node_offset_y,
                node_width, node_height);
    ++nodes_drawn[level];

    QString title = "{ ";
    for (size_t index : node->data())
    {
        title += QString::number(index) + ", ";
    }
    title += "}";
    painter.drawText(node_offset_x, node_offset_y,
                     node_width, node_height,
                     Qt::AlignCenter | Qt::TextWordWrap, title);

    if (node->left())
    {
        draw_node(painter,
                  node->left(),
                  level + 1,
                  levels_count,
                  nodes_drawn,
                  node_width, node_height,
                  node_x, node_y, true);
    }
    if (node->right())
    {
        draw_node(painter,
                  node->right(),
                  level + 1,
                  levels_count,
                  nodes_drawn,
                  node_width, node_height,
                  node_x, node_y, false);
    }
}
