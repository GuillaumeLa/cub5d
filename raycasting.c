#include "cub3d.h"

void print_playerv2()
{
	printf("(X %f, Y %f)\n", s()->p.X, s()->p.Y);
    printf("(dirX %f, dirY %f)\n", s()->p.dirX, s()->p.dirY);
    printf("(planeX %f, planeY %f)\n", s()->p.planeX, s()->p.planeY);
    printf("\n");
}

void draw_vertical_line(int x, double perpWallDist, int side, t_config *game)
{
    int lineHeight = (int)(HEIGHT / perpWallDist);

    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0) drawStart = 0;

    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

    // Couleur du mur (simple pour l'exemple)
    int color;
    if (side == 1)
        color = 0xAAAAAA; // Mur vertical (Nord/Sud)
    else
        color = 0xFFFFFF; // Mur horizontal (Est/Ouest)

    // Dessiner la ligne verticale pixel par pixel
    for (int y = drawStart; y <= drawEnd; y++) {
        mlx_pixel_put(game->mlx, game->win, x, y, color);
    }
}

void cast_ray(int x)
{
    double cameraX = 2 * x / (double)WIDTH - 1;
    double rayDirX = s()->p.dirX + s()->p.planeX * cameraX;
    double rayDirY = s()->p.dirY + s()->p.planeY * cameraX;

    int mapX = (int)s()->p.X;
    int mapY = (int)s()->p.Y;

    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);

    double sideDistX, sideDistY;
    int stepX, stepY;

    // Initialisation de step et sideDist
    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (s()->p.X - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - s()->p.X) * deltaDistX;
    }

    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (s()->p.Y - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - s()->p.Y) * deltaDistY;
    }

    // Algorithme DDA
    int hit = 0;
    int side;
    while (hit == 0) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (s()->map.data[mapX][mapY] == '1') // ou > 0 si c’est un int
            hit = 1;
    }

    // Distance du joueur au mur
    double perpWallDist;
    if (side == 0)
        perpWallDist = (mapX - s()->p.X + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (mapY - s()->p.Y + (1 - stepY) / 2) / rayDirY;

    // Tu peux maintenant utiliser perpWallDist pour dessiner une ligne verticale
    draw_vertical_line(x, perpWallDist, side, s());
}

int raycasting()
{
    print_playerv2();

    s()->screen.img = mlx_new_image(s()->mlx, WIDTH, HEIGHT);
    if (!s()->screen.img)
		return (printf("Error\nCannot init screen.img\n"), 0);
    for (int x = 0; x < WIDTH; x++)
        cast_ray(x);
    mlx_put_image_to_window(s()->mlx, s()->win, s()->screen.img, 0,0);
    return 0;
}

