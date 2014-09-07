#include <QtTest/QtTest>


class CKBLocationDataTest : public QObject
{
    Q_OBJECT
public:

    CKBLocationDataTest();
private slots:
	void testStateCreation();
	void testActionCorrectness();
	void testOneDecisionPoint();

};

