#include "arc.h"

Arc::Arc(Node n1, Node n2,int l)
{
    firstNode = n1;
    secondNode = n2;
    length = l;
}

Node Arc::getFirstPoint()
{
    return firstNode;
}
Node Arc::getSecondPoint()
{
    return secondNode;
}

int Arc::GetLength()
{
    return length;
}

