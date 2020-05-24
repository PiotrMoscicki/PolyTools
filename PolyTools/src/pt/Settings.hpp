#pragma once

#include <pp/Info.hpp>

class QMenuBar;
class QToolBar;

namespace pt
{
	class Tool;
	class SubEditor;

	// ************************************************************************************************
	class RefreshSubEditorShortcuts
	{
	public:
		using Result = bool;
		static inline pp::IntentInfo Info = { "pt::RefreshSubEditorShortcuts", 1 };

		const SubEditor& subEditor;
	};

	// ************************************************************************************************
	class CreateSubEditorMenuBarIntent
	{
	public:
		using Result = QMenuBar*;
		static inline pp::IntentInfo Info = { "pt::CreateMenuBarIntent", 1 };

		const SubEditor& subEditor;
	};

	// ************************************************************************************************
	class CreateSubEditorToolBarIntent
	{
	public:
		using Result = QToolBar*;
		static inline pp::IntentInfo Info = { "pt::CreateSubEditorToolBarIntent", 1 };

		const SubEditor& subEditor;
	};

	// ************************************************************************************************
	class CreateToolToolBarIntent
	{
	public:
		using Result = QToolBar*;
		static inline pp::IntentInfo Info = { "pt::CreateSubEditorToolBarIntent", 1 };

		const Tool& tool;
	};

} // namespace pt