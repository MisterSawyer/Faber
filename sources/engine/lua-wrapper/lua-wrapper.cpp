#include "lua-wrapper.h"
#include <iostream>
#include <string>

namespace hospite
{
	LuaMachine::LuaMachine()
	{
		L = luaL_newstate();
		luaL_openlibs(L);

		if (L == nullptr)
		{
			LOG_ERR("Cannot initialize Lua machine");
			m_initialized = false;
		}

		m_initialized = true;
		LOG_INF("Lua machine created");
	}

	LuaMachine::~LuaMachine()
	{
		lua_close(L);
		LOG_INF("Lua machine destroyed");
	}

	bool LuaMachine::CheckResult(int result)
	{
		if (result != LUA_OK)
		{
			if (lua_isstring(L, -1)) {
				LOG_ERR("Invalid result " << lua_tostring(L, -1));
				if(GetStackSize() > 0)lua_pop(L, 1); // pop error msg from stack
				DisplayStack();
			}

			return false;
		}
		return true;
	}

	bool LuaMachine::PerformCommand(const std::string& command)
	{
		int result = luaL_dostring(L, command.c_str());

		return CheckResult(result);
	}

	bool LuaMachine::PerformScript(const std::string& fileName)
	{
		int result = luaL_dofile(L, fileName.c_str());

		return CheckResult(result);
	}

	bool LuaMachine::BindFunction(const std::string& functionName)
	{
		lua_getglobal(L, functionName.c_str());// push function name onto the stack
		if (lua_isfunction(L, -1) == false)
		{
			LOG_WAR(functionName << " is not the name of a function");
			lua_pop(L, 1); // destroy nil 
			return false;
		}

		//variable name is on the stack
		m_numberOfArguments = 0;
		return true;
	}

	std::size_t LuaMachine::GetStackSize()
	{
		return (std::size_t)(lua_gettop(L));
	}

	void LuaMachine::DisplayStack()
	{
		int top = lua_gettop(L);

		std::string str = "Lua stack(" + std::to_string(top) + ") is \n";
		for (int index = top; index > 0; index--)
		{
			int type = lua_type(L, index);
			switch (type)
			{
				// booleans
			case LUA_TBOOLEAN:
				str = str + (lua_toboolean(L, index) ? "true" : "false") + "\n";
				break;

				// numbers
			case LUA_TNUMBER:
				str = str + std::to_string(lua_tonumber(L, index)) + "\n";
				break;

				// strings
			case LUA_TSTRING:
				str = str + lua_tostring(L, index) + "\n";
				break;

				// other
			default:
				str = str + lua_typename(L, type) + "\n";
				break;
			}
		}
		std::cout << (str);
	}
}