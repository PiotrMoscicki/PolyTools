#pragma once

#include <pt/Tool.hpp>

//-------------------------------------------------------------------------------------------------------
class ICodeTool : public pt::Tool
{
public:
	static inline pt::ToolInfo Info = { std::string("ICodeTool") };

	using Tool::Tool;

	virtual void setText(std::string text) = 0;
	virtual std::string getText() const = 0;
};