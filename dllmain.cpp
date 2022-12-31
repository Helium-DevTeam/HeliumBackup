#include "Helium.h"

#include <map>
#include <filesystem>
#include <string>
#include <format>
#include <chrono>

#include <boost/locale.hpp>

using namespace std;
using namespace helium;
namespace fs = std::filesystem;

helium_extension_logger_c logger("Helium", "Backup");

HELIUM_EXTENSION_EXPORT map<string, string> extension_metadata()
{
	return {
		{"extension_name", "Helium Backup"},
		{"author", "Helium DevTeam"},
		{"url", "https://github.com/Helium-DevTeam/HeliumBackup"},
		{"description", "A official backup extension for Helium."},
		{"helium_version", ">=0.8.45-alpha.0"}
	};
}

int hback_list(helium_command_context& ctx)
{
	logger.debug("#hback list!");
	return 0;
}

int hback_create(helium_command_context& ctx)
{
	if (ctx.GetSource().get_source() != command_source_e::PLAYER)
	{
		logger.error("This command only work in servers");
		return -1;
	}
	using namespace std::literals::chrono_literals;
	const auto server_name = ctx.GetSource().get_source_info()["server_name"];
	const auto server_wptr = helium_server_manager.get_server(server_name);
	if (auto server_ptr = server_wptr.lock()) {
		fs::path server_save_path = helium_config_manager.get_server_dir() + "/" + server_ptr->get_server_directory().string() + "/world";
		fs::path copy_save_path = helium_config_manager.get_extension_dir() + "/Helium-Backup/" + format("{:%F}-{:%H}-{:%M}-{:%S}"
			, chrono::system_clock::now(), chrono::system_clock::now(), chrono::system_clock::now(), chrono::system_clock::now());
		logger.debug("Saving server " + server_name);
		logger.debug(server_save_path.string());
		logger.debug(copy_save_path.string());

		error_code ec;
		try {
			logger.debug("save-off");
			server_ptr->send_to_server("/save-off");
			logger.debug("save-all flush");
			server_ptr->send_to_server("/save-all flush");
			logger.debug("save-on");
			server_ptr->send_to_server("/save-on");
		}
		catch (fs::filesystem_error& e)
		{
			logger.debug("save-on");
			server_ptr->send_to_server("/save-on");
			logger.error(e.what());
		}
	}
	return 0;
}

int hback_restore(helium_command_context& ctx)
{
	logger.debug("#hback restore!");
	return 0;
}

int hback_delete(helium_command_context& ctx)
{
	logger.debug("#hback delete!");
	return 0;
}

HELIUM_EXTENSION_EXPORT int on_self_load()
{
	using enum helium_capabilities_e;

	logger.debug("Hello Helium Extension World!");
	logger.debug(fs::current_path().string());

	auto root = command_dispatcher.Register("#hback");
	auto create = root.Then<Literal>("create");
	auto restore = root.Then<Literal>("restore");
	auto list = root.Then<Literal>("list");
	auto del = root.Then<Literal>("delete");

	create.Then<Argument, String>("<backup-name>").Then<Argument, GreedyString>("[comment]").Requires([](helium_command_source_c& src) -> bool
		{
			return helium_user_manager_c::check_capability(src.get_capabilities(), HCAP_BASIC_CTL | HCAP_SERVER_CTL);
		}).Executes(hback_create);
		create.Then<Argument, String>("<backup-name>").Requires([](helium_command_source_c& src) -> bool
			{
				return helium_user_manager_c::check_capability(src.get_capabilities(), HCAP_BASIC_CTL | HCAP_SERVER_CTL);
			}).Executes(hback_create);
			restore.Then<Argument, String>("<backup-name>").Requires([](helium_command_source_c& src) -> bool
				{
					return helium_user_manager_c::check_capability(src.get_capabilities(), HCAP_BASIC_CTL | HCAP_SERVER_CTL);
				}).Executes(hback_restore);
				list.Requires([](helium_command_source_c& src) -> bool
					{
						if (src.get_source() == command_source_e::PLAYER)
						logger.debug(src.get_source_info().at("player_name"));
				return helium_user_manager_c::check_capability(src.get_capabilities(), HCAP_BASIC_CTL | HCAP_SERVER_CTL);
					}).Executes(hback_list);
					del.Then<Argument, String>("<backup-name>").Requires([](helium_command_source_c& src) -> bool
						{
							return helium_user_manager_c::check_capability(src.get_capabilities(), HCAP_BASIC_CTL | HCAP_SERVER_CTL);
						}).Executes(hback_delete);

						return 0;
}