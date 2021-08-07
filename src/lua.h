#pragma once

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define lua_reg_func(n, f) (lua_pushcfunction(L, f), lua_setfield(L, -2, n))
#define STRING_NUM(n) #n
#define LUA_ARG_ERROR(n) "error: requires " STRING_NUM(n) " arguments"
#define lua_check_num_args(n)                   \
    if (lua_gettop(l) != n) {                   \
        return luaL_error(l, LUA_ARG_ERROR(n)); \
    }

extern lua_State *L;

void init_lua();
void deinit_lua();

void lua_run(const char *);
