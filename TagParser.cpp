#include "TagParser.h"

#include <unordered_map>

namespace RichText
{
	static std::vector<std::pair<std::string, TagType>> keyword2type = { 
		{"#OFFSET<", TagType::TAG_TYPE_OFFSET},
		{"#IMAGE<ID:", TagType::TAG_TYPE_IMAGE_INSERT},
		{"#IMAGE", TagType::TAG_TYPE_IMAGE },
		{"#COLORCOLOR_", TagType::TAG_TYPE_COLOR_BEGIN},
		{"#COLOREND", TagType::TAG_TYPE_COLOR_END},
		{"#SELECTEND#", TagType::TAG_TYPE_SELECT_END},
		{"#SELECT", TagType::TAG_TYPE_SELECT_BEGIN},
		{"#AUTOCOLOR", TagType::TAG_TYPE_AUTOCOLOR_BEGIN},
		{"#AUTOCOLOREND#", TagType::TAG_TYPE_AUTOCOLOR_END},
		{"#POS<", TagType::TAG_TYPE_POS},
		{"#LINK<", TagType::TAG_TYPE_LINK},
		{"#NPCLINK<", TagType::TAG_TYPE_LINK},
		{"#ITEMLINK<", TagType::TAG_TYPE_LINK},
		{"#NAMELINK<", TagType::TAG_TYPE_LINK},
		{"#UILINK<", TagType::TAG_TYPE_LINK},
		{"#FACE<", TagType::TAG_TYPE_FACE},
	};
		
	TagParser::TagParser()
	{
	}

	TagParser::~TagParser()
	{
	}

	std::pair<bool, TagType> TagParser::CheckIsKeyword(size_t index)
	{
		if (target_[index] != '#')
			return std::make_pair(false, TagType::TAG_TYPE_CONTENT);

		size_t pos = 0;
		for (auto keyword : keyword2type)
		{
			pos = target_.find(keyword.first, index);
			if (pos == std::string::npos || pos != index)
				continue;
			else
				return std::make_pair(true, keyword.second);
		}

		return std::make_pair(false, TagType::TAG_TYPE_CONTENT);
	}

	Tag TagParser::ParseTag()
	{
		size_t targetSize = target_.size();

		if (index_ >= targetSize)
			return Tag{ "", TagType::TAG_TYPE_NONE };

		size_t begin = index_;
		size_t end = 0;
		TagType type{ TagType::TAG_TYPE_CONTENT };

		auto checkRes = CheckIsKeyword(index_);

		index_++;

		while (index_ < targetSize)
		{
			if (target_[index_] == '#')
			{
				//keyword
				if (checkRes.first == true)
				{
					index_++;
					end = index_;
					break;
				}
				else
				{
					end = index_;
					break;
				}
			}

			index_++;
		}
		
		type = checkRes.second;

		return Tag::CreateTag(type, target_.substr(begin, end - begin));
	}

	std::vector<Tag> TagParser::ParseTags(std::string& target)
	{
		target_ = target;
		index_ = 0;

		std::vector<Tag> result;

		size_t targetSize = target_.size();

		std::string content;

		while (true)
		{
			Tag tag = ParseTag();
			if (tag.tagType != TagType::TAG_TYPE_NONE)
				result.push_back(tag);
			
			if (index_ >= targetSize)
				break;
		}

		return result;
	}

	void TagParser::Clear()
	{
		target_.clear();
		index_ = 0;
	}
}


