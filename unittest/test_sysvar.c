


#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "sysvar.h"

bool test_sysvar(void){
    char* str;
    str = sysvar_current_date();
    printf ("Date %s\n", str);
    free(str);

    str = sysvar_current_time();
    printf ("Time %s\n", str);
    free(str);

    str = sysvar_current_weekday();
    printf ("Day of week %s\n", str);
    free(str);

    sysvar_set_layout_name("min layout");
    str = sysvar_get_layout_name();
    printf ("Layout name = %s\n", str);
    free(str);

    sysvar_set_layout_size(480, 320);
    uint16_t width, height;
    sysvar_get_layout_size(&width, &height);
    if (480 != width || 320 != height){
	fprintf (stderr, "Error in function sysvar_get_layout_size\n");
	return false;
    }

    sysvar_set_layout_format("bmp");
    str = sysvar_get_layout_format();
    if (strcmp(str, "bmp")){
	fprintf (stderr, "Error in function sysvar_get_layout_format\n");
	return false;
    }
    free(str);

    sysvar_set_layout_resolution(24);
    uint16_t resolution = sysvar_get_layout_resolution();
    if (24 != resolution){
	fprintf (stderr, "Error in function sysvar_get_layout_resolution\n");
	return false;
    }

    sysvar_set_font_location("/usr/share/fonts/dejavu-sans-fonts/");
    str = sysvar_get_font_location();
    if (strcmp(str, "/usr/share/fonts/dejavu-sans-fonts/")){
	fprintf (stderr, "Error in function sysvar_get_font_location\n");
	return false;
    }
    free(str);

    sysvar_set_default_font("DejaVuSans.ttf");
    str = sysvar_get_default_font();
    if (strcmp(str, "DejaVuSans.ttf")){
	fprintf (stderr, "Error in function sysvar_get_default_font\n");
	return false;
    }
    free(str);
    return true;
}
