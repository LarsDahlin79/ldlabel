
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <error_codes.h>
#include <bitmap.h>
#include "freetype.h"
#include "graphics.h"
#include "utils.h"
#include "sysvar.h"
#include "zint_interface.h"

static struct bitmap_definition_t* _bitmap = NULL;
static char* _filename = NULL;

bool graphics_create(char* filename, uint16_t width, uint16_t height, uint8_t resolution){
    if (NULL != filename && utils_string_ends_with(filename, ".bmp")){
	_bitmap = bitmap_create(width, height, RGB24);
	if (NULL == _bitmap){
	    return false;
	}
	_filename = calloc(sizeof(char), strlen(filename) + 1);
	strcpy(_filename, filename);
    }
    return true;
}

bool graphics_destroy(char* filename){
    if (utils_string_ends_with(_filename, ".bmp") &&
	!strcmp(_filename, filename)){
	bitmap_destroy(_bitmap);
	return true;
    }
    return false;
}

bool graphics_set_pixel(char* filename, uint32_t xpos, uint32_t ypos,
			uint32_t red, uint32_t green, uint32_t blue,
			uint32_t alpha){

    /* if filename ends with .bmp, call Bitmap library function */
    if (NULL != _bitmap && utils_string_ends_with(_filename, ".bmp")){
	bitmap_set_pixel(_bitmap, xpos, ypos, red, green, blue, alpha);
    }
    return true;
}

bool graphics_draw_square(char* filename, uint32_t x1, uint32_t y1,
			  uint32_t x2, uint32_t y2,
			  uint32_t red, uint32_t green, uint32_t blue,
			  uint32_t alpha){
    bool success = false;
    if (NULL != _bitmap && utils_string_ends_with(_filename, ".bmp")){
	if (NO_ERROR == bitmap_draw_rectangle(_bitmap, x1, y1, x2, y2, red, green, blue, alpha)){
	    success = true;
	}
    }
    return success;
}

bool graphics_draw_line(char* filename, uint32_t x1, uint32_t y1,
			uint32_t x2, uint32_t y2,
			uint32_t red, uint32_t green, uint32_t blue,
			uint32_t alpha){
    bool success = false;
    if (NULL != _bitmap && utils_string_ends_with(_filename, ".bmp")){
	if (NO_ERROR == bitmap_draw_line(_bitmap, x1, y1, x2, y2, red, green, blue, alpha)){
	    success = true;
	}
    }
    return success;
}

bool graphics_fill_image(char* filename, uint32_t red, uint32_t green,
			 uint32_t blue, uint32_t alpha){
    bool success = false;
    if (NULL != _bitmap && utils_string_ends_with(_filename, ".bmp")){
	error_codes error = bitmap_fill(_bitmap, red, green, blue);
	success = error == NO_ERROR;
    }
    return success;
}

bool graphics_save_file(char* filename){
    error_codes error = NO_ERROR;
    if (NULL != _filename && NULL != _bitmap && utils_string_ends_with(_filename, ".bmp")){
	error = bitmap_write_to_file(_bitmap, _filename);
    }
    return error == NO_ERROR;
}

bool graphics_text(char* filename, char* text, uint16_t xpos,
		   uint16_t ypos, uint32_t red, uint32_t green,
		   uint32_t blue, uint32_t alpha,
		   char* font){
    bool success = false;

    char* font_file = sysvar_get_font_location();
    char* font_name;

    if (NULL == font){
	font_name = sysvar_get_default_font();
    }else{
	font_name = font;
    }

    utils_append_string(font_file, font_name);
    if (NULL == font_file){
	return false;
    }

    if (NULL != _bitmap && utils_string_ends_with(_filename, ".bmp")){
	ft_init();
	ft_set_font(font_file);
	ft_draw_string(filename, xpos, ypos, 500, 100,
		       red, green, blue, text, 1,
		       font_file);
	success = true;
    }
    return success;
}

bool graphics_draw_barcode(char* filename, uint16_t type, char* data, uint16_t xpos, uint16_t ypos, uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha){

    bool success = false;
    if (NULL != _bitmap && utils_string_ends_with(_filename, ".bmp")){
	success = zint_draw_barcode(_filename, xpos, ypos, type, data, red, green, blue);
    }
    return success;
}
