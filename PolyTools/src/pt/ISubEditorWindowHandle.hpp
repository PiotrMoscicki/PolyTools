#pragma once

#include <string>
#include <memory>

#include <pp/Info.hpp>

class QMenuBar;
class QToolBar;
class QStatusBar;

namespace pt
{
	class IToolWindowHandle;
	class SubEditorInfo;

	// ************************************************************************************************
	// ************************************************************************************************
	// ************************************************************************************************
	class ISubEditorWindowHandle
	{
	public:
		// Sub editor is needed to assign this window to correct settings
		virtual void setOwnerInfo(const SubEditorInfo& info) = 0;

		// Sets title of the sub editor (text in tab)
		virtual void setTitle(const std::string& title) = 0;

		// sets menu bar for the whole sub editor window
		virtual void setMenuBar(QMenuBar* menuBar) = 0;

		// Sets toolbar for the whole sub editor window
		virtual void setToolBar(QToolBar* toolBar) = 0;

		// Sets status bar for sub editor window
		virtual void setStatusBar(QStatusBar* statusBar) = 0;

		// Add tool window (dockable window which will be given to tool so it
		// can set its widget there). Window should save layout after any 
		// change to it and then restore it for specific elements when they 
		// are added
		virtual std::unique_ptr<IToolWindowHandle> addToolWindow(std::string uniqueName) = 0;

		// Close sub editor's window
		virtual void close() = 0;
	};

	// ************************************************************************************************
	// ************************************************************************************************
	// ************************************************************************************************
	class OpenSubEditorWindowIntent
	{
	public:
		using Result = std::unique_ptr<ISubEditorWindowHandle>;
		static inline pp::IntentInfo Info = { "pt::OpenSubEditorWindowIntent", 1 };
	};
} // namespace pt