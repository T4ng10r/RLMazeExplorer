#include "CKBLocationDataTest.h"
#include "CKnowledgeBaseTest.h"
#include "TestRunner.h"

int main(int argc, char *argv[]) 
{ 
	QCoreApplication app(argc, argv); 
  if (RUN_ALL_QTESTS(argc, argv)>0)
  {
          return -1;
  }
  return 0;
}
