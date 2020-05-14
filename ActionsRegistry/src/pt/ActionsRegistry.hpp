#pragma once

#include <qmenubar.h>
#include <qtoolbar.h>
#include <pt/IActionsRegistry.hpp>

namespace pt
{
	// ************************************************************************************************
	class ActionsRegistry : public IActionsRegistry
	{
	public:
		bool registerAction(std::string uniqueName, std::shared_ptr<QAction> action) override;
		 
		/* config format
		[
			{
			  "action": "SelectAll",
			  "shortcut": "ctrl + a"
			},
			{
			  "action": "ExpandAll",
			  "shortcut": "ctrl + m -> ctrl + o"
			},
			{
			  "action": "ExpandAll",
			  "shortcut": "ctrl + m -> ctrl + x"
			},
			{
			  "action": "Delete",
			  "shortcut": "delete || ctrl + backspace"
			}
		]
		*/
		void refreshShortcuts(const std::string& config) override;

		/* config format
		[
			{
				"name": "File",
				"children": [
					{
					  "action": "Save"
					},
					{
					  "action": "Reload",
					  "name": "Reload from disk"
					},
					{
					  "action": "New scene"
					},
					{
					  "name": "Open",
					  "type": "Separator"
					},
					{
					  "action": "Open scene"
					},
					{
					  "name": "Save",
					  "type": "Separator"
					},
					{
					  "action": "Save",
					  "optional": "true",
					  "name": "Save scene as..."
					}
				]
			},
			{
				"name": "Edit",
				"children": [
					{
					  "action": "Undo",
					},
					{
					  "action": "Redo",
					}
				]
			}
		]
		*/
		QMenuBar* createMenuBar(const std::string& config) override;

		/* config format
		[
			{
				"name": "File",
				"action": "Undo"
			},
			{
				"action": "Undo"
			},
			{
				"action": "Redo"
			}
		]
		*/
		QToolBar* createToolBar(const std::string& config) override;
	};

} // namespace pt