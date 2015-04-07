#pragma once
#include "DxShape.h"
#include <windows.h>
class DxQuadObject;

class DxQuadNode
{
	public:
		DxQuadNode(void) : _latest( 0 ), _level( 0 ), _index(0), _numObjects(0) {}
		
		DxQuadNode(DWORD level, DWORD index)
		{
			_level = level;
			_index = index;
			_latest = 0;
			_numObjects = 0;
			//_bounds = DxAABB( 
		}

		virtual ~DxQuadNode(void)
		{
			if ( _latest != NULL )
			{
				ResetLink( _latest );
			}
		}

	public:

		void ResetLink	(DxQuadObject* obj);
		bool Push		(DxQuadObject* obj);
		bool OnRemoved	(DxQuadObject* toRemove);

		DxQuadObject* GetFirstObject() { return _latest; }		

	public:
		DxAABB				_bounds;
		DWORD				_level;
		DWORD				_index;
		DxQuadObject*		_latest;
		DxQuadNode*			_parent;
		int					_numObjects;
};
