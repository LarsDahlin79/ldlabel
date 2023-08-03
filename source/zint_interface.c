
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <zint.h>
#include "graphics.h"
#include "zint_interface.h"

static void draw_barcode(char* bitmap, int x, int y, uint32_t red, uint32_t green, uint32_t blue,
			 struct zint_symbol *barcode){
    uint32_t pos = 0, x1 = x, y1 = y;
    uint32_t h, w;

    pos = 0;
    h = barcode->bitmap_height;
    w = barcode->bitmap_width;
    while (y1 < h + y){
	x1 = x;
	while(x1 < w + x){	    
	    if (!barcode->bitmap[pos]){
		graphics_set_pixel(bitmap, x1, y1, red, green, blue, 0x00);
	    }
	    x1++;
	    pos += 3;
	}
	y1++;
    }

}

bool zint_draw_barcode(char* bitmap, int x, int y, int symbology, char* data, uint32_t red, uint32_t green, uint32_t blue){

    struct zint_symbol *barcode=ZBarcode_Create();
    if (barcode==NULL){
	fprintf (stderr, "Error creating barcode\n");
	return false;
    }

    barcode->symbology=symbology;
    ZBarcode_Encode_and_Buffer(barcode,
			       (unsigned char*)data,
			       strlen(data),
			       0);
    draw_barcode(bitmap, x, y, red, green, blue, barcode);
    ZBarcode_Delete(barcode);
    return true;
}
