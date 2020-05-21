#pragma once

#include <pp/Router.hpp>
#include <pt/Settings.hpp>
#include <pt/IToolWindowHandle.hpp>

class QUndoStack;

namespace pt
{
	class ToolInfo
	{
	public:
		std::string name;
	};

	// ************************************************************************************************
	class Tool
	{
	public:
		// ********************************************************************************************
		class Dependencies
		{
		public:
			std::shared_ptr<pp::Router> router;
			std::unique_ptr<IToolWindowHandle> window;
			QUndoStack& undoStack;
			std::map<std::string, std::shared_ptr<QAction>>& actionsRegistry;
		};

		// ********************************************************************************************
		class OwnerAttorney
		{
		protected:
			static void open(Tool& tool, Dependencies dependencies) { tool.open(std::move(dependencies)); }
			static void update(Tool& tool, const float dt) { tool.update(dt); }
			static void close(Tool& tool) { tool.close(); }
		};

		bool isOpen() const { return m_isOpen; }

	protected:
		Tool(Configs configs) : m_defaultConfigs(std::move(configs)) {}
		virtual void onOpen() = 0;
		virtual void onUpdate(float dt) = 0;
		virtual void onClose() = 0;

		void setTitle(const std::string& name) { m_deps.window->setTitle(name); }
		void setWidget(QWidget* widget) { m_deps.window->setWidget(widget); }

		// actions (action bar is automatically refreshed)
		bool registerAction(std::string uniqueName, std::shared_ptr<QAction> action)
		{
			if (m_deps.actionsRegistry->registerAction(std::move(uniqueName), std::move(action)))
			{
				m_deps.window->setToolBar(m_deps.actionsRegistry->createToolBar(m_defaultConfigs.toolBarConfig));
				return true;
			}
			else
				return false;
		}

		// undo/redo
		std::shared_ptr<QUndoStack> getUndoStack() { return m_deps.undoStack; }

		// intents & events
		std::shared_ptr<pp::Router> getRouter() { return m_deps.router; }

	private:
		void open(Dependencies dependencies)
		{
			m_deps = std::move(dependencies);
			onOpen();
			m_deps.window->setToolBar(m_deps.actionsRegistry->createToolBar(m_defaultConfigs.toolBarConfig));
			m_isOpen = true;
		}

		void update(const float dt)
		{
			onUpdate(dt);
		}

		void close()
		{
			m_isOpen = false;
			onClose();
		}

		Configs m_defaultConfigs;
		Dependencies m_deps;
		bool m_isOpen = false;
	};

	// ********************************************************************************************
	template <typename T>
	class CreateToolIntent
	{
	public:
		using Result = std::unique_ptr<T>;
		static inline pp::IntentInfo Info = { std::string("CreateToolIntent_") + T::Info.name, 1 };
	};
} // namespace pt