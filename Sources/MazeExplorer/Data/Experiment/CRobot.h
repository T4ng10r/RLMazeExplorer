#ifndef ROBOT_H
#define ROBOT_H
#include <QList>
#include <QPair>
#include <QVector>
#include <Data/CMazeKnowlegdeBase.h>
#include <Data/CScanResults.h>

class CRobot : public QObject
{
    Q_OBJECT
public:
    CRobot(void);
    ~CRobot(void);
    void	setKnowledgeBase(CMazeKnowlegdeBase * KnowlegdeBase)  {	pKB = KnowlegdeBase;	}
    void	robotStartExploring();					//rozpocznij wêdrówkê robota
    void	setOneStep(bool bOne)	{	bOneStep=bOne;	}
signals:
    void	robotMoved();	//robot zrobil krok do przodu
    void	robotRotate(bool bRight,bool bBack);
    void	checkIfInExit(bool &bIsInExit);
    void	robotScans(CScanResults *);
	void	robotBeforeMove(CScanResults *);
protected:
    bool	bOneStep;
    void	scanLocation();
    void	onOneExit();			//robot mo¿e iœc tylko w jedn¹ stronê
    void	onChooseExit();			//robot mo¿e dokonaæ wyboru
    int		howManyExits();			//ile wyjœæ z danej lokacji
//	QList<int >				sectorExits;			//wynik skanowania lokacji
    CMazeKnowlegdeBase			* pKB;				//baza wiedzy
    CScanResults			currentScanResult;

};
#endif
