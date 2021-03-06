#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"
#include "LeafNode.h"
#include "InternalNode.h"
using namespace std;

BTree::BTree(int ISize, int LSize):internalSize(ISize), leafSize(LSize)
{
  root = new LeafNode(LSize, NULL, NULL, NULL);
} // BTree::BTree()


void BTree::insert(const int value)
{
  // students must write this
  BTreeNode* newNode;
  newNode = root->insert(value);
  if (newNode)
  {
    BTreeNode* oldRoot;
    InternalNode* internal = new InternalNode(internalSize, leafSize,
      NULL, NULL, NULL);
    oldRoot = root;
    internal->insert(oldRoot, newNode);
    oldRoot->setParent(internal);
    newNode->setParent(internal);
    root = internal;
  } 
} // BTree::insert()


void BTree::print()
{
  BTreeNode *BTreeNodePtr;
  Queue<BTreeNode*> queue(1000);

  queue.enqueue(root);
  while(!queue.isEmpty())
  {
    BTreeNodePtr = queue.dequeue();
    BTreeNodePtr->print(queue);
  } // while
} // BTree::print()
