#include "pch.h"
#include "Helium.h"

int extension_metadata()
{
	return 0;
}

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
	
}