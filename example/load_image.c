#include "../targalib.h"
#include <stdio.h>

int main()
{
	tga_image_t *image = tga_new(0, 0);
	const char *filename = "earth.tga";
	tga_read("earth.tga", image);
	printf("w: %d, h: %d", image->header.width, image->header.height);


	tga_write("deneme1.tga", image);
	return 0;
}
