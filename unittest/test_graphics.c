


#include <stdbool.h>
#include <stdint.h>
#include "test_main.h"
#include "graphics.h"

bool test_graphics(void){
    graphics_create("bitmap.bmp", 500, 500, 24);
    graphics_fill_image("bitmap.bmp", 0xFF, 0xFF, 0xFF, 0xFF);
    graphics_set_pixel("bitmap.bmp", 10, 10, 0x00, 0x80, 0xFF, 0x00);
    graphics_draw_rectangle("bitmap.bmp", 55, 45, 95, 95, 0x00, 0x00, 0x00, 0x00);
    graphics_draw_rectangle("bitmap.bmp", 255, 45, 95, 95, 0x00, 0x00, 0x00, 0x00);
    graphics_draw_line("bitmap.bmp", 155, 145, 195, 195, 0x00, 0x00, 0x00, 0x00);
    graphics_save_file("bitmap.bmp");
    graphics_destroy("bitmap.bmp");
    return true;
}
