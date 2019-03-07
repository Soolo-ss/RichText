#include "TagInfos.h"

#include <cassert>

#include <unordered_map>

namespace RichText
{
	static std::unordered_map<std::string, std::string> ColorName2RGB = {
	{ "WHITE"	, "FFFFFFFF" },//°× 0
	{ "ORANGE"	, "F69D3DFF" },	//³È 1
	{ "YELLO"	, "FCDC04FF" },	//»Æ 2
	{ "BLUE"	, "16E2ABFF" },	//À¶ 3
	{ "SKYBLUE" , "00FFFFFF" },	//ÌìÀ¶ 4 
	{ "DBLUE"	, "24CFFFFF" },	//°µÀ¶ 5
	{ "GREENG"	, "79FF35FF" },	//Çà 6
	{ "DGREENG" , "78DD35FF" },	//°µÇà 7
	{ "BGREENG" , "17E2ABFF" }, //ÑÅÇà 8
	{ "RED"		, "F04140FF" },  //½Ûºì 9
	{ "MAGENTA" , "FC01A6FF"},  //Ñóºì 10
	{ "BROWN"	, "DEC77BFF"},  //×ØÉ« 11
	{ "GOLD"	, "FEE24EFF"}, //½ð 12
	{ "DARKGOLD", "F79D3DFF"}, //½ð 13
	{ "PURPLE"	, "E241D9FF"}, //×Ï 14
	{ "GRAY"	, "626262FF"},   //»Ò 15
	{ "PINK"	, "EF70A0FF"},//·Û 16
	{ "BLACK"	, "000000FF"},			//ºÚÉ« 17
	{ "LIGHTBROWN", "5D2004FF"},		//Ç³×ØÉ« 18
	{ "BROWN2"	, "996B4FFF"}, //19
	{ "GLOD2"	, "FFC731FF"}, //20
	{ "DARKGREY", "434343FF"},	//21
	{ "DARK"	, "A1955BFF"}, //22
	};

	TagInfoPtr TagInfo::CreateTagInfoByTag(Tag& tag)
	{
		TagInfoPtr info = nullptr;

		switch (tag.tagType)
		{
		case TagType::TAG_TYPE_CONTENT:
			info = TagInfoPtr(new TagContentInfo());
			break;
		case TagType::TAG_TYPE_OFFSET:
			info = TagInfoPtr(new TagOffsetInfo());
			break;
		case TagType::TAG_TYPE_IMAGE:
			info = TagInfoPtr(new TagImageInfo());
			break;
		case TagType::TAG_TYPE_IMAGE_INSERT:
			info = TagInfoPtr(new TagInsertImageInfo());
			break;
		case TagType::TAG_TYPE_FACE:
			info = TagInfoPtr(new TagFaceImageInfo());
			break;
		case TagType::TAG_TYPE_POS:
			info = TagInfoPtr(new TagPosInfo());
			break;
		case TagType::TAG_TYPE_LINK:
			info = TagInfoPtr(new TagLinkInfo());
			break;
		case TagType::TAG_TYPE_AUTOCOLOR_BEGIN:
			info = TagInfoPtr(new TagAutoColorInfo());
			break;
		case TagType::TAG_TYPE_COLOR_BEGIN:
			info = TagInfoPtr(new TagColorInfo());
			break;
		case TagType::TAG_TYPE_SELECT_BEGIN:
			info = TagInfoPtr(new TagSelectInfo());
			break;
		default:
			break;
		}

        //copy elision
		return info;
	}

	void TagContentInfo::ParseFromTag(Tag& tag, size_t index, std::string& output)
	{
		output.append(tag.tagStr);
	}

	RichTextInfo TagContentInfo::GetRichTextInfo()
	{
		//RichTextInfo* info = new RichTextInfo();

		//info->type = static_cast<uint8_t>(TagType::TAG_TYPE_CONTENT);
		//info->startPos = startPos;
		//info->content = new char[content.size()];
		//strncpy(info->content, content.c_str(), content.size());

		return RichTextInfo();
	}

