#include "CKnowledgeBaseTest.h"

void CKnowledgeBaseTest::initTestCase()
{
	//std::vector<std::pair< LocationDirs, directions > >	vPath;
	std::pair< LocationDirs, directions > stPair;

	stPair.first = LOCATION_FR;
	stPair.second = FRONT_DIR;
	vPathFirstExploration.push_back(stPair);
	//////////////////////////////////////////////////////////////////////////
	stPair.second = RIGHT_DIR;
	vPathSecondExploration.push_back(stPair);
	vPathThirdExploration = vPathSecondExploration;
	stPair.second = RIGHT_DIR;
	vPathSecondExploration.push_back(stPair);
	//////////////////////////////////////////////////////////////////////////
}
void CKnowledgeBaseTest::init()
{
	ptrKB = new CKnowlegdeBase;	
}
void CKnowledgeBaseTest::cleanup()
{
	delete ptrKB;	
	ptrKB=NULL;	
}
void CKnowledgeBaseTest::testEmptyKB()
{
	CKBTreeNode * treeNode = ptrKB->getCurrentNode();
	QVERIFY(treeNode!=NULL);
	QCOMPARE(treeNode->getStateID(), LocationDirs(LOCATION_EMPTY));
}
void CKnowledgeBaseTest::testSingleExploration()
{
	CKBTreeNode * treeNode = ptrKB->getCurrentNode();
	QVERIFY(treeNode!=NULL);
	for(ExplorationPath::const_iterator iterPath = vPathFirstExploration.begin();iterPath != vPathFirstExploration.end();iterPath++)
	{
		QCOMPARE(treeNode->getStateID(),LocationDirs(LOCATION_EMPTY));
		LocationDirs locDirs = LocationDirs(iterPath->first);
		treeNode->setStateID(locDirs);
		treeNode->setAllAction(locDirs.Directions());
		treeNode = treeNode->getStateIDByAction(iterPath->second);
		QVERIFY(treeNode!=NULL);
	}
}
void CKnowledgeBaseTest::testTwoExploration()
{
	CKBTreeNode * treeNode = ptrKB->getCurrentNode();
	QVERIFY(treeNode!=NULL);
	for(ExplorationPath::const_iterator iterPath = vPathFirstExploration.begin();iterPath != vPathFirstExploration.end();iterPath++)
	{
		QCOMPARE(treeNode->getStateID(),LocationDirs(LOCATION_EMPTY));
		LocationDirs locDirs = LocationDirs(iterPath->first);
		treeNode->setStateID(locDirs);
		treeNode->setAllAction(locDirs.Directions());
		treeNode = treeNode->getStateIDByAction(iterPath->second);
		QVERIFY(treeNode!=NULL);
	}

	ptrKB->ResetRootNode();
	treeNode = ptrKB->getCurrentNode();
	for(ExplorationPath::const_iterator iterPath = vPathSecondExploration.begin();iterPath != vPathSecondExploration.end();iterPath++)
	{
		LocationDirs locDirs = LocationDirs(iterPath->first);
		if (treeNode->getStateID()==LOCATION_EMPTY)
		{
			treeNode->setStateID(locDirs);
			treeNode->setAllAction(locDirs.Directions());
		}
		treeNode = treeNode->getStateIDByAction(iterPath->second);
		QVERIFY(treeNode!=NULL);
	}
}
