#ifndef CLUSTERINGTEST_HPP
#define CLUSTERINGTEST_HPP

#include <QObject>

#include "Staff.hpp"
#include "Clustering.hpp"

class ClusteringTest : public QObject
{
    Q_OBJECT

private slots:
    void Clustering();
    void Clustering_data();
};

#endif // CLUSTERINGTEST_HPP
