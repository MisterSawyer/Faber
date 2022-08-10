#pragma once
#include <type_traits>
#include <optional>
#include <functional>

#include "../../framework/logger/logger.h"

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#ifdef _WIN64
#pragma comment(lib, "lua54.lib")
#endif

namespace hospite {
	class LuaMachine
	{
	public:
		LuaMachine();
		virtual ~LuaMachine();
		bool PerformCommand(const std::string & cmd);
		bool PerformScript(const std::string& fileName);

		bool CheckResult(int result);

		template<class T>
		std::optional<T> GetVariable()
		{
			LOG_ERR("Unknown variable type");
			return {};
		}

		template<class T>
		std::optional<T> GetVariable(const std::string& name)
		{
			lua_getglobal(L, name.c_str()); // push variable name on stack
			if (lua_isnil(L, -1)) // if variable does not exists
			{
				LOG_WAR("Variable " << name << " is not recognized");
				lua_pop(L, 1); // destroy nil

				return {};
			}

			//variable exists
			return GetVariable<T>();
		}

		template<>
		std::optional<bool> GetVariable()
		{
			if (lua_isboolean(L, -1))
			{
				bool value = (bool)(lua_toboolean(L, -1));
				lua_pop(L, 1); // pop this value from stack
				return std::optional<bool>(value);
			}

			if (lua_isnil(L, -1))// if value on top is nil
			{
				lua_pop(L, 1); // pop it from stack
			}
			LOG_WAR("Variable is not of boolean type");
			return {};
		}

		template<>
		std::optional<int> GetVariable()
		{
			if (lua_isinteger(L, -1))
			{
				int value = (int)(lua_tointeger(L, -1));
				lua_pop(L, 1);
				return std::optional<int>(value);
			}

			if (lua_isnil(L, -1))
			{
				lua_pop(L, 1);
			}
			LOG_WAR("Variable is not of int type");
			return {};
		}

		template<>
		std::optional<float> GetVariable()
		{
			if (lua_isnumber(L, -1))
			{
				float value = (float)(lua_tonumber(L, -1));
				lua_pop(L, 1);
				return std::optional<float>(value);
			}

			if (lua_isnil(L, -1))
			{
				lua_pop(L, 1);
			}
			LOG_WAR("Variable is not of float type");
			return {};
		}

		template<>
		std::optional<std::string> GetVariable()
		{
			if (lua_isstring(L, -1))
			{
				std::string value = (std::string)(lua_tostring(L, -1));
				lua_pop(L, 1); // destroy value
				return std::optional<std::string>(value);
			}

			if (lua_isnil(L, -1))
			{
				lua_pop(L, 1); // destroy nil
			}
			LOG_WAR("Variable is not of string type");
			return {};
		}

		template <class T>
		std::optional<T> GetTableField(const std::string & table, const std::string & field)
		{
			lua_getglobal(L, table.c_str()); // push table name onto the stack
			if (lua_istable(L, -1))
			{
				lua_pushstring(L, field.c_str()); // push field name onto the stack
				if (CheckResult(lua_gettable(L, -2)))// pops key and makes a value or creates error msg which is poped by checkresult
				{
					std::optional<T> value = GetVariable<T>();
					DisplayStack();
					lua_pop(L, 1); // destroy table name
					return value;
				}
			}
			else
			{
				LOG_WAR(table << " is not a valid table");
			}

			lua_pop(L, 1); // destroy nil
			DisplayStack();

		}

		bool BindFunction(const std::string& functionName);
		
		template<class T>
		void SendArgument(const T& arg){
			LOG_WAR("Not a valid type of an argument")
		}

		template<>
		void SendArgument(const bool & arg) {
			lua_pushboolean(L, arg);
			m_numberOfArguments++;
		}

		template<>
		void SendArgument(const int& arg) {
			lua_pushinteger(L, arg);
			m_numberOfArguments++;
		}

		template<>
		void SendArgument(const float& arg) {
			lua_pushnumber(L, arg);
			m_numberOfArguments++;
		}

		template<>
		void SendArgument(const std::string & arg) {
			lua_pushstring(L, arg.c_str());
			m_numberOfArguments++;
		}

		template<class T>
		std::optional<T> CallFuntion()
		{
			int result = lua_pcall(L, m_numberOfArguments, 1, 0); // remove function name and arguments from the stack

			if (CheckResult(result))
			{
				return GetVariable<T>();
			}

			return {};
		}
		 
		std::size_t GetStackSize();
		void DisplayStack();

	private:

		bool m_functionBinded;
		int m_numberOfArguments;

		bool m_initialized;
		lua_State* L;
	};
}