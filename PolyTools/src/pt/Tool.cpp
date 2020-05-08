#include <pt/Tool.hpp>

using namespace pt;

// ************************************************************************************************
bool Tool::registerAction(std::string uniqueName, std::shared_ptr<QAction> action)
{
	if (m_deps.actionsRegistry->registerAction(std::move(uniqueName), std::move(action)))
	{
		m_deps.window->setToolBar(m_deps.actionsRegistry->createToolBar(m_defaultConfigs.toolBarConfig));
		return true;
	}
	else
		return false;
}

// ************************************************************************************************
void Tool::open(Dependencies dependencies)
{
	m_deps = std::move(dependencies);
	onOpen();
	m_deps.window->setToolBar(m_deps.actionsRegistry->createToolBar(m_deps.toolBarConfig));
	m_isOpen = true;
}

// ************************************************************************************************
void Tool::update(const float dt)
{
	onUpdate(dt);
}

// ************************************************************************************************
void Tool::close()
{
	m_isOpen = false;
	onClose();
}
