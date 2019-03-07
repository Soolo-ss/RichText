#include "TagParser.h"

namespace RichText
{
	Tag Tag::CreateTag(TagType type, std::string content)
	{
		return Tag{ content, type };
	}
}