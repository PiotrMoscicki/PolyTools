#include <pt/ActionsRegistry.hpp>

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

using namespace pt;

// ************************************************************************************************
bool ActionsRegistry::registerAction(std::string uniqueName, std::shared_ptr<QAction> action)
{
	if (m_actions.find(uniqueName) != m_actions.end())
	{
		m_actions.insert({ std::move(uniqueName), std::move(action) });
		return true;
	}
	else 
		return false;
}

// ************************************************************************************************
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
void ActionsRegistry::refreshShortcuts(const std::string& config)
{
}

// ************************************************************************************************
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
QMenuBar* ActionsRegistry::createMenuBar(const std::string& config)
{
	QJsonArray root = QJsonDocument::fromRawData(config.c_str(), config.size()).array();

	for (const auto ref: root)
	{
		QJsonObject obj = ref.toObject();
	}

	return nullptr;
}

// ************************************************************************************************
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
QToolBar* ActionsRegistry::createToolBar(const std::string& config)
{
	return nullptr;
}
