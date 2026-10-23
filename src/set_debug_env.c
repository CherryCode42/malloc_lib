#include "../inc/malloc.h"

t_debug_cfg g_debug_cfg = {
    .debug = 0,
    .check_level = 0,
    .log_enabled = 0
};

void ensure_debug_config( )
{
    static int initialized = 0;

    if (!initialized)
    {
        init_debug_config();
        initialized = 1;
    }
}

void init_debug_config( )
{
	char *env;

	env = getenv("MALLOC_DEBUG");
	if (env)
		g_debug_cfg.debug = atoi(env);

	env = getenv("MALLOC_CHECK");
	if (env)
		g_debug_cfg.check_level = atoi(env);

	env = getenv("MALLOC_LOG");
	if (env)
		g_debug_cfg.log_enabled = atoi(env);
}

