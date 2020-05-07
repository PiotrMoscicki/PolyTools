#pragma once

#include <pt/IActionsRegistry.hpp>

namespace pt
{
	// ************************************************************************************************
	class ActionsRegistry : public IActionsRegistry
	{
	public:
		bool registerAction(std::string uniqueName, std::shared_ptr<QAction> action) override;

		QMenuBar* createMenuBar(const std::string& config) override;
		QToolBar* createToolBar(const std::string& config) override;
	};
} // namespace pt