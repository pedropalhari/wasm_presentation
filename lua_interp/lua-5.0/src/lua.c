#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static char *stackDump(lua_State *L)
{
  char buffer[512];
  char auxBuffer[256];
  int i;
  int top = lua_gettop(L);
  for (i = 1; i <= top; i++)
  { /* repeat for each level */
    int t = lua_type(L, i);
    switch (t)
    {

    case LUA_TSTRING: /* strings */
      printf("`%s'", lua_tostring(L, i));
      break;

    case LUA_TBOOLEAN: /* booleans */
      printf(lua_toboolean(L, i) ? "true" : "false");
      break;

    case LUA_TNUMBER: /* numbers */
      gcvt(lua_tonumber(L, i), 4, auxBuffer);
      //strcat(buffer, auxBuffer);
      break;

    default: /* other values */
      //strcat(buffer, lua_typename(L, t));
      break;
    }
    printf("  "); /* put a separator */
  }
  printf("\n"); /* end the listing */
}

char *runString(char *s)
{
}

int main(void)
{
  char buff[256];
  int error;
  lua_State *L = lua_open(); /* opens Lua */
  luaopen_base(L);           /* opens the basic library */
  luaopen_table(L);          /* opens the table library */
  luaopen_io(L);             /* opens the I/O library */
  luaopen_string(L);         /* opens the string lib. */
  luaopen_math(L);           /* opens the math lib. */

  error = luaL_loadbuffer(L, "function bora()\n return 10;\n end\0", strlen("function bora()\n return 10;\n end\0"), "line") ||
          lua_pcall(L, 0, 0, 0);

  lua_getglobal(L, "bora");
  lua_call(L, 0, 1);

  //printf("%s", stackDump(L));

  lua_close(L);
  return 0;
}