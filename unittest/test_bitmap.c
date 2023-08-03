
#include <stdbool.h>
#include <stdint.h>
#include <error_codes.h>
#include <bitmap.h>
#include "test_main.h"
#include "bm.h"


bool test_bitmap(void){
    
    /* Just test that we can link with bitmap library */
    /* Actual test is done in that library */
    bitmap_create(100, 80, RGB24);
    return true;
}
