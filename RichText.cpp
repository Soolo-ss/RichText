#include "RichText.h"

#include "RichTextParser.h"

#include <vector>

#define MAX_TEXT_BUFFER_SIZE 65535

using namespace RichText;

RichTextParser parser;
std::vector<RichTextInfo> richTextInfos;

char outputBuffer[MAX_TEXT_BUFFER_SIZE];

bool TranslateRichText(const char* target, char** output, int* outputSize, char** outputInfos, int* outputInfosSize)
{
	memset(outputBuffer, 0, MAX_TEXT_BUFFER_SIZE); 

	richTextInfos.clear();
	parser.Clear();

	parser.Parse(target);

	std::string outputStr = parser.GetOutput();
	const char* outputData = outputStr.c_str();
	strncpy(outputBuffer, outputData, outputStr.size());

	*output = outputBuffer;
	*outputSize = static_cast<int>(outputStr.size());

	auto tagInfos = parser.GetTagInfos();

	for (auto tagInfo : tagInfos)
	{
		richTextInfos.push_back(tagInfo->GetRichTextInfo());
	}

	*outputInfos = reinterpret_cast<char*>(richTextInfos.data());
	*outputInfosSize = static_cast<int>(richTextInfos.size());

	return true;
}