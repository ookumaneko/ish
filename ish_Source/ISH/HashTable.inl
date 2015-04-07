
template <class KEY, class VALUE> 
HashTable<KEY, VALUE>::HashTable() : _size(0), _list(0)
{
}

template <class KEY, class VALUE> 
HashTable<KEY, VALUE>::~HashTable()
{
	if ( _size > 0 )
	{
		Clear( false );
	}
}

template <class KEY, class VALUE> 
void HashTable<KEY, VALUE>::CopyPointer(HashTable<KEY, VALUE>& src, bool deleteSource)
{
	Clear();
	//_list = src._list;
	//_size = src._size;

	//if ( deleteSource )
	//{
	//	src._list = 0;
	//	src._size = 0;
	//}

	Node *temp = src._list;
	bool found = false;

	//search through the list
	while ( temp != 0 )
	{
		Add( temp->hash.key, temp->hash.value );
		temp = temp->next;
	}
}

template <class KEY, class VALUE> 
void HashTable<KEY, VALUE>::Add(KEY key, VALUE value)
{
	Node *toAdd = new Node;	
	Node *current = this->_list;

	//assign key and value to the new node
	toAdd->hash.key = key;
	toAdd->hash.value = value;
	toAdd->next = 0;

	if ( _list != 0 )
	{
		//search for the end of list
		while ( current->next != 0 )
		{
			current = current->next;
		}

		//connect new node (temp) to the list
		current->next = toAdd;
	}
	else
	{
		_list = toAdd;
		//_list->hash.value = new VALUE;
	}

	_size++;
}

template <class KEY, class VALUE> 
bool HashTable<KEY, VALUE>::TryGetValue(KEY key, VALUE& out)
{
	Node *temp = this->_list;
	bool found = false;

	if ( _list == 0 )
	{
		return false;
	}

	try
	{
		//search through the list
		while ( temp != 0 )
		{
			//if the key matches
			if ( temp->hash.key == key )
			{
				//send the value to the output parameter
				out = temp->hash.value;
				found = true;
				break;
			}

			temp = temp->next;
		}

		if ( !found )
		{
			throw false;
		}
	}
	catch ( bool e )
	{
		return e;
	}

	return found;
}

template <class KEY, class VALUE> 
bool HashTable<KEY, VALUE>::Remove(KEY key)
{
	Node *temp = this->_list;
	Node *toDelete = 0;

	if ( _list->hash.key == key )
	{
		toDelete = _list;
		_list = _list->next;
	}
	else
	{
		//search for a matching key
		while ( temp->next != 0 )
		{
			//if the key was found
			if ( temp->next->hash.key == key )
			{
				//remember which node to delete
				toDelete = temp->next;

				//reconnect the list
				if ( temp->next->next != 0 )
				{
					temp->next = temp->next->next;
				}
				else
				{
					temp->next = 0;
				}

				//delete the select node with the key
				break;
			}

			temp = temp->next;
		}
	}

	if ( toDelete != 0 )
	{
		delete toDelete;
		_size--;
		return true;
	}

	return false;
}

template <class KEY, class VALUE> 
bool HashTable<KEY, VALUE>::Remove(VALUE toRemove)
{
	Node *temp = this->_list;
	Node *toDelete = 0;

	if ( _list->hash.value == toRemove )
	{
		toDelete = _list;
		_list = _list->next;
	}
	else
	{
		//search for a matching key
		while ( temp->next != 0 )
		{
			//if the key was found
			if ( temp->next->hash.value == toRemove )
			{
				//remember which node to delete
				toDelete = temp->next;

				//reconnect the list
				if ( temp->next->next != 0 )
				{
					temp->next = temp->next->next;
				}
				else
				{
					temp->next = 0;
				}

				//delete the select node with the key
				break;
			}

			temp = temp->next;
		}
	}

	if ( toDelete != 0 )
	{
		delete toDelete;
		_size--;
		return true;
	}

	return false;
}

template <class KEY, class VALUE> 
void HashTable<KEY, VALUE>::Clear(bool doDelete)
{
	if ( _size > 0 && _list != 0 )
	{
		ClearList( _list, doDelete );
	}

	_size = 0;
	_list = 0;
}

template <class KEY, class VALUE> 
void HashTable<KEY, VALUE>::ClearList(Node *list, bool doDelete)
{
	if ( list != 0 )
	{
		ClearList( list->next, doDelete );
		if ( doDelete ) 
		{
			//delete list->hash.value;
			//list->hash.value = 0;
		}

		delete list;
		list = 0;
	}
}

template <class KEY, class VALUE> 
int HashTable<KEY, VALUE>::GetSize() const
{
	return _size;
}