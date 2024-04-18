#include "../targalib.h"

int main()
{
	uint16_t width = 100;
	uint16_t height = 100;
	int dot_x = 50; // X coordinate of the red dot
	int dot_y = 50; // Y coordinate of the red dot

	tga_image_t *image = tga_new(width, height);
	tga_color_t white = { 255, 255, 255 };
	tga_color_t red = { 0, 0, 255 };
	tga_set_bg(image, white);
	tga_set_pixel(image, dot_x, dot_y, red);
	tga_write("white.tga", image);

	// Free allocated memory
	tga_free(image);

	printf("TGA image generated successfully.\n");
	return 0;
}