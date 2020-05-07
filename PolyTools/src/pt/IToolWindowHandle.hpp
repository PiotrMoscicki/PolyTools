#pragma once

#include <QToolBar>

namespace pt
{
	// ************************************************************************************************
	class IToolWindowHandle
	{
	public:
		virtual void setTitle(const std::string& title) = 0;
		virtual void setWidget(QWidget* widget) = 0;
		virtual void setToolBar(QToolBar* toolbar) = 0;
		virtual void close() = 0;
	};
} // namespace pt