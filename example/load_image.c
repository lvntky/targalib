#include <stdio.h>
#include "../targalib.h"

int main()
{
	tga_image_t image;

	if (tga_read("created.tga", &image) == RETURN_SUCCESS) {
		printf("Image loaded successfully.\n");
		printf("Width: %d, Height: %d, Bits per pixel: %d\n",
		       image.header.width, image.header.height,
		       image.header.bits_per_pixel);

		// You can access image data through image.image_data

		free(image.image_data);
	} else {
		printf("Failed to load image.\n");
	}

	return 0;
}
