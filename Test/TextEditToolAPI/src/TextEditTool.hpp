#pragma once

//-------------------------------------------------------------------------------------------------------
class TextEditTool : public Tool
{
public:
	IObserver
	{
	public:
		virtual void onTextChanged() = 0;
	}

	virtual void setText(QString text) = 0;
	virtual QString getText() const = 0;
}