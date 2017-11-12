#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{
  // students must write this
  BTreeNode* newNode;
  int pos = count - 1;
  while (value < keys[pos] && pos > 0)
    --pos;
  newNode = children[pos]->insert(value);
  updateKeys();

  if (newNode && count < internalSize)
  {
    insert(newNode);
  }
  else
  {
    if (newNode && leftSibling && leftSibling->getCount() < internalSize)
    {
      InternalNode* leftInternal = dynamic_cast<InternalNode*>(leftSibling);
      leftInsert(leftInternal, newNode);
    }
    else
    {
      if (newNode && newNode->getMinimum() < keys[internalSize - 1] &&
        rightSibling && rightSibling->getCount() < internalSize)
      {
        InternalNode* rightInternal = dynamic_cast<InternalNode*>(rightSibling);
        rightInsert(rightInternal, newNode);
      }
      else
      {
        if (newNode && rightSibling && rightSibling->getCount() < internalSize)
        {
          InternalNode* rightInternal = dynamic_cast<InternalNode*>(rightSibling);
          rightInternal->insert(newNode);
        }
        else
        {
          if (newNode)
          {
            InternalNode* newInternal = splitInternal(newNode);
            setRightSibling(newInternal);
            return newInternal;
          }
        }
      }
    }
  }
  updateKeys();
  return NULL; // to avoid warnings for now.
} // InternalNode::insert()


void InternalNode::leftInsert(InternalNode* leftInternal, BTreeNode* newNode)
{
  leftInternal->insert(children[0]);
  children[0]->setParent(leftInternal);
  for (int pos = 0; (pos < internalSize); pos++)
  {
    keys[pos] = keys[pos + 1];
    children[pos] = children[pos + 1];
  }
  --count;
  insert(newNode); 
  if (parent)
    parent->updateKeys();
} // InternalNode::leftInsert()


void InternalNode::rightInsert(InternalNode* rightInternal, BTreeNode* newNode)
{
  rightInternal->insert(children[internalSize - 1]);
  children[internalSize - 1]->setParent(rightInternal);
  --count;
  insert(newNode);
  if (parent)
    parent->updateKeys();
} // InternalNode::rightInsert()


void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  int pos;
  for (pos = count - 1; pos >= 0 && (newNode->getMinimum() < keys[pos]); pos--)
  {
    keys[pos + 1] = keys[pos];
    children[pos + 1] = children[pos];
  }

  keys[++pos] = newNode->getMinimum();
  children[pos] = newNode;
  count++;
  updateKeys();
} // InternalNode::insert()


InternalNode* InternalNode::splitInternal(BTreeNode* newNode)
{
  InternalNode *newSibling = new InternalNode(internalSize, leafSize, 
                                                      parent, this, rightSibling);
  if (rightSibling)
    rightSibling->setLeftSibling(newSibling);
  rightSibling = newSibling;

  int pos = (double(internalSize)/2) + 0.5;

  if (newNode->getMinimum() < keys[pos - 1])
  {
    for (int i = pos - 1; i < internalSize; i++)
    {
      newSibling->insert(children[i]);
      children[i]->setParent(newSibling);
      --count;
    }
    insert(newNode);
  }
  else
  {
    for (int i = pos; i < internalSize; i++)
    {
      newSibling->insert(children[i]);
      children[i]->setParent(newSibling);
      --count;
    }
    newSibling->insert(newNode);
    newNode->setParent(newSibling);
  }

  if (parent)
    parent->updateKeys();
  return newSibling;
} // InternalNode::splitInternal()


void InternalNode::updateKeys()
{
  for (int i = 0; i < count; i++)
    keys[i] = children[i]->getMinimum();

 if (parent)
   parent->updateKeys();
} //InternalNode::updateKeys()


void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  // students must write this
  insert(oldRoot);
  insert(node2);

} // InternalNode::insert()


void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


