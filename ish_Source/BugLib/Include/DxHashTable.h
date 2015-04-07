#ifndef _DX_HASH_TABLE
#define _DX_HASH_TABLE

#include "DxLibraryDef.h"

template <class T, class V>
class DxHashTable
{
	//Hash Table Structures
	private:

		struct Hash
		{
			V value;
			T key;
		};

		struct Node
		{
			Hash hash;
			Node* next;
		};

	//constructor
	public:
		DxHashTable<T, V>(void);
		~DxHashTable<T, V>(void);

	public:
		V	operator [](T key);

	//Public Member Methods
	public:
		void Add		(T key, V value);
		V	 GetValue	(T key);
		bool TryGetValue(T key, V out);
		bool Remove		(T key);
		bool Remove		(V toRemove);
		void Clear		(bool doDelete);
		int  GetSize	(void) const;

	//private Methods
	private:
		void ClearList	(Node *list, bool doDelete);

	//Members
	private:
		Node *_list;
		int   _size;
};

#include "DxHashTable.inl"

#endif