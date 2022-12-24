#include "pch.h"
#include "Helium.h"

#include <map>
#include <string>

using namespace std;

Helium::HeliumExtensionLogger logger("HeliumBackup", "Main");

HELIUM_EXTENSION_EXPORT map<string, string> extension_metadata()
{
	return {
		{"extension_name", "Helium Backup"},
		{"author", "Helium DevTeam"},
		{"url", "https://github.com/Helium-DevTeam/HeliumBackup"},
		{"description", "A official backup extension for Helium."},
		{"helium_version", ">=0.8.38-alpha.0"}
	};
}

int hback_list(Helium::HeliumCommandContext& ctx)
{
	logger.debug("#hback list!");
	return 0;
}

HELIUM_EXTENSION_EXPORT int on_self_load()
{
	logger.debug("Hello Helium Extension World!");
	auto root = Helium::command_dispatcher.Register("#hback");
	auto create = root.Then<Literal>("create");
	auto restore = root.Then<Literal>("restore");
	auto list = root.Then<Literal>("list");
	list.Executes(hback_list);
	auto del = root.Then<Literal>("delete");

	const auto server_ptr = Helium::helium_server_manager.GetServer("helium-server-test1");
	if (server_ptr) {
		auto dir = server_ptr->GetServerDirectory();
		logger.debug(dir.string());
	}

	const auto extension_ptr = Helium::helium_extension_manager.GetExtension("HeliumBackup");
	if(extension_ptr)
	{
		auto name = extension_ptr->GetExtensionDescription();
		logger.debug(name);
	}

	for(auto& server_pointer : Helium::helium_server_manager.GetServerList())
	{
		logger.debug(server_pointer->GetServerName());
		server_pointer->AutoStartServer();
	}
	return 0;
}

HELIUM_EXTENSION_EXPORT int helium_server_starting(string_view name, list<any> param)
{
	logger.debug("helium_server_starting!");
	return 0;
}