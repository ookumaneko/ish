#ifndef _DX_SCENE_NODE
#define _DX_SCENE_NODE

#include <vector>
#include <string>
#include "DxUtil.h"
#include "DxRenderer.h"
#include "DxVector2.h"
#include "DxVector3.h"
#include "DxSprite.h"

class DxMatrix;
class DxShape;
class DxAABB;
//class DxVector3;

class DxSceneNode
{
	//let the scenegraph class see this
	friend class DxScenegraph;
	friend class DxSubGrid;

	//constructor and destructor
	public:
		DxSceneNode(std::string name);
		virtual ~DxSceneNode(void);

	//Accessor
	public:
		const std::string& GetName			(void) const { return _name; }

		const DxMatrix& GetLocalTranform	(void) const;
		const DxMatrix& GetWorldTransform	(void) const;
		
		DxMatrix& GetLocalTranform			(void) { return _localTransform; }
		DxMatrix& GetWorldTransform			(void) { return _worldTransform; }

		const DxVector3& GetTranslation		(void) const { return _translation; }
		const DxMatrix&	 GetRotation		(void) const { return _rotation; }
		const DxVector3& GetScale			(void) const { return _scale; }

		DxShape*		GetLocalBounds		(void)		 { return _localBounds; }
		DxShape*		GetWorldBounds		(void)		 { return _worldBounds; }
		const DxShape*	GetLocalBounds		(void) const { return _localBounds; }
		const DxShape*	GetWorldBounds		(void) const { return _worldBounds; }
		DxAABB*			GetCombinedBounds	(void)		 { return _combinedBounds; }
		const DxAABB*	GetCombinedBounds	(void) const { return _combinedBounds; }

		const float		GetRotationAngle	(void) const { return _rotationAngle; }
		float&			GetRotationAngle	(void)		 { return _rotationAngle; }

		std::vector<DxSceneNode*>& GetChilds(void) { return _children; }

		void SetLocalTransform				(const DxMatrix& local);
		void SetWorldTransform				(const DxMatrix& world);

		void SetTranslation					( const DxVector3& trans )	{ _translation = trans; }
		void SetRotation					( const DxMatrix& rot )		{ _rotation = rot; }
		void SetScal						( const DxVector3& scale)	{ _scale = scale; }
		void SetRotationAngle				( float angle )				{ _rotationAngle = angle; }
		//void SetBounds					( const DxShape* bound )	{ _localBounds = bound; }

		void Pause							(void) { _isActive = false; }
		void Activate						(void) { _isActive = true; }

	// Bounding Volume Methods
	protected:
		virtual bool CreateBoundingShape	(void) { return false; }
		virtual bool DestroyBoundingShape	(void);
		virtual void UpdateBoundingShape	(void);
		bool		 CheckBound				(void);

	//framwork methods
	protected:
		virtual bool	Initialize	(void)	{ return true; }
		virtual void	Update		(float delta);		
		virtual void	Draw		(float delta);		
		virtual bool	Shutdown	(void);

	//Events
	protected:
		virtual void	OnAdded		(void)	{}
		virtual void	OnRemoved	(void)	{}
	
	//SceneGraph Management
	protected:

		//childs management
		bool			AddChild			(DxSceneNode* pChild);
		bool			RemoveChild			(DxSceneNode* pChild);
		void			RemoveAllChildren	(void);

		//parents
		void				SetParent		(DxSceneNode* pParent);
		inline DxSceneNode*	GetParent		(void)	const { return _parentNode; } 

		//Graph searching
		DxSceneNode* FindNode				(std::string name);
		DxSceneNode* FindNode				(DxSceneNode* pNodeToFind);

	// public members
	public:
		static int	_numNodesDrawn;
		bool		_isCulled;

	//protected members
	protected:
		DxMatrix		_localTransform;
		DxMatrix		_worldTransform;
		std::string		_name;
		DxVector3		_translation;
		DxMatrix		_rotation;
		DxVector3		_scale;
		DxShape*		_localBounds;
		DxShape*		_worldBounds;
		DxAABB*			_combinedBounds;
		float			_rotationAngle;
		bool			_isActive;

	private:
		DxSceneNode*				_parentNode;
		std::vector<DxSceneNode*>	_children;
};


#endif