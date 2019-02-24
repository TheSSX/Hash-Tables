#ifndef MY_HASH_NODE
#define MY_HASH_NODE

#include <iostream>
using namespace std;

template <class KeyType, class ValueType>
class HashNode {
  KeyType key;     // The hash node's key
  ValueType value; // The key's associated data
  HashNode *next;

  /* extend if necessary */

public:

  HashNode();  // constructor

  KeyType getKey() { return key; }
  ValueType getValue() { return value; }
  void assign(KeyType key, ValueType value); 
  HashNode getNext();
  void setNext(HashNode<KeyType, ValueType>);

  // extend if necessary
};

template <class KeyType, class ValueType>
HashNode<KeyType, ValueType>::HashNode()
{
	/*
	if (node == NULL)
	{
		something to send OUT_OF_MEMORY back
	}
	*/

	next = NULL;
}

template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::assign(KeyType key, ValueType value)
{
	this->key = key;
	this->value = value;
}

template <class KeyType, class ValueType>
HashNode<KeyType, ValueType> HashNode<KeyType, ValueType>::getNext()
{
	return next;
}


/* 
   Implement the constructor, the assign method 
   and any methods that you may additionally need for the HashTable to work.
*/

#endif
