#include "../targalib.h"
#include <stdio.h>

int main()
{
	tga_image_t *earth_image = load_tga_image("earth.tga");
	printf("Image details after load: \n");
	printf("Width: %d\n", earth_image->height);
	printf("Height: %d\n", earth_image->width);
	printf("Total pixel size: %d\n", earth_image->pixel_count);
	return 0;
}