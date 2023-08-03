
#include <stdbool.h>
#include <stdint.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <math.h>
#include "freetype.h"
#include "graphics.h"

static FT_Library library;
static FT_Face face;

bool ft_init(void){
    int error = FT_Init_FreeType(&library);
    if (error){
	return false;
    }
    return true;
}

/* void ft_draw_char(char* bitmap, int x, int y, char c, uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha){ */
static bool ft_draw_char(char* bitmap, int x, int y, int width, 
			 int height, uint32_t red, uint32_t green, uint32_t blue,  FT_Face face){
    /* call draw_pixel in graphics.c */

    int bitpos = 0, imagepos = 0, size, h;
    int pitch, x1, y1, line, top;
    unsigned char* image;

    /* pitch is the width of the char image in bytes, */
    /* including box */
    pitch = face->glyph->bitmap.pitch;
    h = face->glyph->bitmap.rows;
    top = face->glyph->bitmap_top;
    size = pitch * h;
    image = face->glyph->bitmap.buffer;
    x1 = x;
    y1 = y - top + 64;
    line = 0;

    while (imagepos < size){
	bitpos = 0x80;
	while (bitpos > 0){
	    if (image[imagepos] & bitpos){
		graphics_set_pixel(bitmap, x1, y1,
				   red, green, blue,
				   0x00);
	    }
	    bitpos = bitpos >> 1;
	    x1++;
	}
	line++;
	if (line >= pitch){
	    y1++;
	    x1 = x;
	    line = 0;
	}
	imagepos++;
    }
    return true;
}

void ft_draw_string(char* bitmap, int x, int y, int width, 
		    int height, uint32_t red, uint32_t green, uint32_t blue,
		    char* str, int size, char* font){
    int error, glyph_index, pos = 0, len;
    double angle = 0.0f;
    FT_Matrix matrix;
    FT_Vector pen;

    len = strlen(str);
    error = FT_Set_Char_Size(face,
			     0,
			     size*64,
			     800,
			     800);
    if (error){
	fprintf (stderr, "Error setting char size\n");
	return;
    }

    matrix.xx = cos(angle)*0x10000L;
    matrix.xy = -sin(angle)*0x10000L;
    matrix.yx = sin(angle)*0x10000L;
    matrix.yy = cos(angle)*0x10000L;

    pen.x = x;
    pen.y = y;
    while (pos < len){
	FT_Set_Transform(face, &matrix, &pen);

	glyph_index=FT_Get_Char_Index(face, str[pos]);
	error=FT_Load_Glyph(face,
			    glyph_index,
			    FT_LOAD_DEFAULT);
	if (error){
	    fprintf (stderr, "Error setting loading glyph (%d)\n", error);
	    return;
	}

	error=FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);
	if (error){
	    fprintf (stderr, "Error setting rendering glyph\n");
	    return;
	}

	ft_draw_char(bitmap, pen.x, pen.y, width, height, red, green, blue,
		     face);
	pen.x += face->glyph->advance.x>>6;
	pen.y += face->glyph->advance.y>>6;
	pos++;
    }
    
}

bool ft_set_font(char* fontname){
    int error = FT_New_Face(library,
		fontname,
		0,
		&face);
    if (error){
	fprintf (stderr, "Freetype error: cannot handle font %s\n", fontname);
	return false;
    }

    return true;
}
