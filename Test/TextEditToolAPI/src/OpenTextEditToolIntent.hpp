#pragma once

#include <memory>
#include <pp/IntentInfo.hpp>

class TextEditTool;

//-------------------------------------------------------------------------------------------------------
class OpenTextEditToolIntent
{
public:
	using Result = std::unique_ptr<TextEditTool>;
	static inline pp::IntentInfo Info = { "OpenTextEditToolIntent", 1 };
};
