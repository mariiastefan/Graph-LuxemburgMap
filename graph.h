#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "arc.h"
#include <QtXml>
#include <QMatrix>

class Graph
{
    std::vector<Node> noduri;
    std::vector<Arc> arce;
    int **matriceAD;
    std::vector<std::vector<int>> matriceAdiacenta;
    std::vector<std::vector<int>> matriceLength;
    std::vector<std::vector<int>> listaAdiacenta;
public:
    void GenerareMatriceAdiacenta();
    void GenerareListaAdiacenta();
    void GenerareMatrice();
    std::vector<Arc> GetArce();
    std::vector<Node> GetNoduri();
    bool Add(Node n);
    void AddNod(Node n);
    void AddArc(Arc a);
    void DrawGraf(QPainter *p);
    Node GetLastNode();
    int getNumberofNodes();
    void readXML();
    void listElements(QDomElement root, QString tagname, QString attribute,QString attribute2, QString attribute3);
    void listElementsARC(QDomElement root, QString tagname, QString attribute1,QString attribute2, QString attribute3);
    std::vector<int> DIJKSTRA(Node begin, Node end);
};
#endif // GRAPH_H
