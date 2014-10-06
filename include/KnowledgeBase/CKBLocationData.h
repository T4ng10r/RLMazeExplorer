#ifndef _KB_LOCATION_DATA_INCLUDE
#define _KB_LOCATION_DATA_INCLUDE
#include <map>
#include <vector>
#include <math.h>
const double fEspilon = 0.03;
typedef /*long*/ double ValueID;	//identyfikator mo�liwej do wykonania akcji

template<class StateID, class ActionID>
class CKBLocationData
{
public:
	typedef std::map <ActionID, ValueID>	Action2Probabilities;
    CKBLocationData(void):bCorrect(false) {};
    void setStateID(const StateID state)
    {	m_stateID = state;	}
    StateID getStateID()
    {	return m_stateID;	}
    //-------------------------------//
	const Action2Probabilities & getAllActions()
	{	return m_actionsProbabilities;		}
	//randomly returns action based on given fProbability
	//probability is counted from 0 till 1
    ActionID getActiondID(const double fProbability)
    {
        typename Action2Probabilities::iterator Iter;
        Action2Probabilities mActionsValuated;
        double currentValue=0;

		mActionsValuated = valuateActions();
        for(Iter=mActionsValuated.begin(); Iter!=mActionsValuated.end(); Iter++)
        {
            currentValue += Iter->second;
            if (fProbability<=(currentValue))
            {
                return Iter->first;
            }
        }
        return (ActionID)-1;
    }
    CKBLocationData<StateID, ActionID> * getStateIDByAction(const ActionID action)
    {
        typename std::map<ActionID,CKBLocationData>::iterator Iter;
        Iter = m_possibleActions.find(action);
        if (Iter==m_possibleActions.end())
            return nullptr;
        return &(Iter->second);
    }

    //void setAllAction(const vector< ActionID>  vActions);
    void setAllAction(const std::vector< ActionID>  vActions)
    {
        //typename vector< ActionID>::iterator Iter;
        for(unsigned int i=0; i<vActions.size(); i++)
        {
            addNewAction(vActions[i]);
        }
    }

    //void addNewAction(const ActionID action);
    void addNewAction(const ActionID action)
    {
        typename Action2Probabilities::iterator			Iter;
        Iter = m_actionsProbabilities.find(action);
        if (Iter==m_actionsProbabilities.end())
        {
            CKBLocationData<StateID, ActionID> newState;
            m_actionsProbabilities[action]=0;
            m_possibleActions[action] = newState;
        }
    }
    //void teach(const ActionID action, const ValueID value);
    void teach(const ActionID action, const ValueID value)
    {
        typename Action2Probabilities::iterator Iter;
        typename Action2Probabilities::iterator ActionTeached;
        int count = m_actionsProbabilities.size();
        if (count == 1)
            return;
        ActionTeached = m_actionsProbabilities.find(action);
        if (ActionTeached==m_actionsProbabilities.end())
            return;
        double val1 = ActionTeached->second;
        ActionTeached->second+=value;
		//ActionTeached->second = floor(ActionTeached->second*1000)/1000;
        val1 = ActionTeached->second;
    }
	void getDirections(Action2Probabilities &xmActionsProbabilities,bool bValuate=true)
	{
		Action2Probabilities mActionsValuated;
		if (bValuate)
			mActionsValuated = valuateActions();
		else
			mActionsValuated  =m_actionsProbabilities;

		xmActionsProbabilities = mActionsValuated;
	}
	//////////////////////////////////////////////////////////////////////////
	bool operator==(const CKBLocationData& sourceNode)
	{	return m_stateID==sourceNode.m_stateID;		}
	bool operator!=(const CKBLocationData& sourceNode)
	{	return !(this->operator==(sourceNode));		}
	bool operator<(const CKBLocationData& sourceNode)
	{	return m_stateID<sourceNode.m_stateID;	}
	void operator=(const CKBLocationData& sourceNode)
	{
		bCorrect = sourceNode.bCorrect;
		m_stateID = sourceNode.m_stateID;
		m_actionsProbabilities = sourceNode.m_actionsProbabilities;
		m_possibleActions = sourceNode.m_possibleActions;
	}

protected:
	Action2Probabilities softMax()
	{
		typename Action2Probabilities::iterator	Iter;
		Action2Probabilities  actions;

		ValueID sumValue=0;
		for(Iter = m_actionsProbabilities.begin();Iter != m_actionsProbabilities.end();Iter++)
			sumValue+=exp(Iter->second);

		//if (sumValue==0)
		for(Iter = m_actionsProbabilities.begin();Iter != m_actionsProbabilities.end();Iter++)
		{
			ValueID iVal = exp(Iter->second)/sumValue;
			actions.insert(std::make_pair(Iter->first,iVal));
		}
		return actions;
	}
	Action2Probabilities valuateActions()
	{
		return softMax();
		//return valuateActions1();
	}

