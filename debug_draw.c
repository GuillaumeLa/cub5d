void draw_square(int x, int y, int size, int color, t_config *game)
{
    int i = 0;
    while (i < size)
    {
        put_pixel(x + i, y, color, game);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x, y + i, color, game);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x + size, y + i, color, game);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x + i, y + size, color, game);
        i++;
    }
}

void draw_map(t_config *game)
{
    char **map = game->map.data;
    int color = 0x0000FF;
    int y = 0;
    while (map[y])
    {
        int x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                draw_square(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, color, game);
            x++;
        }
        y++;
    }
}