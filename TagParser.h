#pragma once

#include "Tag.h"

#include <vector>
#include <unordered_map>

namespace RichText
{
	
	

	class TagParser
	{
	public:
		TagParser();
		~TagParser();

		enum class TagParseStatus
		{
			TAG_STATUS_OPEN,
			TAG_STATUS_CLOSE
		};

		std::vector<Tag> ParseTags(std::string& target);
		
		void Clear();
	
	private:
		Tag ParseTag();

		std::pair<bool, TagType> CheckIsKeyword(size_t index);

	private:
		std::string target_;
		size_t index_;
	};
}


