
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "test_main.h"
#include "graphics.h"
#include "freetype.h"



bool test_freetype(void){

    ft_init();
    if (!ft_set_font("/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf")){
	fprintf (stderr, "Error loading font\n");
	return false;
    }

    graphics_create("char.bmp", 500, 100, 24);
    ft_draw_string("char.bmp", 10, 10, 500, 100, 0xFF, 0xFF, 0xFF,
		   "I am Error", 1,
		   "/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf");
    ft_draw_string("char.bmp", 100, 10, 500, 100, 0xFF, 0x00, 0x0,
		   "Lars Dahlin", 1,
		   "/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf");
    graphics_save_file("char.bmp");
    graphics_destroy("char.bmp");
    return true;
}
