#include "IniHandler.h"
#include <windows.h>
using namespace ish;

unsigned int IniHandler::ReadValueA(const char* fileName, const char* category, const char* valueName, int errorValue)
{
	return GetPrivateProfileIntA( category, valueName, errorValue, fileName );
}

unsigned int IniHandler::ReadValueW(const char* fileName, const char* category, const char* valueName, int errorValue)
{
	WCHAR name[32], categoryName[32], file[MAX_PATH];
	MultiByteToWideChar( CP_ACP, 0, valueName, -1, name, 32 );
	MultiByteToWideChar( CP_ACP, 0, category, -1, categoryName, 32 );
	MultiByteToWideChar( CP_ACP, 0, fileName, -1, file, MAX_PATH );

	return GetPrivateProfileIntW( categoryName, name, errorValue, file );
}

void IniHandler::ReadStringA(const char* fileName, const char* category, const char* valueName, const char* errorValue, DWORD buffSize, char* output)
{
	GetPrivateProfileStringA( category, valueName, errorValue, output, buffSize, fileName );
}

void IniHandler::ReadStringW(const char* fileName, const char* category, const char* valueName, const char* errorValue, DWORD buffSize, char* output)
{
	WCHAR name[32], categoryName[32], file[MAX_PATH], error[32], out[ 64 ];
	MultiByteToWideChar( CP_ACP, 0, valueName, -1, name, 32 );
	MultiByteToWideChar( CP_ACP, 0, category, -1, categoryName, 32 );
	MultiByteToWideChar( CP_ACP, 0, fileName, -1, file, MAX_PATH );
	MultiByteToWideChar( CP_ACP, 0, errorValue, -1, error, 32 );
	MultiByteToWideChar( CP_ACP, 0, output, -1, out, 64 );

	GetPrivateProfileStringW( categoryName, name, error, out, buffSize, file );
	WideCharToMultiByte( CP_THREAD_ACP, 0, out, -1, output, strlen(output), NULL, NULL );
}

inline bool IniHandler::DeleteSectionA(const char *fileName, const char *section)
{
	return WritePrivateProfileSectionA( section, 0, fileName );
}

bool IniHandler::DeleteSectionW(const char *fileName, const char *section)
{
	WCHAR name[MAX_PATH], sectionName[32];
	MultiByteToWideChar( CP_ACP, 0, fileName, -1, name, 32 );
	MultiByteToWideChar( CP_ACP, 0, section, -1, sectionName, 32 );

	return WritePrivateProfileSectionW( sectionName, 0, name );
}

inline bool IniHandler::WriteSectionA(const char* fileName, const char* category, const char* valueName, const char* value)
{
	return WritePrivateProfileStringA( category, valueName, value, fileName );
}

bool IniHandler::WriteSectionW(const char* fileName, const char* category, const char* valueName, const char* value)
{
	WCHAR name[32], categoryName[32], file[MAX_PATH], v[ 64 ];
	MultiByteToWideChar( CP_ACP, 0, valueName, -1, name, 32 );
	MultiByteToWideChar( CP_ACP, 0, category, -1, categoryName, 32 );
	MultiByteToWideChar( CP_ACP, 0, fileName, -1, file, MAX_PATH );
	MultiByteToWideChar( CP_ACP, 0, value, -1, v, 64 );
	return WritePrivateProfileStringW( categoryName, name, v, file );
}
