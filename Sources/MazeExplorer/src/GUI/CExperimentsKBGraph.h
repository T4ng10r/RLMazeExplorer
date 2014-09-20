#pragma once
#include <QWidget>
#include <QPainter>
#include <QPicture>
#include <QPaintEvent>
#include <QRect>
#include <QPen>
#include <QFont>
#include <QFontMetrics>
#include <QScrollArea>
//#include <KnowledgeBase/CKBLocationData.h>
#include <Data/CMazeKnowlegdeBase.h>
const QSize sizeTreeLocation(100,80);
const QSize sizeText(25,10);
/*
class CExperimentsKBGraph : public QWidget
{
public:
    CExperimentsKBGraph(QWidget *parent=NULL);
    ~CExperimentsKBGraph(void);
//	void setRootNode(CKBLocationData * root);	////wyswietl ca³e drzewo KB traktuj¹c ten wezel jako korzen
    void setNode(CMazeKnowlegdeBase::CKBTreeNode	* ptNode);	//wyswietl dane dotyczace tego wezla w KB
    void setExplorationNodes(CMazeKnowlegdeBase::CKBTreeNode	* ptNode);

protected:
//	void fillLocationWithNodeData(QPicture &picture, CKBLocationData * node);
    void fillLocationWithNodeData(QPicture &picture, CMazeKnowlegdeBase::CKBTreeNode * ptNode);
//    QPicture & fillLocationWithNodeData(CKBTreeNode * ptNode);
    void prepareLocationToDraw();
    void paintEvent(QPaintEvent *event);
//	void drawVisitedTreeLocation(QPainter &painter, QRect &qRect, CKBLocationData * node, QPoint pos);
    void drawKBTreeNode(QPainter &painter,QRect &qEntireDrawArea,CMazeKnowlegdeBase::CKBTreeNode * rootNode,QPoint ptMiddleTop);
    CMazeKnowlegdeBase::CKBTreeNode	*       ptRootNode;
    bool				bSingleNode;
    QPicture			locationBasePicture;
    QFont	            font;
    QFontMetrics	    fontMetric;
    int                 iSidesTextWidth;  //szerokosc tekstu '999%' w Arialu
    bool                bFirst;


};
*/