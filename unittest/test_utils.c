

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "test_main.h"
#include "variables.h"

bool test_utils(void){
    if (utils_string_ends_with(NULL, NULL)){
	fprintf (stderr, "Function utils_string_ends_with failed, line %d\n", __LINE__);
	return false;
    }

    if (utils_string_ends_with("abc", NULL)){
	fprintf (stderr, "Function utils_string_ends_with failed, line %d\n", __LINE__);
	return false;
    }

    if (utils_string_ends_with(NULL, "abc")){
	fprintf (stderr, "Function utils_string_ends_with failed, line %d\n", __LINE__);
	return false;
    }

    if (!utils_string_ends_with("abcdef", "def")){
	fprintf (stderr, "Function utils_string_ends_with failed, line %d\n", __LINE__);
	return false;
    }

    if (utils_string_ends_with("abcdef", "ghi")){
	fprintf (stderr, "Function utils_string_ends_with failed, line %d\n", __LINE__);
	return false;
    }

    char* str = "abcdef";
    if (!utils_string_ends_with(str, "def")){
	fprintf (stderr, "Function utils_string_ends_with failed, line %d\n", __LINE__);
	return false;
    }

        if (utils_string_begins_with(NULL, NULL)){
	fprintf (stderr, "Function utils_string_begins_with failed, line %d\n", __LINE__);
	return false;
    }

    if (utils_string_begins_with("abc", NULL)){
	fprintf (stderr, "Function utils_string_begins_with failed, line %d\n", __LINE__);
	return false;
    }

    if (utils_string_begins_with(NULL, "abc")){
	fprintf (stderr, "Function utils_string_begins_with failed, line %d\n", __LINE__);
	return false;
    }

    if (!utils_string_begins_with("abcdef", "abc")){
	fprintf (stderr, "Function utils_string_begins_with failed, line %d\n", __LINE__);
	return false;
    }

    if (utils_string_begins_with("abcdef", "ghi")){
	fprintf (stderr, "Function utils_string_begins_with failed, line %d\n", __LINE__);
	return false;
    }

    uint16_t start_pos = 0;
    char* next_word = utils_get_substring("abc\ndef\nghi", &start_pos, '\n');
    if (NULL == next_word){
	fprintf (stderr, "Function utils_get_substring failed, line %d\n", __LINE__);
	return false;
    }
    if (strncmp(next_word, "abc", 3)){
	fprintf (stderr, "Function utils_get_substring failed, line %d\n", __LINE__);
	return false;
    }
    /* start_pos += strlen(next_word) + 1; */
    free(next_word);

    next_word = utils_get_substring("abc\ndef\nghi", &start_pos, '\n');
    if (NULL == next_word){
	fprintf (stderr, "Function utils_get_substring failed, line %d\n", __LINE__);
	return false;
    }
    if (strncmp(next_word, "def", 3)){
	fprintf (stderr, "Function utils_get_substring failed, line %d\n", __LINE__);
	return false;
    }
    free(next_word);

    next_word = malloc(19 * sizeof(char));
    strcpy(next_word, "         \t abc   \t");
    utils_trim_string(next_word);
    if (strlen(next_word) != 3){
	fprintf (stderr, "Function utils_trim_string failed, line %d\n", __LINE__);
	return false;
    }
    if (strncmp(next_word, "abc", 3)){
	fprintf (stderr, "Function utils_trim_string failed, line %d\n", __LINE__);
	return false;
    }
    free(next_word);

    start_pos = 4;
    uint16_t nr = utils_get_substring_uint("abc,56789,def,ghi", &start_pos, ',');
    if (56789UL != nr || 10 != start_pos){
	fprintf (stderr, "Function utils_get_int_string failed, line %d\n", __LINE__);
	return false;
    }
    nr = utils_get_substring_uint("abc,56789,def,ghi", &start_pos, ',');
    if (0UL != nr || 14 != start_pos){
	fprintf (stderr, "Function utils_get_int_string failed, line %d\n", __LINE__);
	return false;
    }


    str = malloc(7);
    strcpy(str, "abcdef");
    utils_append_string(str, "123456789");
    if (15 != strlen(str) || strcmp(str, "abcdef123456789")){
	fprintf (stderr, "Function utils_append_string failed, line %d\n", __LINE__);
	return false;
    }
    free(str);

    str = malloc(10);
    strcpy(str, "\"abcdef\"");
    utils_append_string(str, "\"123456789\"");
    if (17 != strlen(str) || strcmp(str, "\"abcdef123456789\"")){
	fprintf (stderr, "Function utils_apped_quote_string failed, line %d\n", __LINE__);
	return false;
    }
    free(str);

    char* str2 = malloc(27);
    if (NULL == str2){
	return false;
    }
    strcpy(str2, "abc,\"123,456,789\", defghi");
    start_pos = 0;
    next_word = utils_get_substring(str2, &start_pos, ',');
    if (strcmp(next_word, "abc")){
	fprintf (stderr, "Function utils_get_substring failed, line %d\n", __LINE__);
	return false;
    }
    free(next_word);
    next_word = utils_get_substring(str2, &start_pos, ',');
    if (strcmp(next_word, "\"123,456,789\"")){
	fprintf (stderr, "Function utils_get_substring failed, line %d\n", __LINE__);
	return false;
    }

    if (!utils_text_is_quote("\"abcdef\"")){
	fprintf (stderr, "Function utils_text_is_quote failed, line %d\n", __LINE__);
	return false;
    }

    if (utils_text_is_quote("\"abcdef\"ghi")){
	fprintf (stderr, "Function utils_text_is_quote failed, line %d\n", __LINE__);
	return false;
    }

    if (!variable_create("my_variable")){
	fprintf (stderr, "Function Error variable_create failed, line %d\n", __LINE__);
	return false;
    }
    if (!variable_update("my_variable", "\"This is a quote\"")){
	fprintf (stderr, "Function variable_update failed, line %d\n", __LINE__);
	return false;
    }
    
    char* value = utils_update_string("my_variable");
    if (strcmp(value, "This is a quote")){
	fprintf (stderr, "Function utils_update_string failed, line %d\n", __LINE__);
	return false;
    }
    free(value);

    if (13 != utils_get_barcode_id("eanx")){
	fprintf (stderr, "Function utils_get_barcode_id failed, line %d\n", __LINE__);
	return false;
    }
    return true;
}

