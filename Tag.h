#pragma once

#include <string>

namespace RichText
{
	enum class TagType
	{
		TAG_TYPE_NONE = 0,
		TAG_TYPE_OFFSET,
		TAG_TYPE_IMAGE,
		TAG_TYPE_COLOR_BEGIN,
		TAG_TYPE_COLOR_END,
		TAG_TYPE_SELECT_BEGIN,
		TAG_TYPE_SELECT_END,
		TAG_TYPE_AUTOCOLOR_BEGIN,
		TAG_TYPE_AUTOCOLOR_END,
		TAG_TYPE_IMAGE_INSERT,
		TAG_TYPE_POS,
		TAG_TYPE_LINK,				//多种LINK可以用统一种处理
		TAG_TYPE_CLOSE,
		TAG_TYPE_FONT_DISTANCE,
		TAG_TYPE_FACE,
		TAG_TYPE_DELLINE,
		TAG_TYPE_CONTENT,
	};

	class Tag
	{
	public:
		Tag() {}

		Tag(std::string str, TagType type)
			: tagStr(str), tagType(type)
		{  }

		std::string tagStr;
		TagType tagType;

		static Tag CreateTagByTagStr(std::string& tagStr);
		static Tag CreateTag(TagType type, std::string content);
	};
}
