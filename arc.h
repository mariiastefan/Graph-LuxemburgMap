#ifndef ARC_H
#define ARC_H

#include "node.h"
class Arc
{
    Node firstNode, secondNode;
    int length;
public:
    Arc(Node n1, Node n2,int l);
    Node getFirstPoint();
    Node getSecondPoint();
    int GetLength();
};
#endif // ARC_H
