#include "graph.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include <queue>
#include <vector>

std::vector<Arc> Graph::GetArce()
{
    return arce;
}

std::vector<Node> Graph::GetNoduri()
{
    return noduri;
}

void Graph::AddNod(Node n)
{
    n.setNumber(noduri.size());
    noduri.push_back(n);
}

void Graph::AddArc(Arc n)
{
    for(auto index:arce)
    {
        if(index.getFirstPoint().getNumber()==n.getFirstPoint().getNumber()&&index.getSecondPoint().getNumber()==n.getSecondPoint().getNumber())
        {
            return;
           }
    }
    arce.push_back(n);
}

Node Graph::GetLastNode()
{
    return noduri[noduri.size()-1];
}

int Graph::getNumberofNodes()
{
    return noduri.size();
}

void Graph::GenerareMatrice()
{
    std::cout<<getNumberofNodes()<<'\n';
    for(int ind1=0;ind1<getNumberofNodes();ind1++)
    {
        std::vector<int> vector;
        for(int ind2=0;ind2<getNumberofNodes();ind2++)
        {
            vector.push_back(-1);
        }
        matriceLength.push_back(vector);
    }
   std::vector<Arc> arc=GetArce();
        for(auto &index:arc)
            {
               matriceLength[index.getFirstPoint().getNumber()][index.getSecondPoint().getNumber()]=index.GetLength();
            }

//    for(int ind1=0;ind1<matriceLength.size();ind1++)
//    {
//        for(int ind2=0;ind2<matriceLength[ind1].size();ind2++)
//        {
//            std::cout<<matriceLength[ind1][ind2]<<" ";
//        }
//        std::cout<<'\n';
//    }

}

void Graph::readXML()
{
    QDomDocument document;
   QFile file("D:/AG/Harta_Luxemburg.xml");
  // QFile file("C:/Users/Maria/Downloads/Harta_Luxemburg.xml");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Failed to open file";
    }
    else
    {
        if(!document.setContent(&file))
        {
            {
                qDebug()<<"Failed to open file";
            }
        }
        file.close();
    }
    QDomElement root=document.firstChildElement();

    listElements(root,"node","id","longitude","latitude");
    listElementsARC(root,"arc","from","to","length");
    GenerareMatrice();
    qDebug()<<"FinishedTOTAL";

}

void Graph::listElements(QDomElement root, QString tagname, QString attribute,QString attribute2, QString attribute3)
{
    QDomNodeList items=root.elementsByTagName(tagname);
    qDebug()<< "Total items = "<<items.count();
    qDebug()<<"NODURI";
    int lonMIN=INT_MAX,lonMAX=INT_MIN,latMIN=INT_MAX,latMAX=INT_MIN;
    int lon,lat;
    int size=items.length();
    for(int index=0;index<size;index++)
    {
        QDomNode itemnode = items.at(index);

        if(itemnode.isElement())
        {
            QDomElement itemele = itemnode.toElement();
            lon= itemele.attribute(attribute2).toUInt();
            lat= itemele.attribute(attribute3).toUInt();
            if(lon>lonMAX)
                lonMAX=lon;
            if(lat>latMAX)
                latMAX=lat;
            if(lat<latMIN)
                latMIN=lat;
            if(lon<lonMIN)
                lonMIN=lon;
        }
    }
   int height=1800;
   int width=800;
   float x,y;
   float l1=lonMAX-lonMIN;
   float l2=latMAX-latMIN;

    for(int index = 0;index < size; index++)
    {
        QDomNode itemnode = items.at(index);

        if(itemnode.isElement())
        {
            QDomElement items = itemnode.toElement();
            lon= items.attribute(attribute2).toUInt();
            lat= items.attribute(attribute3).toUInt();

            float L1=lon-lonMIN;
            float L2=latMAX-lat;
            x=(height/l1)*L1;
            y=width/l2;
            y=y*L2;
            //qDebug()<<x<<" "<<y;
            QPoint point(x,y);
            AddNod(point);

        }
    }
qDebug()<<"FinishedNODURI";
}

void Graph::listElementsARC(QDomElement root, QString tagname, QString attribute1, QString attribute2, QString attribute3)
{
    qDebug()<<"ARCE";
    QDomNodeList items=root.elementsByTagName(tagname);
    int size=items.length();
    for(int index=0;index<size;index++)
    {
        QDomNode itemnode = items.at(index);

        if(itemnode.isElement())
        {
            QDomElement items = itemnode.toElement();
            int from= items.attribute(attribute1).toUInt();
            int to= items.attribute(attribute2).toUInt();
            int length=items.attribute(attribute3).toUInt();
            Arc arc(noduri[from],noduri[to],length);
            AddArc(arc);
        }
    }
    qDebug()<<"FinishedARCE";

}

std::vector<int> Graph::DIJKSTRA(Node begin, Node end)
{
    std::vector<Node> W= GetNoduri();
    std::vector<int> dist, parents;
    std::vector<bool> S;
    std::priority_queue<std::pair<int, int>> queue;

    for(auto &nod:W)
    {

        dist.push_back(-1);
        parents.push_back(0);
        S.push_back(false);
    }

    dist[begin.getNumber()]=0;
    parents[begin.getNumber()]=0;
    S[begin.getNumber()]=false;
    queue.push(std::make_pair(begin.getNumber(),0));
    int x;
    std::vector<Arc> arc=GetArce();
    while(!queue.empty())
    {
        x=queue.top().first;
        queue.pop();
        if(S[x])
            continue;
        if(x==end.getNumber())
            break;

        S[x]=true;

        for(auto &ind: arc)
        {
            if(ind.getFirstPoint().getNumber()==x)
            {
                if(dist[ind.getSecondPoint().getNumber()]>(dist[ind.getSecondPoint().getNumber()]+matriceLength[x][ind.getSecondPoint().getNumber()]))
                {
                    dist[ind.getSecondPoint().getNumber()]=dist[x]+matriceLength[x][ind.getSecondPoint().getNumber()];
                    parents[ind.getSecondPoint().getNumber()]=x;
                    queue.push(std::make_pair(ind.getSecondPoint().getNumber(),dist[ind.getSecondPoint().getNumber()]));
                }
            }
            if(ind.getSecondPoint().getNumber()==x)
            {
                if(dist[ind.getFirstPoint().getNumber()]>(dist[ind.getFirstPoint().getNumber()]+matriceLength[x][ind.getFirstPoint().getNumber()]))
                {
                    dist[ind.getFirstPoint().getNumber()]=dist[x]+matriceLength[x][ind.getFirstPoint().getNumber()];
                    parents[ind.getFirstPoint().getNumber()]=x;
                    queue.push(std::make_pair(ind.getFirstPoint().getNumber(),dist[ind.getFirstPoint().getNumber()]));
                }
            }
        }
    }

       return parents;

}

void Graph::GenerareListaAdiacenta()
{

}

