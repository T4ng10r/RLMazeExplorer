#ifndef _KNOWLEDGE_BASE_INCLUDE_
#define _KNOWLEDGE_BASE_INCLUDE_

#include <KnowledgeBase/CKBLocationData.h>
#include <KnowledgeBase/CExplorationResult.h>
#include <Data/Experiment/EnviromentVariables.h>

#include <vector>
#include <map>
#include <string>
#include <time.h>

enum choosingExitsMethod
{
    staticOneLocationLearning,
    treeOfLastDecisionPoints
};


template<class StateID, class ActionID>
class CKnowlegdeBase
{
public:
	typedef CKBLocationData<StateID,ActionID> CKBTreeNode;

	CKnowlegdeBase(void): m_eTeachMethod(treeOfLastDecisionPoints),m_ptrCurrentNode(NULL){};
	~CKnowlegdeBase(void){};
	//resets entire KB (quantities and KBRoot)
	void ResetRootNode()	{	m_ptrCurrentNode = &m_stKBRoot;	}
	CKBTreeNode * getCurrentNode()	{	return m_ptrCurrentNode;	}

	CExplorationResult<StateID,ActionID> * getCurrentExplorationResult() const { return m_ptrCurrentExplorationResult; }
	void setCurrentExplorationResult(CExplorationResult<StateID,ActionID> * val) { m_ptrCurrentExplorationResult = val; }

	void teach(double value,bool bReward)
	{
		if (m_ptrCurrentExplorationResult!=NULL)	return;
		m_ptrCurrentExplorationResult->bExplorationSuccessful=bReward;
		switch(m_eTeachMethod)
		{
		case treeOfLastDecisionPoints:
			treeLearningPolicy(m_ptrCurrentExplorationResult,value,bReward);
			break;
		default:
			break;
		}
	};
	//*******************************************************************//
	virtual ActionID chooseExit(StateID stateID)
	{
		static unsigned int before=1;
		double			probability;
		directions		result;

		unsigned int seed = (unsigned)time( NULL );
		seed =seed+seed%before++;
		srand(seed);
		probability=rand()%100;

		switch(m_eTeachMethod)
		{
		case staticOneLocationLearning:
			//		result = m_mOneLocation[locationID].getLocation(probability);
			break;
		case treeOfLastDecisionPoints:
			result = chooseExitFromTree(stateID,probability);
			break;
		}
		return (ActionID)-1;
	}
	virtual ActionID chooseExitFromTree( StateID stateID,double probability )=0;
protected:
	virtual void treeLearningPolicy(CExplorationResult<StateID,ActionID> *lastExplorationResult, double value, bool bReward) = 0;
	
protected:
	choosingExitsMethod		m_eTeachMethod;
	CExplorationResult<StateID,ActionID>	*	m_ptrCurrentExplorationResult;
	CKBTreeNode				m_stKBRoot;
	CKBTreeNode *			m_ptrCurrentNode;

};
#endif // _KNOWLEDGE_BASE_INCLUDE_
