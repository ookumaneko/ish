#ifndef _DX_RESOURCE_MANAGER_
#define _DX_RESOURCE_MANAGER_

#include "DxHashTable.h"

class DxTexture;
class DxFont;
class DxMesh;
class DxWave;

class DxResourceManager
{
	//type enumurator
	public:
		static enum ResourceType
		{
			Texture = 0,
			Font,
			Mesh,
			Wave,
		};

	//framework method
	public:
		static void Initislize	(void);
		static bool Shutdown	(void);

	// Resource Accesors
	public:
		static DxTexture*	GetTexture	(char* key);
		static DxFont*		GetFont		(char* key);
		static DxMesh*		GetMesh		(char* key);
		static DxWave*		GetWave		(char* key, bool copy);

		static bool TryGetTexture	(char* key, DxTexture* &out);
		static bool TryGetFont		(char* key, DxFont* &out);
		static bool TryGetMesh		(char* key, DxMesh* &out);
		static bool TryGetWave		(char* key, bool copy, DxWave* &out);

	//resource loading methods
	public:
		static DxTexture*	LoadTexture	(char* fileName, char* key);
		static DxMesh*		LoadMesh	(char* fileName, char* key, DxTexture* singleTexture = 0);
		static DxFont*		LoadFont	(char* fontName, char* key, int size = 16 );
		static DxWave*		LoadWave	(char* fileName, char* key, bool copy);

		static bool LoadTexture	(char* fileName, char* key, DxTexture* &out);
		static bool LoadMesh	(char* fileName, char* key, DxMesh* &out, DxTexture* singleTexture = 0);
		static bool LoadFont	(int size, char* key, DxFont* &out, char* fontName = "Arial");
		static bool LoadWave	(char* fileName, char* key, bool copy, DxWave* &out);

	// resource management
	public:
		static bool RemoveTexture	(char* key);
		static bool RemoveTexture	(DxTexture* tex);
		static bool RemoveFont		(char* key);
		static bool RemoveFont		(DxFont* font);
		static bool RemoveMesh		(char* key);
		static bool RemoveMesh		(DxMesh* mesh);
		static bool RemoveWave		(char* key);
		static bool RemoveWave		(DxWave* wave);

	// members storing resources
	private:
		static DxHashTable<char*, DxTexture*>*	_textures;
		static DxHashTable<char*, DxMesh*>*		_meshs;
		static DxHashTable<char*, DxFont*>*		_fonts;
		static DxHashTable<char*, DxWave*>*		_waves;
};

#endif