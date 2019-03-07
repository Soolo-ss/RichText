#pragma once

#include "Tag.h"
#include "TagInfos.h"
#include "TagParser.h"
#include "RichTextInfo.h"

#include <string>
#include <vector>
#include <stack>

namespace RichText
{
	class RichTextParser
	{
	public:
		RichTextParser()
			: target_(),
			  targetSize_(0),
			  index_(0),
			  tagIndex_(0)
		{  }

		void Parse(std::string target);

		const std::string& GetOutput() const
		{
			return output_;
		}

		std::vector<TagInfoSharedPtr> GetTagInfos() const
		{
			return tagInfos_;
		}

		void Clear();
	private:
		void ParseRichText();

	private:
		std::string target_;
		size_t targetSize_;
		size_t index_;
		size_t tagIndex_;

		std::vector<Tag> tags_;
		std::vector<TagInfoSharedPtr> tagInfos_;
		std::stack<TagInfoSharedPtr> tagInfoStack_;
		std::string output_;

		TagParser tagParser_;
	};
}
