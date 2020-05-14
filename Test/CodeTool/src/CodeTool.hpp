#pragma once

#include <qplaintextedit.h>
#include <ICodeTool.hpp>

//-------------------------------------------------------------------------------------------------------
class CodeTool : private QPlainTextEdit, public ICodeTool
{
public:
	CodeTool();

	// pt::Tool
	void onOpen() override;
	void onUpdate(float dt) override;
	void onClose() override;

	// ICodeTool
	void setText(std::string text) override;
	std::string getText() const override;
};