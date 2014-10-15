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
	void	setKnowledgeBase(maze_knowlegde_base * KnowlegdeBase);
	void	start_exploring();					//rozpocznij w�dr�wk� robota
	void	setOneStep(bool bOne);
Q_SIGNALS:
	void	move_forward();	//robot zrobil krok do przodu
	void	rotate(bool bRight,bool bBack);
	void	is_in_exit(bool &bIsInExit);
	void	robotScans(scan_results_handle );
	void	robotBeforeMove(scan_results_handle );
protected:
	std::unique_ptr<robot_private> pimpl;
};
#endif
