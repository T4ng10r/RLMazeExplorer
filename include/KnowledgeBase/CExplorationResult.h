#ifndef _EXPLORATION_RESULTS_INCLUDE_
#define _EXPLORATION_RESULTS_INCLUDE_

#include <vector>

template<class StateID, class ActionID>
class CExplorationResult
{
public:
	//CExplorationResult();
	//~CExplorationResult();
	virtual void	clear()		{	m_vDecisions.clear();	}
	void	addDecision(StateID stateID, ActionID actionID);
	size_t	getDecisionsCount()		{	return m_vDecisions.size();		}
	bool	getDecisionPoint(unsigned int nr,StateID &stateID, ActionID &actionID)
	{
		if (m_vDecisions.size()>=nr)
			return false;
		stateID = m_vDecisions[nr].first;
		actionID = m_vDecisions[nr].second;
		return true;
	}
	bool	bExplorationSuccessful;
protected:
	std::vector<std::pair< StateID, ActionID> >			m_vDecisions;
};
#endif //_EXPLORATION_RESULTS_INCLUDE_
