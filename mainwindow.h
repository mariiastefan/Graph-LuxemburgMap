#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include <QPushButton>
#include <QRadioButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *event);
    ~MainWindow();
private slots:

private:
    Ui::MainWindow *ui;
    Graph g;
    Node firstNode, secondNode,first,second;
    bool drawArc,drawNode;
    std::vector <int> vectDij;


};
#endif // MAINWINDOW_H
