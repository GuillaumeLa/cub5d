#include "cub3d.h"

int main(int argc , char *argv[])
{
	(void)argv;
	(void)argc;

	if (parsing())
	{
		init_player();
		init_game();
	}
	free_map();
	free_textures();
	return (0);
}