	void TagOffsetInfo::ParseFromTag(Tag& tag, size_t index, std::string& output)
	{
		size_t commaPos = tag.tagStr.find_first_of(',');
		size_t colonPos = tag.tagStr.find_first_of(':');
		size_t colonPos2 = tag.tagStr.find_last_of(':');
		size_t bracketPos = tag.tagStr.find_last_of('>');

		assert(commaPos > colonPos);
		assert(bracketPos > colonPos2);

		colonPos++;
		colonPos2++;

		std::string xPos = tag.tagStr.substr(colonPos, commaPos - colonPos);
		std::string yPos = tag.tagStr.substr(colonPos2, bracketPos - colonPos2);

		x = std::stoi(xPos);
		y = std::stoi(yPos);

		return;
	}

	RichTextInfo TagOffsetInfo::GetRichTextInfo()
	{
		RichTextInfo info;

		info.type = static_cast<uint8_t>(TagType::TAG_TYPE_OFFSET);
		info.startPos = static_cast<uint32_t>(startPos);
		info.x = x;
		info.y = y;

		return info;
	}

	void TagImageInfo::ParseFromTag(Tag& tag, size_t index, std::string& output)
	{
		size_t imageEndPos = tag.tagStr.find("#IMAGE") + strlen("#IMAGE");

		image = tag.tagStr.substr(imageEndPos, tag.tagStr.size() - imageEndPos - 1);

		output.append("<quad ");
		output.append(image);
		output.append("/>");
	}

	RichTextInfo TagImageInfo::GetRichTextInfo()
	{
		RichTextInfo info;

		info.type = static_cast<uint8_t>(TagType::TAG_TYPE_IMAGE);
		info.startPos = static_cast<uint32_t>(startPos);
		//info.content = new char[image.size()];
		strncpy(info.content, image.c_str(), image.size());

		return info;
	}

	void TagInsertImageInfo::ParseFromTag(Tag& tag, size_t index, std::string& output)
	{
		size_t imageEndPos = tag.tagStr.find("#IMAGE<ID:") + strlen("#IMAGE<ID:");

		image = tag.tagStr.substr(imageEndPos, tag.tagStr.size() - imageEndPos - 2);

		output.append("<quad ");
		output.append(image);
		output.append("/>");
	}

	RichTextInfo TagInsertImageInfo::GetRichTextInfo()
	{
		RichTextInfo info;

		info.type = static_cast<uint8_t>(TagType::TAG_TYPE_IMAGE);
		info.startPos = static_cast<uint32_t>(startPos);
		//info.content = new char[image.size()];
		strncpy(info.content, image.c_str(), image.size());

		return info;
	}

	void TagFaceImageInfo::ParseFromTag(Tag& tag, size_t index, std::string& output)
	{
		size_t commaPos = tag.tagStr.find_first_of(',');
		size_t colonPos = tag.tagStr.find_first_of(':');
		size_t colonPos2 = tag.tagStr.find_last_of(':');
		size_t bracketPos = tag.tagStr.find_last_of('>');

		assert(commaPos > colonPos);
		assert(bracketPos > colonPos2);

		colonPos++;
		colonPos2++;

		std::string xPos = tag.tagStr.substr(colonPos, commaPos - colonPos);
		std::string yPos = tag.tagStr.substr(colonPos2, bracketPos - colonPos2);

		image.append(xPos);
		image.append(",");
		image.append(yPos);

		output.append("<quad ");
		output.append(image);
		output.append("/>");
	}

	RichTextInfo TagFaceImageInfo::GetRichTextInfo()
	{
		RichTextInfo info;

		info.type = static_cast<uint8_t>(TagType::TAG_TYPE_IMAGE);
		info.startPos = static_cast<uint32_t>(startPos);
		//info.content = new char[image.size()];
		strncpy(info.content, image.c_str(), image.size());

		return info;
	}

