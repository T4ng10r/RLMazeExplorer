#include <QtTest/QtTest>
#include <KnowledgeBase/CKnowlegdeBase.h>
#include <Data/experiment/EnviromentVariables.h>
#include "TestRunner.h"

typedef CKnowlegdeBase<LocationDirs ,directions> KnowlegdeBase;

class CKnowledgeBaseTest : public QObject
{
    Q_OBJECT
public:
	//CKnowledgeBaseTest();
    KnowlegdeBase * ptrKB;
	//FAILED
	typedef std::vector<std::pair< LocationDirs, directions > > ExplorationPath;
	ExplorationPath	vPathFirstExploration;
	//FAILED
	ExplorationPath	vPathSecondExploration;
	//FAILED
	ExplorationPath	vPathThirdExploration;
/*private Q_SLOTS:
	void init();
	void cleanup();
	void initTestCase();
	void testEmptyKB();
	void testSingleExploration();
	void testTwoExploration();*/
};

DECLARE_TEST(CKnowledgeBaseTest)
