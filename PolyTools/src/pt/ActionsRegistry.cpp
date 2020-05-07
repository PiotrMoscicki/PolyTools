#include <pt/ActionsRegistry.hpp>

using namespace pt;

// ************************************************************************************************
bool ActionsRegistry::registerAction(std::string uniqueName, std::shared_ptr<QAction> action)
{
	return false;
}

// ************************************************************************************************
QMenuBar* ActionsRegistry::createMenuBar(const std::string& config)
{
	return nullptr;
}

// ************************************************************************************************
QToolBar* ActionsRegistry::createToolBar(const std::string& config)
{
	return nullptr;
}
