#include <pt/SubEditor.hpp>

#include <pp/Common.hpp>

#include <pt/ActionsRegistry.hpp>

using namespace pt;

// ************************************************************************************************
bool SubEditor::registerAction(std::string uniqueName, std::shared_ptr<QAction> action)
{
	if (m_deps.actionsRegistry->registerAction(std::move(uniqueName), std::move(action)))
	{
		m_window->setMenuBar(m_deps.actionsRegistry->createMenuBar(m_deps.manuBarConfig));
		m_window->setToolBar(m_deps.actionsRegistry->createToolBar(m_deps.toolBarConfig));
		return true;
	}
	else
		return false;
}

// ************************************************************************************************
void SubEditor::open(Dependencies dependencies)
{
	m_deps = std::move(dependencies);

	// get window for sub editor
	if (auto result = m_deps.router->processIntent(OpenISubEditorWindowHandle()); result.has_value())
		m_window = std::move(result.value());
	else
	{
		m_deps.router->processEvent(pp::LogEvent{
			"Couldn't create SubEditorWindowHandle; the SubEditor will not open.",
			pp::LogEvent::eLogLevel::ERROR });

		return;
	}

	// create default action registry if none provided
	if (!m_deps.actionsRegistry)
		m_deps.actionsRegistry = std::make_shared<ActionsRegistry>();

	// create undo stack
	m_undoStack = std::make_shared<QUndoStack>();

	onOpen();

	m_window->setMenuBar(m_deps.actionsRegistry->createMenuBar(m_deps.manuBarConfig));
	m_window->setToolBar(m_deps.actionsRegistry->createToolBar(m_deps.toolBarConfig));
}

// ************************************************************************************************
void SubEditor::update(const float dt)
{
	onUpdate(dt);
}

// ************************************************************************************************
void SubEditor::close()
{
	onClose();
}

// ************************************************************************************************
std::optional<Tool::Dependencies> SubEditor::generateToolDeps(const std::string& uniqueName)
{
	Tool::Dependencies result;
	result.router = m_deps.router;
	result.undoStack = m_undoStack;
	result.actionsRegistry = m_deps.actionsRegistry;
	result.toolBarConfig = uniqueName;

	if (auto result = m_deps.router->processIntent(OpenISubEditorWindowHandle()); result.has_value())
		m_window = std::move(result.value());
	else
	{
		m_deps.router->processEvent(pp::LogEvent{
			"Couldn't create SubEditorWindowHandle; the SubEditor will not open.",
			pp::LogEvent::eLogLevel::ERROR });

		return {};
	}

	return result;
}
