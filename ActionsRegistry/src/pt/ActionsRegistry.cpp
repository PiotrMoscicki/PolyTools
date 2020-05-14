#include <pt/ActionsRegistry.hpp>

#include <qmenubar.h>
#include <qtoolbar.h>

namespace pt
{

// ************************************************************************************************
bool ActionsRegistry::registerAction(std::string uniqueName, std::shared_ptr<QAction> action)
{
	return false;
}
// ************************************************************************************************
void ActionsRegistry::refreshShortcuts(const std::string& config)
{
}
// ************************************************************************************************
QMenuBar* ActionsRegistry::createMenuBar(const std::string& config)
{
	return new QMenuBar();
}

// ************************************************************************************************
QToolBar* ActionsRegistry::createToolBar(const std::string& config)
{
	return new QToolBar();
}

} // namespace pt