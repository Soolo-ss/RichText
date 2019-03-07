#pragma once

#include "Tag.h"
#include "RichTextInfo.h"

#include <string>
#include <memory>

namespace RichText
{
	class TagInfo;

	using TagInfoPtr = std::unique_ptr<TagInfo>;
	using TagInfoSharedPtr = std::shared_ptr<TagInfo>;

	class TagInfo
	{
	public:
		virtual ~TagInfo() { }

		virtual void ParseFromTag(Tag& tag, size_t index, std::string& output) = 0;

		virtual void ParseFromEndTag(Tag& tag, size_t index, std::string& output) {}

		virtual RichTextInfo GetRichTextInfo() { return RichTextInfo(); };

		static TagInfoPtr CreateTagInfoByTag(Tag& tag);

		void SetStartPos(size_t pos)
		{
			startPos = pos;
		}

	protected:
		size_t startPos = 0;
	};

	class TagContentInfo : public TagInfo
	{
	public:
		void ParseFromTag(Tag& tag, size_t index, std::string& output) override;

		RichTextInfo GetRichTextInfo() override;
	private:
		std::string content;
	};

	class TagAutoColorInfo : public TagInfo
	{
	public:
		void ParseFromTag(Tag& tag, size_t index, std::string& output) override;
	private:
		size_t endPos = 0;
		std::string color;
	};

	class TagColorInfo : public TagInfo
	{
	public:
		void ParseFromTag(Tag& tag, size_t index, std::string& output) override;

		void ParseFromEndTag(Tag& tag, size_t index, std::string& output) override;

		RichTextInfo GetRichTextInfo() override;
	private:
		std::string color;
		size_t endPos;
	};

	class TagOffsetInfo : public TagInfo
	{
	public:
		void ParseFromTag(Tag& tag, size_t index, std::string& output) override;

		RichTextInfo GetRichTextInfo() override;
	private:
		int x = 0;
		int y = 0;
	};

	class TagLinkInfo : public TagInfo
	{
	public:
		void ParseFromTag(Tag& tag, size_t index, std::string& output) override;

		RichTextInfo GetRichTextInfo() override;

	private:
		std::string content;
	};

	class TagImageInfo : public TagInfo
	{
	public:
		void ParseFromTag(Tag& tag, size_t index, std::string& output) override;

		RichTextInfo GetRichTextInfo() override;
	private:
		std::string image;
	};

	class TagInsertImageInfo : public TagInfo
	{
	public:
		void ParseFromTag(Tag& tag, size_t index, std::string& output) override;

		RichTextInfo GetRichTextInfo() override;
	private:
		std::string image;
	};

	class TagFaceImageInfo : public TagInfo
	{
	public:
		void ParseFromTag(Tag& tag, size_t index, std::string& output) override;

		RichTextInfo GetRichTextInfo() override;
	private:
		std::string image;
	};

	class TagPosInfo : public TagInfo
	{
	public:
		void ParseFromTag(Tag& tag, size_t index, std::string& output) override;

		RichTextInfo GetRichTextInfo() override;
	private:
		int x = 0;
		int y = 0;
	};

	class TagSelectInfo : public TagInfo
	{
	public:
		void ParseFromTag(Tag& tag, size_t index, std::string& output) override;

		void ParseFromEndTag(Tag& tag, size_t index, std::string& output) override;

		RichTextInfo GetRichTextInfo() override;

	private:
		size_t endPos = 0;
	};

}

