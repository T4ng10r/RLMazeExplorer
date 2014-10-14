#ifndef EXPERIMENT_MANAGER_HPP
#define EXPERIMENT_MANAGER_HPP

#include <list>
#include <Data/experiment/experiment.h>

//Manages experiments
class CExperimentManager
{
public:
    CExperimentManager(void);
    ~CExperimentManager(void);

	experiment	& getCurrentExperiment();
	experiment	stExperiment;

	maze		m_stCurrentMaze;

};
#endif	/*EXPERIMENT_MANAGER_HPP*/
