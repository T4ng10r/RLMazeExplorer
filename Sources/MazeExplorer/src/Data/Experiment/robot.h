#ifndef ROBOT_H
#define ROBOT_H
#include <memory>
#include <Data/CMazeKnowlegdeBase.h>
#include <Data/CScanResults.h>

class robot_private;

class robot : public QObject
{
    Q_OBJECT
public:
    robot(void);
    ~robot(void);
	void	setKnowledgeBase(CMazeKnowlegdeBase * KnowlegdeBase);
    void	start_exploring();					//rozpocznij wêdrówkê robota
	void	setOneStep(bool bOne);
Q_SIGNALS:
    void	robotMoved();	//robot zrobil krok do przodu
    void	robotRotate(bool bRight,bool bBack);
    void	is_in_exit(bool &bIsInExit);
    void	robotScans(CScanResults *);
	void	robotBeforeMove(CScanResults *);
protected:
	std::unique_ptr<robot_private> pimpl;
};
#endif
