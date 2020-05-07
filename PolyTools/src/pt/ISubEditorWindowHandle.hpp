#pragma once

#include <pp/Info.hpp>

#include <pt/IToolWindowHandle.hpp>

namespace pt
{
	// ************************************************************************************************
	class ISubEditorWindowHandle
	{
	public:
		virtual void setTitle(const std::string& title) = 0;
		virtual void setToolBar(QToolBar* toolBar) = 0;
		virtual void setMenuBar(QMenuBar* menuBar) = 0;
		virtual void setStatusBar(QStatusBar* statusBar) = 0;
		virtual std::unique_ptr<IToolWindowHandle> addToolWindow(std::string uniqueName) = 0;
		virtual void restoreLayout(const std::string& layoutSettings) = 0;
		virtual std::string saveLayout() const = 0;
		virtual void close() = 0;
	};

	// ************************************************************************************************
	class OpenISubEditorWindowHandle
	{
	public:
		using Result = std::unique_ptr<ISubEditorWindowHandle>;
		static inline pp::IntentInfo Info = { "pt::OpenToolWindowIntent", 1 };
	};
} // namespace pt