

#include <stdbool.h>
#include <stdio.h>
#include "test_main.h"
#include "ldlabel.h"


bool test_ldlabel(void){
    /* command name, resolution, width, height, bgcolour red, green, blue */
    bool success = ldlabel_execute("layout,     my_layout.bmp    , 24, 800, 600, 255, 255, 255, 0");
    if (!success){
	return false;
    }

    /* line, my_layout.bmp, 150, 100, 175, 100, 255, 0, 0, 0, 0 */

    success = ldlabel_execute("font, DejaVuSans.ttf");
    if (!success){
	fprintf (stderr, "Error in function font\n");
	return false;
    }
    success = ldlabel_execute("text, my_layout.bmp, 40, 50, Test layout, 255, 0, 0, 0");
    if (!success){
	fprintf (stderr, "Error in function text\n");
	return false;
    }

    success = ldlabel_execute("barcode, my_layout.bmp, 10, 200, 29, 0123456789, 255, 255, 0, 0");
    if (!success){
	fprintf (stderr, "Error in function barcode\n");
	return false;
    }

    success = ldlabel_execute("variable, name, \" I am\"");
    if (!success){
	fprintf (stderr, "Error in function variable\n");
	return false;
    }

    success = ldlabel_execute("append, name, \" Error\"");
    if (!success){
	fprintf (stderr, "Error in function append\n");
	return false;
    }

    success = ldlabel_execute("save, my_layout.bmp");
    if (!success){
	fprintf (stderr, "Error in function save\n");
	return false;
    }
    return success;
}

