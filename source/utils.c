

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zint.h>
#include "utils.h"
#include "variables.h"

bool utils_string_ends_with(char* str, char* substr){
    if (NULL == str || NULL == substr){
	return false;
    }

    if (strlen(substr) > strlen(str)){
	return false;
    }

    size_t start = strlen(str) - strlen(substr);
    if (!strcmp(str + start, substr)){
	return true;
    }

    return false;
}

bool utils_string_begins_with(char* str, char* substr){
    if (NULL == str || NULL == substr){
	return false;
    }

    if (strlen(substr) > strlen(str)){
	return false;
    }

    if (!strncmp(str, substr, strlen(substr))){
	return true;
    }

    return false;
}

char* utils_get_substring(char* input, uint16_t* start_pos, char separator){
    char* next_line = NULL;
    bool inside_quote = false;

    if (*start_pos >= strlen(input)){
	/* We have no more parameters to read. */
	return NULL;
    }

    /* Copy until separator or end-of-line. */
    uint16_t stop = *start_pos;
    while (input[stop] != separator &&
	   input[stop] != '\0' &&
	   input[stop] != '\n'){
	if (input[stop] == '\"'){
	    inside_quote = true;
	    stop++;
	}
	if (inside_quote){
	    while (input[stop] != '\"'){
		stop++;
		if (input[stop] == '\n' || input[stop] == '\0'){
		    fprintf (stderr, "Error: quotes not closed\n");
		    return NULL;
		}
	    }
	    inside_quote = false;
	}
	stop++;
    }

    next_line = calloc(stop - *start_pos, sizeof(char));
    if (NULL == next_line){
	return NULL;
    }
    strncpy(next_line, input + *start_pos, stop - *start_pos);
    *start_pos = stop + 1;
    return next_line;
}

uint32_t utils_get_substring_uint(char* line, uint16_t* start, char separator){
    char* substr = utils_get_substring(line, start, separator);
    utils_trim_string(substr);
    uint32_t value = atoi(substr);
    free(substr);
    return value;
}

/* Return a copy of the string without leading 
 * and trailing spaces and tabs 
 */
void utils_trim_string(char* input){
    /* Remove leading and trailing tabs & spaces */
    uint16_t start = 0;
    uint16_t stop = 0;
    
    while (input[start] == ' ' || input[start] == '\t' || input[start] == '\n' || input[start] == '\0'){
	start++;
    }
    stop = strlen(input) - 1;
    while (input[stop] == ' ' || input[stop] == '\t' || input[stop] == '\n' || input[stop] == '\0'){
	stop--;
    }

    stop++;
    uint16_t len = (stop - start) * sizeof(char);
    char* copy = malloc(len);
    strncpy(copy, input + start, len);
    if (len < strlen(input)){
	input = realloc(input, sizeof(char) * len + 1);
	if (NULL == input){
	    return;
	}
	strncpy(input, copy, strlen(copy) + 1);
	input[len] = '\0';
    }
}

void utils_append_string(char* original, char* append){
    size_t len = 0u;
    if (utils_text_is_quote(original)){
	len = strlen(original) + strlen(append) - 2;
	original = realloc(original, sizeof(char) * len);
	strncpy(original + strlen(original) - 1, append + 1, strlen(append));
    }else{
	len = strlen(original) + strlen(append);
	original = realloc(original, sizeof(char) * len);
	strncpy(original + strlen(original), append, strlen(append));
    }
    original[len] = '\0';
}

bool utils_text_is_quote(char* input){
    size_t len = strlen(input) - 1;
    return (input[0] == '\"' && input[len] == '\"');
}

/*
 * Copies the second given string into the position of the first given string.
 */
