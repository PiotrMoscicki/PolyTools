#include <iostream>

#include <pp/PolyPlugin.hpp>

#include <AddIntent.hpp>

//-------------------------------------------------------------------------------------------------------
class Plugin : public pp::IPlugin
{
public:
	void init(std::shared_ptr<pp::IntentRouter> router) final
	{
		router->registerReceiver<AddIntent>(getPluginInfo(), [this] (AddIntent intent) { return addIntentReceiver(std::move(intent)); });
	}

	void deinit(std::shared_ptr<pp::IntentRouter> router) final { }
	pp::PluginInfo getPluginInfo() const final { return { "Calculator", { 1, 0, 0} }; }

private:
	AddIntent::Result addIntentReceiver(AddIntent intent) { return intent.a + intent.b; }
};

//-------------------------------------------------------------------------------------------------------
POLY_PLUGIN_ENTRY()
{
	return new Plugin();
}

class Router;

class SubEditor
{
public:
	// 
	void init(std::shared_ptr<Router> router);

protected:
	bool registerAction(std::string name, std::unique_ptr<QAction> action);

	virtual void onInit() = 0;

	const std::shared_ptr<Router> m_router;

private:
	void setupMenuBar();
}

class TextSubEditor
{
public:

}

class OpenTextSubEditor
{
public:
	using Result = bool;
	static inline pp::IntentInfo Info = { "OpenTextSubEditor", 1 };
}




class 