#include "Helium.h"

#include <map>
#include <filesystem>
#include <string>

using namespace std;
using namespace Helium;
namespace fs = std::filesystem;

HeliumExtensionLogger logger("HeliumBackup", "Main");

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

int hback_list(HeliumCommandContext& ctx)
{
	logger.debug("#hback list!");
	return 0;
}

int hback_create(HeliumCommandContext& ctx)
{
	logger.debug("#hback create!");
	return 0;
}

int hback_restore(HeliumCommandContext& ctx)
{
	logger.debug("#hback restore!");
	return 0;
}

int hback_delete(HeliumCommandContext& ctx)
{
	logger.debug("#hback delete!");
	return 0;
}

HELIUM_EXTENSION_EXPORT int on_self_load()
{
	using enum HeliumCapabilities;

	logger.debug("Hello Helium Extension World!");
	logger.debug(fs::current_path().string());

	auto root = command_dispatcher.Register("#hback");
	auto create = root.Then<Literal>("create");
	auto restore = root.Then<Literal>("restore");
	auto list = root.Then<Literal>("list");
	auto del = root.Then<Literal>("delete");

	create.Then<Argument, String>("<backup-name>").Then<Argument, GreedyString>("[comment]").Requires([](HeliumCommandSource& src) -> bool
	{
		return HeliumUserManager::CheckCapability(src.GetCapabilities(), HCAP_BASIC_CTL | HCAP_SERVER_CTL);
	}).Executes(hback_create);
	create.Then<Argument, String>("<backup-name>").Requires([](HeliumCommandSource& src) -> bool
	{
		return HeliumUserManager::CheckCapability(src.GetCapabilities(), HCAP_BASIC_CTL | HCAP_SERVER_CTL);
	}).Executes(hback_create);
	restore.Then<Argument, String>("<backup-name>").Requires([](HeliumCommandSource& src) -> bool
	{
		return HeliumUserManager::CheckCapability(src.GetCapabilities(), HCAP_BASIC_CTL | HCAP_SERVER_CTL);
	}).Executes(hback_restore);
	list.Requires([](HeliumCommandSource& src) -> bool
	{
		if(src.GetSource() == CommandSource::PLAYER)
			logger.debug(src.GetSourceInfo().at("player_name"));
		return HeliumUserManager::CheckCapability(src.GetCapabilities(), HCAP_BASIC_CTL | HCAP_SERVER_CTL);
	}).Executes(hback_list);
	del.Then<Argument, String>("<backup-name>").Requires([](HeliumCommandSource& src) -> bool
	{
		return HeliumUserManager::CheckCapability(src.GetCapabilities(), HCAP_BASIC_CTL | HCAP_SERVER_CTL);
	}).Executes(hback_delete);

	return 0;
}