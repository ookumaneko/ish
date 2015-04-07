#pragma once

class DxQuadNode;
class DxSceneNode;

class DxQuadObject
{
	// constructor and destructor
	private:
		DxQuadObject() {}
		
	public:
		DxQuadObject(int id, DxSceneNode* object, bool canCollide);
		virtual ~DxQuadObject(void) {}

	// member methods
	public:
		bool RemoveFromTree(void);

	// members
	public:
		DxQuadNode*			 _node;		// the node this object belongs to in tree
		DxSceneNode*		 _object;	// the object
		DxQuadObject*	 _next;		// pointer to the next object
		DxQuadObject*	 _previous; // pointer to the previous ojbect
		int					 _id;
		bool				 _canCollide;
};