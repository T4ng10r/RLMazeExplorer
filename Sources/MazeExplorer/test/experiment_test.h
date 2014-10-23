#include <QtTest>
#include <QObject>
#include <Data/experiment/experiment.h>
#include "TestRunner.h"

class experiment_test : public QObject
{
public:
	experiment_test();
	~experiment_test();

	void init_settings();
	void init_maze();
public:
	experiment_settings settings;
	maze_interface_type maze_;
	//CKnowledgeBaseTest();
private Q_SLOTS:
/*private Q_SLOTS:
	void init();
	void cleanup();
	void initTestCase();
	void testEmptyKB();
	void testSingleExploration();
	void testTwoExploration();*/
private:
    Q_OBJECT
};

DECLARE_TEST(experiment_test)

