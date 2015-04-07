/* Hash Table Class */
/* This is using .inl because hashtable uses 
   Templates. 
*/
//---------------------------------------------------------------//
//-------------------Constructor and Destructor------------------//
//---------------------------------------------------------------//


template <class T, class V> 
DxHashTable<T, V>::DxHashTable() : _size(0), _list(0)
{

}

template <class T, class V> 
DxHashTable<T, V>::~DxHashTable()
{
	if ( _size > 0 )
		Clear( false );
}


template <class T, class V> 
V DxHashTable<T, V>::operator[](T key)
{
	return GetValue( key );
}

//---------------------------------------------------------------//
//--------------------------Member Methods-----------------------//
//---------------------------------------------------------------//


template <class T, class V> 
void DxHashTable<T, V>::Add(T key, V value)
{
	Node *toAdd = new Node;	//new node
	Node *current = this->_list;

	//assign key and value to the new node
	toAdd->hash.key = key;
	toAdd->hash.value = value;
	toAdd->next = 0;

	if (_list != 0)
	{
		//search for the end of list
		while (current->next != 0)
		{
			current = current->next;
		}

		//connect new node (temp) to the list
		current->next = toAdd;
	}
	else
	{
		_list = toAdd;
		//_list->hash.value = new V;
	}

	_size++;
}

template <class T, class V> 
V DxHashTable<T, V>::GetValue(T key)
{
	Node *temp = _list;
	bool found = false;
	V out = 0;

	if (_list == 0) return 0;

	try
	{
		//search through the list
		while (temp != 0)
		{
			//if the key matches
			if (temp->hash.key == key)
			{
				//send the value to the output parameter
				out = temp->hash.value;
				found = true;
			}

			temp = temp->next;
		}

		if (!found) throw false;
	}
	catch (bool e)
	{
		return 0;
	}

	return out;
}

template <class T, class V> 
bool DxHashTable<T, V>::TryGetValue(T key, V out)
{
	Node *temp = this->_list;
	bool found = false;

	if (_list == 0) return false;

	try
	{
		//search through the list
		while (temp != 0)
		{
			//if the key matches
			if (temp->hash.key == key)
			{
				//send the value to the output parameter
				out = temp->hash.value;
				found = true;
			}

			temp = temp->next;
		}

		if (!found) throw false;
	}
	catch (bool e)
	{
		return e;
	}

	return found;
}

template <class T, class V> 
bool DxHashTable<T, V>::Remove(T key)
{
	Node *temp = this->_list;
	Node *toDelete = 0;

	if (_list->hash.key == key)
	{
		toDelete = _list;
		_list = _list->next;
	}
	else
	{
		//search for a matching key
		while (temp->next != 0)
		{
			//if the key was found
			if (temp->next->hash.key == key)
			{
				//remember which node to delete
				toDelete = temp->next;

				//reconnect the list
				if (temp->next->next != 0)
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

	if (toDelete != 0)
	{
		delete toDelete;
		_size--;
		return true;
	}

	return false;
}

template <class T, class V> 
bool DxHashTable<T, V>::Remove(V toRemove)
{
	Node *temp = this->_list;
	Node *toDelete = 0;

	if (_list->hash.value == toRemove)
	{
		toDelete = _list;
		_list = _list->next;
	}
	else
	{
		//search for a matching key
		while (temp->next != 0)
		{
			//if the key was found
			if (temp->next->hash.value == toRemove)
			{
				//remember which node to delete
				toDelete = temp->next;

				//reconnect the list
				if (temp->next->next != 0)
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

	if (toDelete != 0)
	{
		delete toDelete;
		_size--;
		return true;
	}

	return false;
}

template <class T, class V> 
void DxHashTable<T, V>::Clear(bool doDelete)
{
	if ( _size > 0 && _list != 0 )
	{
		ClearList( _list, doDelete );
	}

	_size = 0;
	_list = 0;
}

template <class T, class V> 
void DxHashTable<T, V>::ClearList(Node *list, bool doDelete)
{
	if ( list != 0 )
	{
		ClearList( list->next, doDelete );
		if ( doDelete ) 
		{
			delete list->hash.value;
			list->hash.value = 0;
		}

		delete list;
	}
}

template <class T, class V> 
int DxHashTable<T, V>::GetSize() const
{
	return _size;
}