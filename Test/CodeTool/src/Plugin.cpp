#include <iostream>

#include <pp/PolyPlugin.hpp>
#include <CodeTool.hpp>

namespace
{

//-------------------------------------------------------------------------------------------------------
class Plugin : public pp::IPlugin
{
public:
	void init(std::shared_ptr<pp::Router> router) final
	{
		router->registerIntentHandler<pt::CreateToolIntent<ICodeTool>>(getPluginInfo(),
			[this] (pt::CreateToolIntent<ICodeTool> intent)
			{
				return std::make_unique<CodeTool>();
			});
	}

	void deinit(std::shared_ptr<pp::Router> router) final { }
	pp::PluginInfo getPluginInfo() const final { return { "CodeTool", { 1, 0, 0} }; }
};

} // namespace

//-------------------------------------------------------------------------------------------------------
POLY_PLUGIN_ENTRY()
{
	return new Plugin();
}