#include "RichTextParser.h"

namespace RichText
{
	void RichTextParser::Parse(std::string target)
	{
		target_ = target;
		targetSize_ = target.size();
		//tags_ = TagParser::ParseTags();
		tags_ = tagParser_.ParseTags(target);

		ParseRichText();
	}

	void RichTextParser::Clear()
	{
		target_.clear();
		targetSize_ = 0;
		tags_.clear();
		index_ = 0;
		tagIndex_ = 0;
		tagInfos_.clear();
		output_.clear();

		tagParser_.Clear();
	}

	void RichTextParser::ParseRichText()
	{
		std::string richText = target_.substr(index_, targetSize_ - index_);

		//std::string output;

		//for (; tagIndex_ != tags_.size(); ++tagIndex_)
		//{
		while(tagIndex_ < tags_.size())
		{ 
			Tag tag = tags_[tagIndex_];

			switch (tag.tagType)
			{
			case TagType::TAG_TYPE_CONTENT:
			case TagType::TAG_TYPE_OFFSET:
			case TagType::TAG_TYPE_IMAGE:
			case TagType::TAG_TYPE_IMAGE_INSERT:
			case TagType::TAG_TYPE_POS:
			case TagType::TAG_TYPE_LINK:
			case TagType::TAG_TYPE_FACE:
			{
				//û��Ƕ�׵�����
				TagInfoSharedPtr info = TagInfo::CreateTagInfoByTag(tag);
				if (info)
				{
					info->SetStartPos(output_.size());
					info->ParseFromTag(tag, index_, output_);
					tagInfos_.push_back(info);
				}

				index_ += tag.tagStr.size();
				++tagIndex_;
				break;
			}
			case TagType::TAG_TYPE_AUTOCOLOR_BEGIN:
			case TagType::TAG_TYPE_COLOR_BEGIN:
			case TagType::TAG_TYPE_SELECT_BEGIN:
			{
				//Ƕ�׵�����
				TagInfoSharedPtr info = TagInfo::CreateTagInfoByTag(tag);

				if (info)
				{
					info->SetStartPos(output_.size());
					info->ParseFromTag(tag, index_, output_);
					tagInfos_.push_back(info);
					tagInfoStack_.push(info);
				}

				index_ += tag.tagStr.size();
				++tagIndex_;

				//ParseRichText();

				break;
			}
			case TagType::TAG_TYPE_AUTOCOLOR_END:
			case TagType::TAG_TYPE_COLOR_END:
			case TagType::TAG_TYPE_SELECT_END:
			{
				TagInfoSharedPtr beginInfo = tagInfoStack_.top();
				tagInfoStack_.pop();

				beginInfo->ParseFromEndTag(tag, index_, output_);

				index_ += tag.tagStr.size();
				++tagIndex_;

				break;
			}
			default:
				//���һ��warnning��Ϣ
				++tagIndex_;
				break;
			}
		}

		//û�ж�Ӧ��������Tag
		while (!tagInfoStack_.empty())
		{
			TagInfoSharedPtr beginInfo = tagInfoStack_.top();
			tagInfoStack_.pop();

			//beginInfo->ParseFromEndTag()
			//parse but no tag
			//������tags[0] ʵ�����ò���
			beginInfo->ParseFromEndTag(tags_[0], 0, output_);
		}
	}
}