#include "CKBStateDataTest.h"
#include <Data/experiment/EnviromentVariables.h>
#include <set>
/*
class CTestDecisionPoint : public CDecisionPoint
{
public:
	LocationDirs locDirs;
protected:
	virtual bool blindlyEquals(const CDecisionPoint *that) const {
		const CTestDecisionPoint *castedThat = dynamic_cast<const CTestDecisionPoint*>(that);
		// perform comparisons on private data
		bool isEqual = (this->locDirs == castedThat->locDirs);
		return (isEqual && CDecisionPoint::blindlyEquals(that));
	}
	virtual const std::type_info* getTypeEquiv() const {
		return &typeid(*(new CTestDecisionPoint()));
	}
};

class CTestActions : public CActions
{
public:
	directions dirs;
protected:
	virtual bool blindlyEquals(const CActions *that) const {
		const CTestActions *castedThat = dynamic_cast<const CTestActions*>(that);
		// perform comparisons on private data
		bool isEqual = (this->dirs == castedThat->dirs);
		return (isEqual && CActions::blindlyEquals(that));
	}
	virtual const std::type_info* getTypeEquiv() const {
		return &typeid(*(new CTestActions()));
	}
};


CKBStateDataTest::CKBStateDataTest()
{}
void CKBStateDataTest::testStateCreation()
{
	//create two states
	CKBStateData state1;
	CKBStateData state2;
	CKBStateData state3;

	//create two states descriptions
	CTestDecisionPoint stateID1;
	stateID1.locDirs = LOCATION_FRONT;
	state1.setStateID(&stateID1);
	CTestDecisionPoint stateID2;
	stateID2.locDirs = LOCATION_LEFT;
	state2.setStateID(&stateID2);

	CTestDecisionPoint stateID3;
	stateID3.locDirs = LOCATION_FRONT;
	state3.setStateID(&stateID3);

	QVERIFY(state2!=state1);
	QVERIFY(state2!=state3);
    QVERIFY(state3==state1);
}
void CKBStateDataTest::testActionCorrectness()
{
	//CKBStateData state1;

	//CTestActions * action1 =  &state1.getActiondID(1);
	//action1.dirs=FRONT_DIR;

	//QVERIFY(action1.getCorrectnes()==false);
	//QCOMPARE(state1.getAllActions().size(),(unsigned int)0);

	//std::vector< CTestActions> vActions;
	//vActions.push_back(action1);
	//state1.setAllAction(vActions);
	//QCOMPARE(state1.getAllActions().size(),(unsigned int)1);

	//CTestActions action2 =  state1.getActiondID(1);
	//action2.dirs=FRONT_DIR;

	//CTestActions action3 =  state1.getActiondID(1);
	//action3.dirs=LEFT_DIR;

	//QVERIFY(action2.getCorrectnes()==true);
	//QVERIFY(action2==action1);
	//QVERIFY(action3!=action1);

}
*/
