#pragma once

#include <qmenubar.h>
#include <qtoolbar.h>

namespace pt
{
	// ************************************************************************************************
	class IActionsRegistry
	{
	public:
		virtual bool registerAction(std::string uniqueName, std::shared_ptr<QAction> action) = 0;
		 
		virtual void refreshShortcuts(const std::string& config) = 0;
		virtual QMenuBar* createMenuBar(const std::string& config) = 0;
		virtual QToolBar* createToolBar(const std::string& config) = 0;
	};
} // namespace pt