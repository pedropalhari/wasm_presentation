#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static char *stackDump(lua_State *L, char *buffer)
{
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
      sprintf(buffer, "%g", lua_tonumber(L, i));
      break;

    default: /* other values */
      sprintf(buffer, "%s", lua_typename(L, t));
      break;
    }
    printf("  "); /* put a separator */
  }
  printf("\n"); /* end the listing */

  return buffer;
}

char *runString(char *s)
{
  char buffer[512];
  int error;
  lua_State *L = lua_open(); /* opens Lua */
  luaopen_base(L);           /* opens the basic library */
  luaopen_table(L);          /* opens the table library */
  luaopen_io(L);             /* opens the I/O library */
  luaopen_string(L);         /* opens the string lib. */
  luaopen_math(L);           /* opens the math lib. */

  printf("echo %s", s);

  error = luaL_loadbuffer(L, s, strlen(s), "line") ||
          lua_pcall(L, 0, 0, 0);

  lua_getglobal(L, "main");
  lua_call(L, 0, 1);

  stackDump(L, buffer);
  //printf("buffer %s", buffer);

  lua_close(L);
  return buffer;
}

//https://www.lua.org/pil/24.1.html

int main(void)
{
  char buffer[512];
  char buff[256];
  int error;
  lua_State *L = lua_open(); /* opens Lua */
  luaopen_base(L);           /* opens the basic library */
  luaopen_table(L);          /* opens the table library */
  luaopen_io(L);             /* opens the I/O library */
  luaopen_string(L);         /* opens the string lib. */
  luaopen_math(L);           /* opens the math lib. */

  error = luaL_loadbuffer(L, "function main()\nreturn 30 * 4;\nend", strlen("function main()\nreturn 30 * 4;\nend"), "line") ||
          lua_pcall(L, 0, 0, 0);

  lua_getglobal(L, "main");
  lua_call(L, 0, 1);

  printf("%s", stackDump(L, buffer));

  lua_close(L);
  return 0;
}