#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include "LibDef.h"

template <class KEY, class VALUE>
class HashTable
{
	//Hash Table Structures
	private:

		struct Hash
		{
			KEY key;
			VALUE value;

			Hash& operator =(const Hash& rhs)
			{
				key = rhs.key;
				value = rhs.value;
			}
		};

		struct Node
		{
			Hash hash;
			Node* next;

			Node() : hash(), next(0) {}

			Node& operator =(const Node& rhs)
			{
				hash = rhs.hash;
				next = rhs.next;
			}
		};

	public:

		//--constructor--//
		HashTable<KEY, VALUE>(void);
		~HashTable<KEY, VALUE>(void);

		//--Public Member Methods--//
		void  Add			(KEY key, VALUE value);
		bool  TryGetValue	(KEY key, VALUE& out);
		bool  Remove		(KEY key);
		bool  Remove		(VALUE toRemove);
		void  Clear			(bool doDelete = false);
		void  CopyPointer	(HashTable<KEY, VALUE>& src, bool deleteSource);
		int   GetSize		(void) const;

	private:
		
		//--private Methods--//
		void ClearList	(Node *list, bool doDelete);

		//--Members--//
		Node *_list;
		int   _size;
};

#include "HashTable.inl"

#endif