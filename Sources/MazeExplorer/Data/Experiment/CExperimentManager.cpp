#include "CExperimentManager.h"

CExperimentManager::CExperimentManager(void)
{}
CExperimentManager::~CExperimentManager(void){}
CExperiment	& CExperimentManager::getCurrentExperiment()
{
	return stExperiment;
};
