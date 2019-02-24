#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>
//#include <string>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY }; // extend if necessary

template <class KeyType, class ValueType>
class HashTable {
  typedef vector <HashNode<KeyType,ValueType> > Table;
  Table *table; // size of table (# of buckets) is stored in the Table data structure
  size_t num;   // number of entries stored in the HashTable;

public:
  HashTable();        // constructor, initializes table of size 11;
  HashTable(size_t);  // constructor, requires size of table as arg
  ~HashTable();       // destructor

  size_t size();      // returns size of the hash table (number of buckets)
  size_t hash_function(KeyType);  // the table's hash function
  ValueType getValue(KeyType);    // find and return data associated with key

  void insert(KeyType,ValueType); // insert data associated with key into table
  void erase(KeyType);            // remove key and associated data from table

  void rehash(size_t); // sets a new size for the hash table, rehashes the hash table 
  // extend if necessary
};



template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable()
{
	num = 0;
	table = new Table(11);

	for (unsigned int i=0; i<table->size(); i++)
	{
		table[i] = NULL;
	}
}

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(size_t x)
{
	num = 0;
	table = new Table(x);

	for (unsigned int i=0; i<table->size(); i++)
	{
		table[i] = NULL;
	}
}

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::~HashTable()
{
	for (unsigned int i=0; i<table->size(); i++)
	{
		table->pop_back();
	}

	delete table;
}

/*
 * Credit goes to user "Nick" on stackoverflow.com
 * Original link: https://stackoverflow.com/questions/8317508/hash-function-for-a-string
 */
template <class KeyType, class ValueType>
size_t HashTable<KeyType, ValueType>::hash_function(KeyType key)
{
   int seed = 141;
   unsigned long hash = 0;

   for(unsigned int i=0; i<sizeof(key); i++)
   {
	   hash = (hash * seed) + key[i];
   }

   return hash % HashTable<KeyType,ValueType>::size();
}

template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::insert(KeyType key,ValueType value)
{
	size_t index = hash_function(key);
	HashNode<KeyType, ValueType> newNode;
	newNode.assign(key, value);

	if (table.at(index) != NULL)
	{
		HashNode<KeyType, ValueType> current;
		current = table->at(index);

		while (current.getNext() != NULL)
		{
			current = current.getNext();
		}

		current.setNext(newNode);
	}
	else
	{
		table->at(index) = newNode;
	}

	num++;
}

//Function size() that uses the templates is being defined outside the class. This means the templates must be declared again.
template <class KeyType, class ValueType>
size_t HashTable<KeyType,ValueType>::size() {		//Templates must be explicitly stated in angle brackets after the class name
  return table->size();
}

/* Implement the 
- Constructors, Destructor
- hash_function, insert, getValue methods
- erase, and rehash methods 
*/

#endif
