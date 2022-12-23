#include "pch.h"
#include "Helium.h"

#include <map>
#include <string>

using namespace std;

Helium::HeliumExtensionLogger logger("HeliumBackup", "Main");

HELIUM_EXTENSION_EXPORT map<string, string> extension_metadata()
{
	return {
		{"name", "Helium Backup"},
		{"author", "Helium DevTeam"},
		{"url", "https://github.com/Helium-DevTeam/HeliumBackup"},
		{"description", "A official backup extension for Helium."},
		{"helium_version", ">=0.8.38-alpha.0"}
	};
}

HELIUM_EXTENSION_EXPORT int on_self_load()
{
	auto root = Helium::command_dispatcher.Register("#hback");
	auto create = root.Then<Literal>("create");
	auto restore = root.Then<Literal>("restore");
	auto list = root.Then<Literal>("list");
	auto del = root.Then<Literal>("delete");
	logger.info("awa");
	return 0;
}

HELIUM_EXTENSION_EXPORT int on_load()
{
	const auto server_ptr = Helium::helium_server_manager.GetServer("test1");
	auto dir = server_ptr->GetServerDirectory();
	const auto extension_ptr = Helium::helium_extension_manager.GetExtension("HeliumBackup");
	auto d = extension_ptr->GetExtensionPath();
	return 0;
}