	void TagPosInfo::ParseFromTag(Tag& tag, size_t index, std::string& output)
	{
		size_t commaPos = tag.tagStr.find_first_of(',');
		size_t colonPos = tag.tagStr.find_first_of(':');
		size_t colonPos2 = tag.tagStr.find_last_of(':');
		size_t bracketPos = tag.tagStr.find_last_of('>');

		std::string xPos = tag.tagStr.substr(colonPos, commaPos);
		std::string yPos = tag.tagStr.substr(colonPos2, bracketPos);

		x = std::stoi(xPos);
		y = std::stoi(yPos);
	}

	RichTextInfo TagPosInfo::GetRichTextInfo()
	{
		RichTextInfo info;

		info.type = static_cast<uint8_t>(TagType::TAG_TYPE_POS);
		info.startPos = static_cast<uint32_t>(startPos);
		info.x = x;
		info.y = y;

		return info;
	}

	void TagLinkInfo::ParseFromTag(Tag& tag, size_t index, std::string& output)
	{
		startPos = output.size();

		output.append("<color='#");
		output.append("19C800");		//link color
		output.append("'>");

		size_t STRStartPos = tag.tagStr.find("STR:") + strlen("STR:");
		size_t STREndPos = 0;
		for (size_t i = STRStartPos; i != tag.tagStr.size(); ++i)
		{
			if (tag.tagStr[i] == ',' || tag.tagStr[i] == '>')
			{
				STREndPos = i;
				break;
			}
		}

		std::string STRName = tag.tagStr.substr(STRStartPos, STREndPos - STRStartPos);

		output.append(STRName);

		output.append("</color>");

		size_t linkContentPos = tag.tagStr.find('<') + 1;
		size_t linkContentEndPos = tag.tagStr.find_last_of('>');

		content = tag.tagStr.substr(linkContentPos, linkContentEndPos - linkContentPos);
	}

	RichTextInfo TagLinkInfo::GetRichTextInfo()
	{
		RichTextInfo info;

		info.type = static_cast<uint8_t>(TagType::TAG_TYPE_LINK);
		info.startPos = static_cast<uint32_t>(startPos);
		//info.content = new char[content.size()];
		strncpy(info.content, content.c_str(), content.size());

		return info;
	}

	void TagSelectInfo::ParseFromTag(Tag& tag, size_t index, std::string& output)
	{

	}

	void TagSelectInfo::ParseFromEndTag(Tag& tag, size_t index, std::string& output)
	{
		endPos = output.size();
	}

	RichTextInfo TagSelectInfo::GetRichTextInfo()
	{
		RichTextInfo info;

		info.type = static_cast<uint8_t>(TagType::TAG_TYPE_SELECT_BEGIN);
		info.startPos = static_cast<uint32_t>(startPos);
		info.endPos = static_cast<uint32_t>(endPos);

		return info;
	}

	void TagColorInfo::ParseFromTag(Tag& tag, size_t index, std::string& output)
	{
		output.append("<color='#");

		size_t colorBeginPos = tag.tagStr.find('_') + 1;
		size_t colorEndPos = tag.tagStr.find_last_of('#');
		
		color = tag.tagStr.substr(colorBeginPos, colorEndPos - colorBeginPos);

		std::string colorCode = ColorName2RGB.at(color);

		output.append(colorCode);
		output.append("'>");
	}

	void TagColorInfo::ParseFromEndTag(Tag& tag, size_t index, std::string& output)
	{
		output.append("</color>");
		endPos = output.size();
	}

	RichTextInfo TagColorInfo::GetRichTextInfo()
	{
		RichTextInfo info;

		info.type = static_cast<uint8_t>(TagType::TAG_TYPE_COLOR_BEGIN);
		info.startPos = static_cast<uint32_t>(startPos);
		//info.content = new char[color.size()];
		strncpy(info.content, color.c_str(), color.size());

		return info;
	}

	void TagAutoColorInfo::ParseFromTag(Tag& tag, size_t index, std::string& output)
	{
		endPos = output.size();
	}
}
