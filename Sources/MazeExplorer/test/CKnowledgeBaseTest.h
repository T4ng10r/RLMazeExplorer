#include <QtTest/QtTest>
#include <KnowledgeBase/CKnowlegdeBase.h>

class CKnowledgeBaseTest : public QObject
{
    Q_OBJECT
public:
    //CKnowledgeBaseTest();
	CKnowlegdeBase * ptrKB;	
	//FAILED
	typedef std::vector<std::pair< LocationDirs, directions > > ExplorationPath;
	ExplorationPath	vPathFirstExploration;
	//FAILED
	ExplorationPath	vPathSecondExploration;
	//FAILED
	ExplorationPath	vPathThirdExploration;
private slots:
	void init();
	void cleanup();
	void initTestCase();
	void testEmptyKB();
	void testSingleExploration();
	void testTwoExploration();
};
