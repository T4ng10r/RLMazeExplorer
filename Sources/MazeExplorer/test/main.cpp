#include "CMazeTest.h"
#include "CKBLocationDataTest.h"
#include "CKnowledgeBaseTest.h"

int main(int argc, char *argv[]) 
{ 
	QCoreApplication app(argc, argv); 

	CMazeTest cMazeTestCase; 
	if (QTest::qExec(&cMazeTestCase, argc, argv)!=0)
		return -1;  

	CKBLocationDataTest cKBLocationDataTest;
	if (QTest::qExec(&cKBLocationDataTest, argc, argv)!=0)
		return -1; 

	CKnowledgeBaseTest cKnowledgeBaseTest;
	if (QTest::qExec(&cKnowledgeBaseTest, argc, argv)!=0)
		return -1; 
}
