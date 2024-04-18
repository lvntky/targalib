#include <stdio.h>
#include "../targalib.h"

int main()
{
	tga_image_t image;

	if (tga_read("test.tga", &image) == RETURN_SUCCESS) {
		printf("Image loaded successfully.\n");
		printf("Width: %d, Height: %d, Bits per pixel: %d\n",
		       image.header.width, image.header.height,
		       image.header.bits_per_pixel);

		size_t image_size = image.header.width * image.header.height *
				    (image.header.bits_per_pixel / 8);
		for (size_t i = 0; i < image_size; i++) {
			printf("%ld\tr:%d\tg%d\tb:%d\ta:%d\n", i + 1,
			       image.image_data[i].r, image.image_data[i].g,
			       image.image_data[i].b, image.image_data[i].a);
		}

		// You can access image data through image.image_data

		free(image.image_data);
	} else {
		printf("Failed to load image.\n");
	}

	tga_dump_headers(&image, "output.txt");

	return 0;
}
