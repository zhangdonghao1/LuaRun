#include"lua.h"

class LuaCo
{
public:
    LuaCo();
    ~LuaCo();
private:
    lua_State* m_L;
};

class LuaVm
{
public:
    LuaVm();
    ~LuaVm();
public:
    bool iniLuaVm();
private:
    lua_State* m_L;
};




