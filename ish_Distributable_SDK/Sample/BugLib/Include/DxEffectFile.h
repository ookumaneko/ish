#ifndef _ED_EFFECT_FILE_
#define _ED_EFFECT_FILE_

#include "DxUtil.h"

class DxMatrix;
class DxMaterial;

class DxEffectFile
{
	// enumulators
	public:

		enum MatrixHandles
		{
			WorldMatrix = 0,
			ViewMatrix,
			ProjMatrix,
			
			WorldViewMatrix,
			ViewProjMatrix,
			WorldViewProjMatrix,

			MaxMatrixHandle,
		};
			
		enum ParameterHandles
		{
			BoneInfluenceCount = 0,

			AmbientMaterialColour,
			DiffuseMaterialColour,
			EmissiveMaterialColour,
			ApecularMaterialColour,
			SpecularPower,

			k_PointLightPos0,
			k_PointlightVec0,
			k_PointlightColor0,

			k_sunVector,
			k_sunColor,
			k_cameraPos,
			k_cameraDistances,
			k_cameraFacing,
			k_ambientLight,

			k_patchCorners,
			k_atmosphericLighting,

			k_posScaleOffset,
			k_uvScaleOffset,

			k_lensFlareColor,

			MaxParamHandles,
		};

	public:
		DxEffectFile(char* fileName);
		virtual ~DxEffectFile(void);

	public:
		bool Load			(char* filaName);
		bool Begin			(void);
		bool ActivatePass	(int pass);
		void End			(void);

	public:
		ID3DXEffect* GetEffect		(void) const { return _effect; }
		int			 GetTotalPass	(void) const;


		bool IsParameterUsed	(ParameterHandles handle) const;
		bool IsMatrixUsed		(MatrixHandles handle) const;
		bool SetParameter		(ParameterHandles handle, const void* data, unsigned int size = D3DX_DEFAULT) const;
		bool SetMatrix			(MatrixHandles handle, const DxMatrix& matrix) const;
		bool SetFloat			(ParameterHandles handle, float data) const;
		void SetMaterial		(ParameterHandles handle, const DxMaterial& mtrl);

		bool SetValue			(D3DXHANDLE handle, LPCVOID data, unsigned int size) const;
		bool SetMatrix			(D3DXHANDLE handle, const D3DXMATRIX& data) const;
		bool SetFloat			(D3DXHANDLE handle, float val) const;

	private:
		ID3DXEffect*	_effect;
		D3DXHANDLE		_technique;
		D3DXHANDLE		_paramHandle[MaxParamHandles];
		D3DXHANDLE		_matrixHandle[MaxMatrixHandle];
		//D3DXHANDLE	_textureHandle[];
		//D3DXHANDLE	_textureMatrixHandle[];
		//D3DXHANDLE	_shadowTextureHandle;

};


#endif