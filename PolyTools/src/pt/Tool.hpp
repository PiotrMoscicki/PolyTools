#pragma once

#include <qundostack.h>

#include <pp/Router.hpp>
#include <pt/IActionsRegistry.hpp>
#include <pt/IToolWindowHandle.hpp>

namespace pt
{
	// ************************************************************************************************
	class Tool
	{
	public:
		// ********************************************************************************************
		class Dependencies
		{
		public:
			std::shared_ptr<pp::Router> router;
			std::shared_ptr<QUndoStack> undoStack;
			std::unique_ptr<IToolWindowHandle> window;
			std::shared_ptr<IActionsRegistry> actionsRegistry;
			std::string toolBarConfig;
		};

		// ********************************************************************************************
		class OwnerAttorney
		{
		protected:
			static void open(Tool& tool, Dependencies dependencies) { tool.open(std::move(dependencies)); }
			static void update(Tool& tool, const float dt) { tool.update(dt); }
			static void close(Tool& tool) { tool.close(); }
		};

	protected:
		virtual void onOpen() = 0;
		virtual void onUpdate(float dt) = 0;
		virtual void onClose() = 0;

		void setTitle(const std::string& name) { m_deps.window->setTitle(name); }
		void setWidget(QWidget* widget) { m_deps.window->setWidget(widget); }

		// actions (action bar is automatically refreshed)
		bool registerAction(std::string uniqueName, std::shared_ptr<QAction> action);

		// undo/redo
		std::shared_ptr<QUndoStack> getUndoStack() { return m_deps.undoStack; }

		// intents & events
		std::shared_ptr<pp::Router> getRouter() { return m_deps.router; }

	private:
		void open(Dependencies dependencies);
		void update(const float dt);
		void close();

		Dependencies m_deps;
	};
} // namespace pt