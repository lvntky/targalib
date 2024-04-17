// targalib.h - v0.1.0 - Targa image manipulation library - public domain
// Levent Kaya, Apr 2024
//
// Designed to be compact
// Easy to use
// Utilized throug several Computer Graphics projects
//
// Documentation
// TAR Spesification document : https://www.gamers.org/dEngine/quake3/TGA.txt
//
// Version History
// 17-04-2024   v0.1.0  Initial Release
//
// License
// See the end of the file

#ifndef __TARGALIB_H__
#define __TARGALIB_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct tga_header {
	uint8_t id; // Length of the image ID field (0-255)
	uint8_t image_map_type; // Whether a color map is included 0 = no color-map data. 1 = color-map is included.
	/*
    * Compression and color types
    * 0- No Image Data Included
    * 1- Uncompressed, Color mapped image
    * 2- Uncompressed, True Color Image
    * 9- Run-length encoded, Color mapped image
    * 11- Run-Length encoded, Black and white image 
    */
	uint8_t image_type;
	/*
    * Image Specifications
    */
	uint16_t color_map_origin; // Color map origin (2 bytes)
	uint16_t color_map_length; // Color map length (2 bytes)
	uint8_t color_map_depth; // Color map entry size (1 byte)
	uint16_t x_origin; // X-coordinate of the lower-left corner (2 bytes)
	uint16_t y_origin; // Y-coordinate of the lower-left corner (2 bytes)
	uint16_t width; // Width of the image (2 bytes)
	uint16_t height; // Height of the image (2 bytes)
	uint8_t pixel_depth; // Pixel depth (1 byte)
	uint8_t image_descriptor; // Image descriptor byte (1 byte)
	uint8_t width_high; // High byte of width (for handling endianness)
	uint8_t height_high; // High byte of height (for handling endianness)
} tga_header_t;

typedef struct tga_image {
	uint16_t width;
	uint16_t height;
	uint32_t pixel_count;
	uint32_t *pixels; // Array of pixel data (format depends on pixel_depth)
} tga_image_t;

#ifdef __cplusplus
extern "C" {
#endif

tga_image_t *load_tga_image(const char *filename);
bool save_tga_image(const char *filename, tga_image_t *image);
void flip_tga_horizontally();
void flip_tga_vertically();
bool scale_tga_image(tga_image_t *image, int new_width, int new_height);

#endif //__TARGALIB_H__

#ifdef __TARGALIB_IMPLEMENTATION__

tga_image_t *load_tga_image(const char *filename)
{
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		fprintf(stderr,
			"Error: Unable to open file '%s' for reading.\n",
			filename);
		return NULL;
	}

	tga_header_t header;
	if (fread(&header, sizeof(tga_header_t), 1, file) != 1) {
		fprintf(stderr,
			"Error: Unable to read Targa header from file '%s'.\n",
			filename);
		fclose(file);
		return NULL;
	}

	uint16_t width = header.width | (header.width_high << 8);
	uint16_t height = header.height | (header.height_high << 8);

	tga_image_t *image = (tga_image_t *)malloc(sizeof(tga_image_t));
	if (image == NULL) {
		fprintf(stderr,
			"Error: Memory allocation failed for Targa image struct.\n");
		fclose(file);
		return NULL;
	}

	image->width = width;
	image->height = height;
	image->pixel_count = (uint32_t)width * (uint32_t)height;

	image->pixels =
		(uint32_t *)malloc(sizeof(uint32_t) * image->pixel_count);
	if (image->pixels == NULL) {
		fprintf(stderr,
			"Error: Memory allocation failed for Targa image pixel data.\n");
		free(image); // Free previously allocated memory
		fclose(file);
		return NULL;
	}

	if (fread(image->pixels, sizeof(uint32_t), image->pixel_count, file) !=
	    image->pixel_count) {
		fprintf(stderr,
			"Error: Unable to read pixel data from file '%s'.\n",
			filename);
		free(image->pixels); // Free allocated pixel data
		free(image); // Free allocated image struct
		fclose(file);
		return NULL;
	}

	fclose(file);
	return image;
}

#endif //__TARGALIB_IMPLEMENTATION__
/*
-------------------------------------------------------------------------------
This software available under unlicense
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
-------------------------------------------------------------------------------
*/