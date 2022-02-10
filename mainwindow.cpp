#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include "graph.h"
#include "arc.h"
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QFile>
#include <QWidget>
#include <QRadioButton>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>
#include <QtMath>
#include <stddef.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    drawArc = false;
    drawNode=false;
    ui->setupUi(this);
    g.readXML();
}


void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        {
            QPointF p = e->localPos();
            std::vector<Node> noduri = g.GetNoduri();
            Node foundNode;
            for (auto& n : noduri)
            {
                if (fabs(n.getPoint().x() - p.x()) < 20 && fabs(n.getPoint().y() - p.y()) < 20)
                {
                    foundNode = n;
                    break;
                }
            }
            if (foundNode.getNumber() == -1)
                return;
            if (firstNode.getNumber() == -1)
            {
                firstNode = foundNode;
            }
            else
            {
                secondNode = foundNode;
                first=firstNode;
                second=secondNode;
                vectDij=g.DIJKSTRA(first,second);
                firstNode = Node();
                secondNode = Node();
                drawNode = true;
                update();
            }
        }

}
void MainWindow::paintEvent(QPaintEvent *event)
{
        QPainter p(this);
        if (g.getNumberofNodes())
        {

            std::vector<Arc> arce = g.GetArce();
            for(auto& arc: arce)
            {
                p.drawLine(arc.getFirstPoint().getPoint(), arc.getSecondPoint().getPoint());
            }
        }
        if(drawNode==true)
        {
            qDebug()<<"sunt aici";
            p.setBrush(Qt::darkCyan);
            p.setPen(Qt::cyan);
            QRect r(first.getPoint().x()-10,first.getPoint().y()-10, 20,20);
            p.drawEllipse(r);
            p.setBrush(Qt::darkMagenta);
            p.setPen(Qt::magenta);
            QRect t(second.getPoint().x()-10,second.getPoint().y()-10, 20,20);
            p.drawEllipse(t);
            int index1=second.getNumber();
            p.setPen(Qt::red);
            while(index1!=first.getNumber())
            {
                std::vector<Arc> arce = g.GetArce();
                for(auto& index2:arce)
                {
                    if(index2.getFirstPoint().getNumber()==vectDij[index1] && index2.getSecondPoint().getNumber()==index1)
                        p.drawLine(index2.getFirstPoint().getPoint(), index2.getSecondPoint().getPoint());
                    if(index2.getFirstPoint().getNumber()==index1 && index2.getSecondPoint().getNumber()==vectDij[index1])
                        p.drawLine(index2.getFirstPoint().getPoint(), index2.getSecondPoint().getPoint());
                }

                index1=vectDij[index1];
            }
        }

}


MainWindow::~MainWindow()
{

    delete ui;
}