    //sumuje wartosci kazdej z akcji, wynik traktuje jako 100%,
    //a nastepnie wylicza procentowo ile ktorej akcji jest w calosci
    //w ten sposob otrzymujemy procentowe prawdopodobnienstwa z dowolnych wartosci
    Action2Probabilities valuateActions1()
    {
        bool bAllMinus=true;
        bool bAllPlus=true;
        typename Action2Probabilities::iterator			Iter;
        Action2Probabilities  tempMap,actions;
        //Action2Probabilities  actions;
        int iZeroFound = 0,iPlusFound = 0,iMinusFound = 0,iCount;
        ValueID valuesSum = 0;
        double discount=0;


        //ValueID biggestMin = 0;



        tempMap = m_actionsProbabilities;
        //-------------------- znajdz najmniejsza wartość
        for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
            if (Iter->second > 0)
            {
                iPlusFound++;
                bAllMinus=false;
            }
            else if (Iter->second < 0)
            {
                iMinusFound++;
                bAllPlus=false;
            }
            else //if (Iter->second == 0)
            {
                iZeroFound++;
                bAllMinus=false;
                bAllPlus=false;
            }
        iCount=tempMap.size();
        //--- zwieksza prawdobod. wszystkich akcji tak by zadne z nich nie bylo mniejsze od zera
//		if (biggestMin !=0)
//			for(Iter=tempMap.begin();Iter!=tempMap.end();Iter++)
//				Iter->second +=-biggestMin;

        if (iMinusFound==iCount || iPlusFound==iCount)
        {
            for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
            {
                valuesSum+= (iPlusFound==iCount ? Iter->second : -Iter->second );
            }

            for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
            {
                actions[Iter->first] =
                    (( (iPlusFound==iCount ? 0 : valuesSum ) + Iter->second))/valuesSum;
            }
        }
        else if (iZeroFound==iCount)
        {
            for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
                actions[Iter->first] = 100/iZeroFound;
        }

        //// obliczamy rozklad dla
        // musimy uwzglednic dla zer minimalna szanse ich wybrania
        else if (iPlusFound==0)
        {
            do
            {
                iZeroFound=0;
                valuesSum=0;
                //--- ustal ilosc zerowych prawdobod. i zsumuj je wszystkie
                for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
                {
                    if (Iter->second==0) iZeroFound++;
                    valuesSum+=Iter->second;
                }
                //--- jesli sa jakies zerowe prawdobod. wsrod innych niezerowych
                //--- to zwieksz
                if (iZeroFound>0 && valuesSum!=0)
                    for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
                    {
                        if (Iter->second==0) Iter->second = valuesSum*(fEspilon/iZeroFound);
                    }
                else if (valuesSum==0)
                    iZeroFound=0;
            }
            while(iZeroFound>0);
            //Q_ASSERT(valuesSum!=0);
            discount = 100/valuesSum;
            for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
                actions[Iter->first] = Iter->second*discount;
        }
        else if (iMinusFound==0)
        {
            do
            {
                iZeroFound=0;
                valuesSum=0;
                //--- ustal ilosc zerowych prawdobod. i zsumuj je wszystkie
                for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
                {
                    if (Iter->second==0) iZeroFound++;
                    valuesSum+=Iter->second;
                }
                //--- jesli sa jakies zerowe prawdobod. wsrod innych niezerowych
                //--- to zwieksz
                if (iZeroFound>0 && valuesSum!=0)
                    for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
                    {
                        if (Iter->second==0) Iter->second = valuesSum*(fEspilon/iZeroFound);
                    }
                else if (valuesSum==0)
                    iZeroFound=0;
            }
            while(iZeroFound>0);
            //Q_ASSERT(valuesSum!=0);
            discount = 100/valuesSum;
            for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
                actions[Iter->first] = Iter->second*discount;
        }
        else
        {
        }
        return actions;
        //ustawiamy dla zer minimalna szanse ich wybrania

        //discount to mnoznik ktory przemnozony daje procentowe prawdopodobienstwo
        if (valuesSum!=0)
        {
            discount = 100/valuesSum;
            discount = discount<0?-discount:discount;
        }
        for(Iter=tempMap.begin(); Iter!=tempMap.end(); Iter++)
        {
            if (valuesSum==0)
                actions[Iter->first] = 100/m_actionsProbabilities.size();
            else
                actions[Iter->first] = Iter->second*discount;
        }
        return actions;
    }

    bool bCorrect;
    StateID m_stateID;
    Action2Probabilities		m_actionsProbabilities;
    std::map<ActionID,CKBLocationData>	m_possibleActions;
};
#endif
