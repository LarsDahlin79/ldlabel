

#include <stdbool.h>
#include <stdint.h>
#include <zint.h>
#include "test_main.h"
#include "zint_interface.h"
#include "graphics.h"

bool test_zint(void){
    graphics_create("barcode.bmp", 500, 600, 24);
    graphics_fill_image("barcode.bmp", 0xFF, 0xFF, 0xFF, 0xFF);
    zint_draw_barcode("barcode.bmp", 10, 10, 29, "0123456789", 0x00, 0x00, 0xFF);
    zint_draw_barcode("barcode.bmp", 10, 210, 58, "0123456789", 0xFF, 0x00, 0xFF);
    zint_draw_barcode("barcode.bmp", 10, 410, 58, "www.logisnext.eu", 0x00, 0x00, 0x00);
    graphics_save_file("barcode.bmp");
    graphics_destroy("barcode.bmp");
    return true;
}