char* utils_insert_string(char* original, char* insert, uint32_t position){

    size_t len = 0u;
    len = strlen(original) + strlen(insert);
    size_t second_half_len = len - position;

    char* second_half = calloc(sizeof(char), second_half_len);
    if (NULL == second_half){
	return NULL;
    }
    strncpy(second_half, original + position, second_half_len);	

    original = realloc(original, sizeof(char) * len);
    if (NULL == original){
	free(second_half);
	return NULL;
    }

    if (utils_text_is_quote(insert)){
	strncpy(original + position, insert + 1, strlen(insert) - 2);
	strncpy(original + position + strlen(insert) - 2, second_half, strlen(second_half));
    }else{
	strncpy(original + position, insert, strlen(insert));
	strncpy(original + position + strlen(insert), second_half, strlen(second_half));
    }

    free(second_half);
    return original;
}

char* utils_update_string(char* text){
    char* value = NULL;
    if (variable_is_variable(text)){
	value = variable_read(text);
	utils_trim_string(value);
	if (utils_text_is_quote(value)){
	    size_t len = strlen(value);
	    strncpy(value, value + 1, strlen(value) - 2);
	    value[len-2] = '\0';
	}
	return value;
    }
    return text;
}

/* Based on the constants in zint.h, map name with id number */
static struct barcode_name_id{
    uint16_t id;
    char* name;
} all_barcode_types[] = {
    {BARCODE_CODE11          , "code11"},
    {BARCODE_C25STANDARD     , "c25standard"},
    {BARCODE_C25MATRIX       , "c25matrix"},
    {BARCODE_C25INTER        , "c25inter"},
    {BARCODE_C25IATA         , "c25iata"},
    {BARCODE_C25LOGIC        , "c25logic"},
    {BARCODE_C25IND          , "c25ind"},
    {BARCODE_CODE39          , "code39"},
    {BARCODE_EXCODE39        , "excode39"},
    {BARCODE_EANX            , "eanx"},
    {BARCODE_EANX_CHK        , "eanx_chk"},
    {BARCODE_GS1_128         , "gs1_128"},
    {BARCODE_EAN128          , "ean128"},
    {BARCODE_CODABAR         , "codabar"},
    {BARCODE_CODE128         , "code128"},
    {BARCODE_DPLEIT          , "dpleit"},
    {BARCODE_DPIDENT         , "dpident"},
    {BARCODE_CODE16K         , "code16k"},
    {BARCODE_CODE49          , "code49"},
    {BARCODE_CODE93          , "code93"},
    {BARCODE_FLAT            , "flat"},
    {BARCODE_DBAR_OMN        , "dbar_omn"},
    {BARCODE_RSS14           , "rss14"},
    {BARCODE_DBAR_LTD        , "dbar_ltd"},
    {BARCODE_RSS_LTD         , "rss_ltd"},
    {BARCODE_DBAR_EXP        , "dbar_exp"},
    {BARCODE_RSS_EXP         , "rss_exp"},
    {BARCODE_TELEPEN         , "telepen"},
    {BARCODE_UPCA            , "upca"},
    {BARCODE_UPCA_CHK        , "upca_chk"},
    {BARCODE_UPCE            , NULL},
    {BARCODE_UPCE_CHK        , NULL},
    {BARCODE_POSTNET         , NULL},
    {BARCODE_MSI_PLESSEY     , NULL},
    {BARCODE_FIM             , NULL},
    {BARCODE_LOGMARS         , NULL},
    {BARCODE_PHARMA          , NULL},
    {BARCODE_PZN             , NULL},
    {BARCODE_PHARMA_TWO      , NULL},
    {BARCODE_PDF417          , NULL},
    {BARCODE_PDF417COMP      , NULL},
    {BARCODE_PDF417TRUNC     , NULL},
    {BARCODE_MAXICODE        , NULL},
    {BARCODE_QRCODE          , NULL},
    {BARCODE_CODE128B        , NULL},
    {BARCODE_AUSPOST         , NULL},
    {BARCODE_AUSREPLY        , NULL},
    {BARCODE_AUSROUTE        , NULL},
    {BARCODE_AUSREDIRECT     , NULL},
    {BARCODE_ISBNX           , NULL},
    {BARCODE_RM4SCC          , NULL},
    {BARCODE_DATAMATRIX      , NULL},
    {BARCODE_EAN14           , NULL},
    {BARCODE_VIN             , NULL},
    {BARCODE_CODABLOCKF      , NULL},
    {BARCODE_NVE18           , NULL},
    {BARCODE_JAPANPOST       , NULL},
    {BARCODE_KOREAPOST       , NULL},
    {BARCODE_DBAR_STK        , NULL},
    {BARCODE_RSS14STACK      , NULL},
    {BARCODE_DBAR_OMNSTK     , NULL},
    {BARCODE_RSS14STACK_OMNI , NULL},
    {BARCODE_DBAR_EXPSTK     , NULL},
    {BARCODE_RSS_EXPSTACK    , NULL},
    {BARCODE_PLANET          , NULL},
    {BARCODE_MICROPDF417     , NULL},
    {BARCODE_USPS_IMAIL      , NULL},
    {BARCODE_ONECODE         , NULL},
    {BARCODE_PLESSEY         , NULL},
    {BARCODE_TELEPEN_NUM     , NULL},
    {BARCODE_ITF14           , NULL},
    {BARCODE_KIX             , NULL},
    {BARCODE_AZTEC           , NULL},
    {BARCODE_DAFT            , NULL},
    {BARCODE_DPD             , NULL},
    {BARCODE_MICROQR         , NULL},
    {BARCODE_HIBC_128        , NULL},
    {BARCODE_HIBC_39         , NULL},
    {BARCODE_HIBC_DM         , NULL},
    {BARCODE_HIBC_QR         , NULL},
    {BARCODE_HIBC_PDF        , NULL},
    {BARCODE_HIBC_MICPDF     , NULL},
    {BARCODE_HIBC_BLOCKF     , NULL},
    {BARCODE_HIBC_AZTEC      , NULL},
    {BARCODE_DOTCODE         , NULL},
    {BARCODE_HANXIN          , NULL},
    {BARCODE_MAILMARK        , NULL},
    {BARCODE_AZRUNE          , NULL},
    {BARCODE_CODE32          , NULL},
    {BARCODE_EANX_CC         , NULL},
    {BARCODE_GS1_128_CC      , NULL},
    {BARCODE_EAN128_CC       , NULL},
    {BARCODE_DBAR_OMN_CC     , NULL},
    {BARCODE_RSS14_CC        , NULL},
    {BARCODE_DBAR_LTD_CC     , NULL},
    {BARCODE_RSS_LTD_CC      , NULL},
    {BARCODE_DBAR_EXP_CC     , NULL},
    {BARCODE_RSS_EXP_CC      , NULL},
    {BARCODE_UPCA_CC         , NULL},
    {BARCODE_UPCE_CC         , NULL},
    {BARCODE_DBAR_STK_CC     , NULL},
    {BARCODE_RSS14STACK_CC   , NULL},
    {BARCODE_DBAR_OMNSTK_CC  , NULL},
    {BARCODE_RSS14_OMNI_CC   , NULL},
    {BARCODE_DBAR_EXPSTK_CC  , NULL},
    {BARCODE_RSS_EXPSTACK_CC , NULL},
    {BARCODE_CHANNEL         , NULL},
    {BARCODE_CODEONE         , NULL},
    {BARCODE_GRIDMATRIX      , NULL},
    {BARCODE_UPNQR           , NULL},
    {BARCODE_ULTRA           , NULL},
    {BARCODE_RMQR            , NULL},    
    {0, NULL},
};

uint16_t utils_get_barcode_id(char* barcode_type){
    uint8_t pos = 0;
    while (NULL != all_barcode_types[pos].name){
	if (!strcmp(all_barcode_types[pos].name, barcode_type)){
	    return all_barcode_types[pos].id;
	}
	pos++;
    }
    return 0;
}



