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
#include <string.h>

#define TARGALIB_ERROR "targalib.h [ERROR] "
#define RETURN_FAIL 1
#define RETURN_SUCCESS 0

typedef struct tga_header {
	uint8_t id_length;
	uint8_t color_map_type;
	uint8_t image_type;
	uint16_t color_map_origin;
	uint16_t color_map_length;
	uint8_t color_map_depth;
	uint16_t x_origin;
	uint16_t y_origin;
	uint16_t width;
	uint16_t height;
	uint8_t bits_per_pixel;
	uint8_t image_descriptor;
} tga_header_t;

typedef struct tga_color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} tga_color_t;

typedef struct tga_image {
	tga_header_t header;
	tga_color_t *data;
} tga_image_t;

#ifdef __cplusplus
extern "C" {
#endif

tga_image_t *tga_new(uint16_t width, uint16_t height);
void tga_free(tga_image_t *image);
int tga_read(const char *filename, tga_image_t *image);
int tga_write(const char *filename, const tga_image_t *image);
void flip_tga_horizontally();
void flip_tga_vertically();
int scale_tga_image(tga_image_t *image, int new_width, int new_height);

#endif //__TARGALIB_H__

//#ifdef TARGALIB_IMPLEMENTATION

tga_image_t *tga_new(uint16_t width, uint16_t height) {
	tga_image_t* image = (tga_image_t*)malloc(sizeof(tga_image_t));
    if (!image) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    memset(image, 0, sizeof(tga_image_t));

    image->header.width = width;
    image->header.height = height;
    image->header.bits_per_pixel = 32; // Assuming 32 bits per pixel RGBA

    size_t dataSize = width * height * sizeof(tga_color_t);
    image->data = (tga_color_t*)malloc(dataSize);
    if (!image->data) {
        fprintf(stderr, "Memory allocation failed\n");
        free(image);
        return NULL;
    }

    memset(image->data, 0, dataSize);

    return image;
}

int tga_read(const char *filename, tga_image_t *image)
{
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "%sFailed to open file %s for reading.\n",
                TARGALIB_ERROR, filename);
        return RETURN_FAIL;
    }

    if (fread(&image->header, sizeof(tga_header_t), 1, file) != 1) {
        fprintf(stderr, "%sFailed to read image headers from %s.\n",
                TARGALIB_ERROR, filename);
        fclose(file);
        return RETURN_FAIL;
    }

    // Check if the image type is supported (usually uncompressed true-color or grayscale)
    if (image->header.image_type != 2 && image->header.image_type != 3) {
        fprintf(stderr, "%sUnsupported image type in %s.\n",
                TARGALIB_ERROR, filename);
        fclose(file);
        return RETURN_FAIL;
    }

    // Check if the bits per pixel is supported (usually 24 or 32 bits)
    //

    size_t data_size = image->header.width * image->header.height * sizeof(tga_color_t);
    image->data = (tga_color_t *)malloc(data_size);

    if (!image->data) {
        fprintf(stderr, "%sMemory allocation failed for image data %s.\n",
                TARGALIB_ERROR, filename);
        fclose(file);
        return RETURN_FAIL;
    }

    if (fread(image->data, data_size, 1, file) != 1) {
        fprintf(stderr, "%sFailed to read image data from %s.\n",
                TARGALIB_ERROR, filename);
        fclose(file);
        free(image->data);
        return RETURN_FAIL;
    }

    fclose(file);
    return RETURN_SUCCESS;
}

int tga_write(const char *filename, const tga_image_t *image) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "%sFailed to open file %s for writing.\n", TARGALIB_ERROR, filename);
        return RETURN_FAIL;
    }

    // Write TGA header
    if (fwrite(&image->header, sizeof(tga_header_t), 1, file) != 1) {
        fprintf(stderr, "%sFailed to write TGA header to %s.\n", TARGALIB_ERROR, filename);
        fclose(file);
        return RETURN_FAIL;
    }

    // Write image data
    size_t data_size = image->header.width * image->header.height * sizeof(tga_color_t);
    if (fwrite(image->data, data_size, 1, file) != 1) {
        fprintf(stderr, "%sFailed to write image data to %s.\n", TARGALIB_ERROR, filename);
        fclose(file);
        return RETURN_FAIL;
    }

    fclose(file);
    return RETURN_SUCCESS;
}


//#endif //TARGALIB_IMPLEMENTATION
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
