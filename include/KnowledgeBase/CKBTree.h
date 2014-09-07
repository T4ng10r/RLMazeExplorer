#ifndef CKBTREE_H
#define CKBTREE_H
#include "CKBStateData.h"

class CKBTreeBase : public CKBStateData
{
public:
	CKBTreeBase(): currentNode(NULL)
	{
		currentNode = &root;
	}
    ~CKBTreeBase();
    void loadTree() {};
    void saveTree() {};
	void resetCurrentNode()
	{
		currentNode = &root;
	}
    CKBStateData & getCurrentNode()
	{
		return *currentNode;
	}
    void learnFromRoute() {};
    //void resetRootNode();

protected:

    CKBStateData root;
    CKBStateData *	currentNode;
};
#endif
