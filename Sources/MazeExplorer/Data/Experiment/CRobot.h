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
    void	robotStartExploring();					//rozpocznij w�dr�wk� robota
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
    void	onOneExit();			//robot mo�e i�c tylko w jedn� stron�
    void	onChooseExit();			//robot mo�e dokona� wyboru
    int		howManyExits();			//ile wyj�� z danej lokacji
//	QList<int >				sectorExits;			//wynik skanowania lokacji
    CMazeKnowlegdeBase			* pKB;				//baza wiedzy
    CScanResults			currentScanResult;

};
#endif
