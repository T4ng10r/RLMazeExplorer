#include <QtTest/QtTest>
#include "TestRunner.h"

class CKBLocationDataTest : public QObject
{
    Q_OBJECT
public:

	CKBLocationDataTest();
private Q_SLOTS:
	void testStateCreation();
	void testActionCorrectness();
	void testOneDecisionPoint();

};
DECLARE_TEST(CKBLocationDataTest)

