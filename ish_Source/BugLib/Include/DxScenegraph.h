#ifndef _DX_SCENE_GRAPH
#define _DX_SCENE_GRAPH

#include "DxLibraryDef.h"
#include <string>

class DxSceneNode;

class DxScenegraph
{
	//constructor and destructor
	public:
		DxScenegraph(void);
		virtual ~DxScenegraph(void);

	//Framework methods
	public:
		virtual bool Initialise	(void);
		virtual void Update		(float delta);
		virtual void Draw		(float delta);
		virtual bool Shutdown	(void);

	// SceneNode methods
	public:

		//Graph heirarchy changes
		bool		AddNode		(DxSceneNode* pNode, std::string parentNode);
		bool		RemoveNode	(DxSceneNode* pNodeToRemove);
	
	protected:

		// Heirarchy events
		void		OnNodeAdded		(DxSceneNode* pNode);
		void		OnNodeRemoved	(DxSceneNode* pNode);

	public:
		//Graph searching
		DxSceneNode* FindNode		(std::string name);
		DxSceneNode* FindNode		(DxSceneNode* pNodeToFind);

	//members
	private:

		// The scene root node
		DxSceneNode*		_rootNode;	

};

#endif