#include <QtTest/QtTest>
#include <KnowledgeBase/CKBStateData.h>

class CKBStateDataTest : public QObject
{
    Q_OBJECT
public:

    CKBStateDataTest();
private slots:
	void testStateCreation();
	void testActionCorrectness();

};

