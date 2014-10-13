#include "CKBLocationDataTest.h"
#include <set>
#include <KnowledgeBase/CKBLocationData.h>
#include <Experiment/EnviromentVariables.h>

typedef CKBLocationData<LocationDirs,directions> CKBTreeNode;

CKBLocationDataTest::CKBLocationDataTest()
{}
void CKBLocationDataTest::testStateCreation()
{
	CKBTreeNode state1;
	CKBTreeNode state2;
	CKBTreeNode state3;

	state1.setStateID(LOCATION_FRONT);
	state2.setStateID(LOCATION_LEFT);
	state3.setStateID(LOCATION_FRONT);

	QVERIFY(state2!=state1);
	QVERIFY(state2!=state3);
    QVERIFY(state3==state1);
}
void CKBLocationDataTest::testActionCorrectness()
{
	CKBTreeNode state1;

	state1.setStateID(LOCATION_FL);

	directions dirAction = state1.getActiondID(1);
	QCOMPARE(dirAction,ERROR_DIR);
	QCOMPARE(state1.getAllActions().size(),(unsigned int)0);

	std::vector< directions > vActions;
	vActions.push_back(FRONT_DIR);
	vActions.push_back(LEFT_DIR);
	state1.setAllAction(vActions);
	QCOMPARE(state1.getAllActions().size(),(unsigned int)2);

	directions dirAction1 = state1.getActiondID(0.3);
	QCOMPARE(dirAction1,FRONT_DIR);
	dirAction1 = state1.getActiondID(0.6);
	QCOMPARE(dirAction1,LEFT_DIR);
}
void CKBLocationDataTest::testOneDecisionPoint()
{
	CKBTreeNode state1;
	state1.setStateID(LOCATION_FL);

	std::vector< directions > vActions;
	vActions.push_back(FRONT_DIR);
	vActions.push_back(LEFT_DIR);
	state1.setAllAction(vActions);

	CKBTreeNode  * state2 = state1.getStateIDByAction(FRONT_DIR);
	QVERIFY(NULL!=state2);
	state2->setStateID(LOCATION_FLR);

	CKBTreeNode  * state3 = state1.getStateIDByAction(LEFT_DIR);
	QVERIFY(NULL!=state3);
	state3->setStateID(LOCATION_LR);


}
