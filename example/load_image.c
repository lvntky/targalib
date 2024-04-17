#include "../targalib.h"
#include <stdio.h>

int main()
{
	tga_image_t *image = tga_new(10, 10);
	const char *filename = "earth.tga";
	tga_read("flag_b32.tga", image);
	tga_print_headers(image);

	return 0;
}
