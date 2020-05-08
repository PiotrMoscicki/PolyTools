#pragma once

#include <pt/IActionsRegistry.hpp>

namespace pt
{
	// ************************************************************************************************
	class ActionsRegistry : public IActionsRegistry
	{
	public:
		bool registerAction(std::string uniqueName, std::shared_ptr<QAction> action) override;

		void refreshShortcuts(const std::string& config) override;
		QMenuBar* createMenuBar(const std::string& config) override;
		QToolBar* createToolBar(const std::string& config) override;

	private:
		std::map<std::string, std::shared_ptr<QAction>> m_actions;
	};
} // namespace pt