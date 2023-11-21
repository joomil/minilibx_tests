#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

#include <X11/X.h>
#include <X11/keysym.h>

typedef struct s_data {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*canvas;
}	t_data;

int	process_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	else if (keysym == XK_t)
		printf("hello world\n");
	return (0);
}

int	process_structure(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	process_mouse(int keysym, t_data *data)
{
	if (keysym == Button1)
		printf("left click\n");
	else if (keysym == Button2)
		printf("scroll button\n");
	else if (keysym == Button3)
		printf("right click\n");
	else if (keysym == Button4)
		printf("scroll_up\n");
	else if (keysym == Button5)
		printf("scroll down\n");
	return (0);
}

void	draw_pixel(t_data *data, int x, int y, int color)
{
	data->canvas[y * 1600 + x] = color;
}

void	draw_rect(t_data *data, int x, int y, int width, int height, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			draw_pixel(data, i + x, j + y, color);
			i++;
		}
		j++;
	}
	
}

int	main_loop(t_data *data)
{
	static int test = 0;
	static int	x = 0;
	static int	y = 0;

	// CLEAR WINDOW
	draw_rect(data, 0, 0, 1600, 900, 0x000000);


	draw_rect(data, x, y, 50, 50, 0xFFFFFF);
	if (x > 1500)
		x = 0;
	if (y > 800)
		y = 0;
	x++;
	y++;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	printf("test=%d\n", test++);
	return (0);
}

int	main()
{
	t_data	*data;

	data = calloc(1, sizeof(*data));
	if (!data)
		return (0);

	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1600, 900, "hello");

	data->img_ptr = mlx_new_image(data->mlx_ptr, 1600, 900);
	int bpp;
	int endian;
	int sizeline;
	data->canvas = (int *)mlx_get_data_addr(data->img_ptr, &bpp, &sizeline, &endian);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, process_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, process_structure, data);
	// mlx_hook(data->win_ptr, ButtonPress, ButtonPressMask, process_mouse, data->mlx_ptr);

	mlx_loop_hook(data->mlx_ptr, main_loop, data);

	mlx_loop(data->mlx_ptr);

	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

// draw_pixel(x=500, y=2)
// [
// 	bpp;
// 	endian;
// 	sizeline
// 	[...........................|......]
// ]
