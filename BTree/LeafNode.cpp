#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()

int LeafNode::getMaximum()const
{
  if (count > 0)
    return values[count - 1];
  else
    return 0;
} // LeafNode::getMaximum()

LeafNode* LeafNode::insert(int value)
{
  if (count < leafSize)
  {
    insertValue(value);
  }
  else
  {
    BTreeNode* left = getLeftSibling();
    BTreeNode* right = getRightSibling();
    if (left && left->getCount() < leafSize) //deleted value > getMinimum()
    {
      int passVal = getMinimum();
      left->insert(passVal);
      for (int pos = 0; (pos < leafSize); pos++)// && (value > values[pos]); pos++)
        values[pos] = values[pos + 1];
      --count;
      insert(value);
      resetMinimum();
    } // commented out (value > values[pos] since it was not moving down the values correctly
    else
    {
      if ( value < getMaximum() && right && right->getCount() < leafSize)
      { // can write getMaximum() to change the val[leafS - 1] 
        int passVal = values[leafSize - 1];
        right->insert(passVal);
        --count;
        insert(value);
        resetMinimum();
      }
      else
      {
        if (right && right->getCount() < leafSize)
        {
          right->insert(value);
          parent->updateKeys();
          resetMinimum();
        }
        else//if (value > getMinimum())
        {
          LeafNode* newNode = splitNode(value);
          setRightSibling(newNode);
          return newNode;
        } // split-right/left only used to redirect neighbors, they actually do the same
      }
    }
  }
  return NULL;
}

// deleted splitLef since it was exacly the same as split right (splitNode)

void LeafNode::insertValue(int value)
{
  int pos;

  for (pos = count - 1; pos >= 0 && (value < values[pos]); pos--)
    values[pos+1] = values[pos];

  values[++pos] = value;
  count++;
  resetMinimum();
} // LeafNode::insertValue()


void LeafNode::resetMinimum()
{
  if (parent)
    parent->updateKeys();
} // LeafNode::resetMinimum()

LeafNode* LeafNode::splitNode(int value)
{
  LeafNode *newSibling = new LeafNode(leafSize, parent, this, rightSibling); 

  int pos = (double(leafSize)/2) + 0.5;

  if (rightSibling)
    rightSibling->setLeftSibling(newSibling);
  rightSibling = newSibling;

  if (value < values[pos - 1])
  {
    for (int i  = pos - 1; i < leafSize; i++)
    {
      newSibling->insert(values[i]);
      --count;
    } // move values to new sibling starting from the ceil(L/2)
    insert(value);
  }
  else
  {
    for (int i = pos; i < leafSize; i++)
    {
      newSibling->insert(values[i]);
      --count;
    }
    newSibling->insert(value);
  }
  
  resetMinimum();

  return newSibling;
} // LeafNode::splitNode()


void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


