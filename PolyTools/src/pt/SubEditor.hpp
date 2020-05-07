#pragma once

#include <qstatusbar.h>

#include <pt/IActionsRegistry.hpp>
#include <pt/ISubEditorWindowHandle.hpp>
#include <pt/Tool.hpp>

namespace pt
{
	// ************************************************************************************************
	class SubEditor : public Tool::OwnerAttorney
	{
	public:
		// ********************************************************************************************
		class Dependencies
		{
		public:
			std::shared_ptr<pp::Router> router;
			std::shared_ptr<IActionsRegistry> actionsRegistry;
			std::string manuBarConfig;
			std::string toolBarConfig;
			std::string lqyoutConfig;
		};

		// ********************************************************************************************
		class OwnerAttorney
		{
		protected:
			static void open(SubEditor& subEditor, Dependencies dependencies) { subEditor.open(std::move(dependencies)); }
			static void update(SubEditor& subEditor, const float dt) { subEditor.update(dt); }
			static void close(SubEditor& subEditor) { subEditor.close(); }
		};

	protected:
		virtual void onOpen() = 0;
		virtual void onUpdate(float dt) = 0;
		virtual void onClose() = 0;

		// name
		void setTitle(const std::string& name) { m_window->setTitle(name); }
		void setStatusBar(QStatusBar* statusBar) { m_window->setStatusBar(statusBar); }

		// managing tools
		template <typename T, typename... Args>
		T& registerTool(std::string uniqueName, Args&&... args)
		{
			std::unique_ptr<T> newTool = std::new_unique<T>(std::forward<Args>(args)...);
			m_tools.insert(std::move(name), std::move(newTool));
		}

		template <typename T, typename... Args>
		T& openTool(std::string uniqueName, Args&&... args)
		{
			registerTool<T>(uniqueName, std::forward<Args>(args)...);

			if (std::optional<Tool::Dependencies> deps = generateToolDeps(uniqueName); deps.has_value())
				Tool::OwnerAttorney::open(*newTool, std::move(toolDeps));
			else
			{
				m_deps.router->processEvent(pp::LogEvent{
					"Couldn't open tool.",
					pp::LogEvent::eLogLevel::ERROR });
			}

			return getTool<T>();
		}

		template <typename T>
		void closeTool();

		template <typename T>
		T& getTool();

		template <typename T>
		bool isToolOpen();

		// actions (action bar is automatically refreshed)
		bool registerAction(std::string uniqueName, std::shared_ptr<QAction> action);

		// undo/redo
		std::shared_ptr<QUndoStack> getUndoStack() { return m_undoStack; }

		// intents & events
		std::shared_ptr<pp::Router> getRouter() { return m_deps.router; }

	private:
		void open(Dependencies dependencies);
		void update(const float dt);
		void close();
		std::optional<Tool::Dependencies> generateToolDeps(const std::string& uniqueName);

		Dependencies m_deps;
		std::unique_ptr<ISubEditorWindowHandle> m_window;
		std::shared_ptr<QUndoStack> m_undoStack;

		std::map<std::string, std::unique_ptr<Tool>> m_tools;
	};
} // namespace pt