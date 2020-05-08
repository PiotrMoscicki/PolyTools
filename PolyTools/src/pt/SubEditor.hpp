#pragma once

#include <typeindex>
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
		class Configs
		{
		public:
			std::string manuBarConfig;
			std::string toolBarConfig;
			std::string shortcutsConfig;
			std::string layoutConfig;
		};

		// ********************************************************************************************
		class Dependencies
		{
		public:
			std::shared_ptr<pp::Router> router;
			std::shared_ptr<IActionsRegistry> actionsRegistry;
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
		SubEditor(Configs configs) : m_defaultConfigs(std::move(configs)) {}
		virtual void onOpen() = 0;
		virtual void onUpdate(float dt) = 0;
		virtual void onClose() = 0;

		// name
		void setTitle(const std::string& name) { m_window->setTitle(name); }
		void setStatusBar(QStatusBar* statusBar) { m_window->setStatusBar(statusBar); }

		// ********************************************************************************************
		// managing tools
		template <typename T>
		T* registerTool()
		{
			if (isToolRegistered<T>())
			{
				m_deps.router->processEvent(pp::LogEvent{
					"Tool is already registered; it won't be registered again.",
					pp::LogEvent::eLogLevel::ERROR });
			}
			else
			{
				if (auto tool = m_deps.router->processIntent(CreateToolIntent<T>(); tool.has_value())
					m_tools.insert(std::move(T::Info.name), std::move(tool.value()));
				else
				{
					m_deps.router->processEvent(pp::LogEvent{
						"Couldn't find implementation for tool",
						pp::LogEvent::eLogLevel::ERROR });
				}
			}

			return getTool<T>();
		}

		// ********************************************************************************************
		template <typename T>
		T* openTool()
		{
			if (isToolOpen<T>())
			{
				m_deps.router->processEvent(pp::LogEvent{
					"Tool is already opened; it won't be opened again.",
					pp::LogEvent::eLogLevel::ERROR });
			}
			else
			{
				if (!isToolRegistered<T>())
					registerTool<T>();

				if (std::optional<Tool::Dependencies> deps = generateToolDeps(T::Info); deps.has_value())
					Tool::OwnerAttorney::open(*newTool, std::move(toolDeps));
				else
				{
					m_deps.router->processEvent(pp::LogEvent{
						"Couldn't open tool.",
						pp::LogEvent::eLogLevel::ERROR });
				}
			}

			return getTool<T>();
		}

		// ********************************************************************************************
		template <typename T>
		void closeTool()
		{
			if (isToolRegistered<T>())
			{
				if (isToolOpen<T>())
					Tool::OwnerAttorney::close(getTool<T>());
				else
				{
					m_deps.router->processEvent(pp::LogEvent{
						"Tool is already closed; it won't be closed again.",
						pp::LogEvent::eLogLevel::ERROR });
				}
			}
			else
			{
				m_deps.router->processEvent(pp::LogEvent{
					"Can't close tool which is not registered.",
					pp::LogEvent::eLogLevel::ERROR });
			}
		}

		// ********************************************************************************************
		template <typename T>
		T* getTool()
		{
			if (isToolRegistered<T>())
				return m_tools.find(T::Info)->second;
			else
			{
				m_deps.router->processEvent(pp::LogEvent{
					"Trying to get non-registered tool.",
					pp::LogEvent::eLogLevel::WARN });

				return nullptr;
			}
		}

		// ********************************************************************************************
		template <typename T>
		bool isToolOpen() 
		{
			if (isToolRegistered<T>())
				return getTool<T>().isOpen()
			else
			{
				m_deps.router->processEvent(pp::LogEvent{
					"Checking if non-registered tool is opened.",
					pp::LogEvent::eLogLevel::WARN });

				return false;
			}
		}

		// ********************************************************************************************
		template <typename T>
		bool isToolRegistered() 
		{ 
			return std::find(m_tools.begin(), m_tools.end(), T::Info) != m_tools.end(); 
		}

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

		Configs m_defaultConfigs;
		Dependencies m_deps;
		std::unique_ptr<ISubEditorWindowHandle> m_window;
		std::shared_ptr<QUndoStack> m_undoStack;

		std::map<ToolInfo, std::unique_ptr<Tool>> m_tools;
	};
} // namespace pt