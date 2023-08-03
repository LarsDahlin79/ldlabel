

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "test_main.h"
#include "variables.h"

bool test_variables(void){

    if (!variable_init()){
	fprintf (stderr, "Function variable_init failed, line %d\n", __LINE__);
	return false;
    }

    /* No variables have been created yet */
    if (variable_is_variable("var_name")){
	fprintf (stderr, "Function variable_is_variable failed, line %d\n", __LINE__);
	return false;
    }

    if (!variable_create("var_name")){
	fprintf (stderr, "Function variable_create failed, line %d\n", __LINE__);
	return false;
    }

    if (!variable_is_variable("var_name")){
	fprintf (stderr, "Function variable_is_variable failed, line %d\n", __LINE__);
	return false;
    }

    if (!variable_update("var_name", "0123456789")){
	fprintf (stderr, "Function variable_update failed, line %d\n", __LINE__);
	return false;
    }

    char* value;
    value = variable_read("var_name");
    if (strcmp(value, "0123456789")){
	fprintf (stderr, "Function variable_read failed, line %d\n", __LINE__);
	return false;
    }

    if (!variable_destroy("var_name")){
	fprintf (stderr, "Function variable_destroy failed, line %d\n", __LINE__);
	return false;
    }

    if (variable_destroy("var_name")){
	fprintf (stderr, "Function variable_destroy failed, line %d\n", __LINE__);
	return false;
    }

    return true;
}
