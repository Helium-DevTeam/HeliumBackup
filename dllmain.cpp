#include "pch.h"
#include "Helium.h"

int on_self_load()
{
	auto root = Helium::command_dispatcher.Register("#hback");
	auto create = root.Then<Literal>("create");
	auto restore = root.Then<Literal>("restore");
	auto list = root.Then<Literal>("list");
	auto del = root.Then<Literal>("delete");
}

int on_load()
{
	const auto server_ptr = Helium::helium_server_manager.GetServer("test1");
	auto dir = server_ptr->GetServerDirectory();
}