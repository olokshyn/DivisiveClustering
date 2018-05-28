#include "MainWindow.h"

#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>

#include "DendogramView.h"
#include "Tree.hpp"
#include "Clustering.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_dendogram_view(new DendogramView(this))
{
    auto layout = new QGridLayout(this);
    auto button = new QPushButton(this);
    button->setText("Draw dendogram");
    connect(button, SIGNAL(clicked(bool)), SLOT(draw_tree()));
    layout->addWidget(button, 1, 1);

    auto area = new QScrollArea(this);
    area->setWidget(m_dendogram_view);
    layout->addWidget(area, 2, 1, 1, 4);

    showMaximized();
}

template <typename T>
using CachingMinkowskiDistanceNorm4 = CachingMinkowskiDistanceNorm<T, 4>;

void MainWindow::draw_tree()
{
    std::vector<std::vector<double>> data = {
        {44.5, 84.98, 20.4, 3.2,  14.4},  // 0
        {32.5, 30.58, 71.4, 8.5,  11.6},  // 1
        {33.9, 38.42, 78.7, 9.2,  56.1},  // 2
        {38.8, 60.34, 12.1, 3.3,  16.4},  // 3
        {34.4, 60.22, 10.9, 3.2,  13.5},  // 4
        {43.6, 60.79, 20.4, 5.4,  22.4},  // 5
        {41.0, 29.82, 79.7, 8.3,  65.5},  // 6
//        {36.4, 70.57, 17.3, 5.4,  27.8},
        {17.9, 34.51, 69.7, 7.1,  62.3},  // 7
        {32.1, 64.73, 24.5, 6.0,  39.8},  // 8
        {38.1, 36.63, 76.2, 8.6,  56.9},  // 9
        {41.5, 32.84, 44.4, 5.7,  37.4},  // 10
        {55.0, 62.64, 11.3, 3.5,  18.6},  // 11
        {36.7, 34.07, 79.2, 6.7,  54.4},  // 12
        {15.8, 39.27, 57.0, 6.7,  64.2},  // 13
        {40.9, 28.46, 54.8, 7.3,  22.6},  // 14
        {49.4, 30.27, 72.1, 8.5,  46.0},  // 15
        {38.1, 69.04, 13.4, 3.3,  7.9},   // 16
        {27.6, 25.42, 79.9, 10.2, 25.4},  // 17
        {33.2, 53.13, 11.2, 3.4,  17}     // 18
    };
    m_dendogram_view->draw_tree(
                CLUSTERING(std::vector<double>,
                           CachingEuclideanDistanceNorm,
                           MiddleLinkDistancePolicy)(data));
}
