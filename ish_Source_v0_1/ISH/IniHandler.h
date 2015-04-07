#ifndef _INI_HANDLER_H
#define _INI_HANDLER_H
#include "LibDef.h"
#include <string>

namespace ish
{

class DECLSPEC IniHandler
{
	protected:
		static unsigned int ReadValueA(const char* fileName, const char* category, const char* valueName, int errorValue);
		static unsigned int ReadValueW(const char* fileName, const char* category, const char* valueName, int errorValue);
		static void ReadStringA(const char* fileName, const char* category, const char* valueName, const char* errorValue, unsigned long buffSize, char* output);
		static void ReadStringW(const char* fileName, const char* category, const char* valueName, const char* errorValue, unsigned long buffSize, char* output);
		static bool WriteSectionA(const char* fileName, const char* category, const char* valueName, const char* value);
		static bool WriteSectionW(const char* fileName, const char* category, const char* valueName, const char* value);
		static bool DeleteSectionA(const char* fileName, const char* section);
		static bool DeleteSectionW(const char* fileName, const char* section);

	public:
		IniHandler(void){};
		virtual ~IniHandler(void){};

		inline static unsigned int ReadValue(const char* fileName, const char* category, const char* valueName, int errorValue)
		{
			#ifdef UNICODE
				return ReadValueW( fileName, category, valueName, errorValue );
			#else
				return ReadValueA( fileName, category, valueName, errorValue );
			#endif 
		}

		inline static void ReadString(const char* fileName, const char* category, const char* valueName, const char* errorValue, unsigned long buffSize, char* output)
		{
			#ifdef UNICODE
				return ReadStringA( fileName, category, valueName, errorValue, buffSize, output );
			#else
				return ReadStringW( fileName, category, valueName, errorValue, buffSize, output );
			#endif 
		}

		inline static void ReadString(const char* fileName, const char* category, const char* valueName, const char* errorValue, std::string& output)
		{
			char buff[1024];

			#ifdef UNICODE
				ReadStringA( fileName, category, valueName, errorValue, 1024, buff );
			#else
				ReadStringW( fileName, category, valueName, errorValue, 64, buff );
			#endif 

			output = buff;
		}

		inline static bool DeleteSection(const char* fileName, const char* section)
		{
			#ifdef UNICODE
				return DeleteSectionA( fileName, section );
			#else
				return DeleteSectionW( fileName, section );
			#endif 
		}

		inline static bool WriteSection(const char* fileName, const char* category, const char* valueName, const char* value)
		{
			#ifdef UNICODE
				return WriteSectionA( fileName, category, valueName, value );
			#else
				return WriteSectionW( fileName, category, valueName, value );
			#endif 
		}
};

} // namespace ish

#endif