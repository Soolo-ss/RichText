#pragma once

#include <stdint.h>

#define MAX_RICH_TEXT_CONTENT_SIZE 256

namespace RichText
{
	class RichTextInfo
	{
	public:
		RichTextInfo()
			: type(0), startPos(0), endPos(0),
			  x(0), y(0), size(0)
		{ 
			memset(content, 0, MAX_RICH_TEXT_CONTENT_SIZE);
		}

		~RichTextInfo() 
		{
		}

		uint8_t type = 0;
		uint32_t startPos = 0;
		uint32_t endPos = 0;
		int32_t x = 0;
		int32_t y = 0;
		uint8_t size;
		char content[MAX_RICH_TEXT_CONTENT_SIZE];
	};
}
