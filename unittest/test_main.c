
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "test_main.h"
#include "main.h"

void test_all(void){
    if (!test_variables()){
	fprintf (stderr, "Error in variables module\n");
	return;
    }else{
	fprintf (stdout, "Variables module OK\n");
    }

    if (!test_sysvar()){
	fprintf (stderr, "Error in sysvar module\n");
	return;
    }else{
	fprintf (stdout, "Sysvar module OK\n");
    }

    if (!test_utils()){
	fprintf (stderr, "Error in utils module\n");
	return;
    }else{
	fprintf (stdout, "Utils module OK\n");
    }

    if (!test_bitmap()){
	fprintf (stderr, "Error in bitmap module\n");
	return;
    }else{
	fprintf (stdout, "Bitmap module OK\n");
    }

    if (!test_graphics()){
	fprintf (stderr, "Error in freetype module\n");
	return;
    }else{
	fprintf (stdout, "Graphics module OK\n");
    }

    if (!test_freetype()){
	fprintf (stderr, "Error in freetype module\n");
	return;
    }else{
	fprintf (stdout, "Freetype module OK\n");
    }

    if (!test_zint()){
	fprintf (stderr, "Error in zint module\n");
	return;
    }else{
	fprintf (stdout, "Zint module OK\n");
    }

    if (!test_ldlabel()){
	fprintf (stderr, "Error in ldlabel module\n");
	return;
    }else{
	fprintf (stdout, "ldlabel module OK\n");
    }

    fprintf (stdout, "All tests successful\n");
}
