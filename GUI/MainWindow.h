#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class DendogramView;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void draw_tree();

private:
    DendogramView* m_dendogram_view;
};

#endif // MAINWINDOW_H
