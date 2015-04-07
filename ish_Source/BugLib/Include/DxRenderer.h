#ifndef DXRENDERER_H
#define DXRENDERER_H

#include "DxUtil.h"
#include "DxScenegraph.h"
#include "DxMatrix.h"
#include "DxColour.h"
#include "DxViewFrustum.h"
#include "DxLightMaterial.h"

class DxGame;
class DxTexture;
class DxMaterial;

class DxRenderer : public DxScenegraph
{
	// constructor and destructor
	private:
		DxRenderer			(void);

	public:
		virtual ~DxRenderer	(void);

	//Framework methods
	public:
		virtual void Initialize		(HWND hWnd, D3DDEVTYPE devType, DWORD requestedVP, bool useShader);
		virtual void Update			(float delta);
		virtual void Draw			(float delta);
		virtual void ShutDown		(void);
		virtual void ResetDevice	(void);
		virtual bool IsDeviceLost	(void);
		virtual bool CheckDeviceCaps(int version);

	// Accessors
	public:

		// Accessors to the devices and renderer
		static DxRenderer*			GetInstance			(void);
		static IDirect3DDevice9*	GetDevice			(void);
		D3DPRESENT_PARAMETERS&		GetPP				(void);

		// resolution
		int GetWidth	(void) const;
		int GetHeight	(void) const;

		// view and projection
		const DxMatrix&		GetViewMatrix		(void) const;
		const DxMatrix&		GetProjectionMatrix	(void) const;

		void SetViewMatrix			(const DxMatrix& view); 			
		void SetProjectionMatrix	(const DxMatrix& projection);

		// view frustum
		void SetFrustum				(const DxViewFrustum& frustum);
		
		const DxViewFrustum& GetViewFrustum(void) const { return _frustum; }
		DxViewFrustum&		 GetViewFrustum(void)		{ return _frustum; }
	
		// bounding volume debug
		static float GetIsDrawShapes(void)			{ return _isDrawBoundingShapes; }
		static void  SetIsDrawShapes(bool enable)	{ _isDrawBoundingShapes = enable; }
		static void  ToggleIsDrawShape(void)		{ _isDrawBoundingShapes = !_isDrawBoundingShapes; }

		bool GetShaderEnabled	(void) const	{ return _shaderEnabled; }
		void EnableShader		(bool enable)	{ _shaderEnabled = enable; }

	//general methods
	public:
		void ToggleFullScreen		(void);
		void SetBackBufferSize		(int width, int height);
		void ResetBackBufferSize	(void);
		void Clear					(unsigned int colour);
		void Clear					(DxColour& colour);	

	// Render states
	public:

		static enum FillModes
		{
			FILL_POINT = 1,
			WIREFRAME,
			SOLID,
		};

		static enum CullingModes
		{
			CULL_NONE = 1,
			CLOCK,
			COUNTER_CLOCK,
		};

		static enum PrimitiveType
		{
			POINT_LIST = 1,
			TRIANGLE_LIST = 4,
			TRIANGLE_STRIP,
		};

	// render state Methods
	public:
		void EnableZBuffer			(bool enable);
		void EnableLighting			(bool enable);
		void EnableAlphaBlend		(bool enable);
		void SetFillMode			(unsigned int mode);
		void SetCullingMode			(unsigned int mode);

		void EnableLight			(DWORD index, bool enable)		{ _gd3dDevice->LightEnable( index, enable ); }
		void SetLight				(DWORD index, DxLight& light)	{ _gd3dDevice->SetLight( index, &light.GetLight() ); }

		// point sprite
		void EnablePointSprite	(void);
		void DisablePointSprite	(void);
		void SetPointSprite		(bool enablePointSprite, bool enableScale, float pointSize, float minSize, 
								 float maxSize, float scaleA = 0, float scaleB = 0, float scaleC = 1 );
		
		//transforms
		void SetWorldTransform		(const DxMatrix& transform);
		
	// Graphics Device Methods
	public:
		void SetTexture(DWORD stage, const DxTexture& texture);
		void SetTexture(DWORD stage, const DxTexture* texture);

		void SetMaterial(const D3DMATERIAL9& mat);
		void SetMaterial(const D3DMATERIAL9* mat);
		void SetMaterial(const DxMaterial& mat);
		void SetMaterial(const DxMaterial* mat);

		void SetIndices				(LPDIRECT3DINDEXBUFFER9 indexBuffer);
		void SetFVF					(DWORD fvf);
		void SetVertexDeclaration	(IDirect3DVertexDeclaration9* decl);
		void SetStreamSource		(unsigned int streamNumber, LPDIRECT3DVERTEXBUFFER9 pData, unsigned int offSet, unsigned int stride);

		HRESULT DrawPrimitive(unsigned int primitiveType, unsigned int startIndex, unsigned int numPrimitives);
		HRESULT DrawIndexedPrimitive(unsigned int primitiveType, int baseIndex, 
									 unsigned int minIndex, unsigned int numVertices, 
									 unsigned int startIndex, unsigned int numPrimitives);
	

	//Render Methods
	public:
		bool Begin		(void);
		void End		(void);
		void SwitchBuffer(void);

	//members
	protected:
		static IDirect3DDevice9*	_gd3dDevice;
		static IDirect3D9*			_d3dObject;
		static DWORD				_requestedVP;
		static bool					_isDrawBoundingShapes;
		DxMatrix					_viewMatrix;
		DxMatrix					_projectionMatrix;
		DxViewFrustum				_frustum;

		D3DDEVTYPE					_devType;
		D3DPRESENT_PARAMETERS		_d3dPP;
		HWND						_hWnd;
		int							_width;
		int							_height;
		bool						_zbufferEnabled;
		bool						_isDrawing;
		bool						_isActive;
		bool						_shaderEnabled;

	private:
		static DxRenderer*			_instance;
};

#endif