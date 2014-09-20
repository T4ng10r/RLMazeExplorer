#ifndef EXPERIMENT_MANAGER_HPP
#define EXPERIMENT_MANAGER_HPP

#include <list>
#include <Data/Experiment/CExperiment.h>

//Manages experiments
class CExperimentManager
{
public:
    CExperimentManager(void);
    ~CExperimentManager(void);

	CExperiment	& getCurrentExperiment();
	CExperiment	stExperiment;

	maze		m_stCurrentMaze;

};
#endif	/*EXPERIMENT_MANAGER_HPP*/