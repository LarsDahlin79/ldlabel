


bool graphics_create(char* filename, uint16_t width, uint16_t height, uint8_t resolution);
bool graphics_set_pixel(char* filename, uint32_t xpos, uint32_t ypos,
			uint32_t red, uint32_t green, uint32_t blue,
			uint32_t alpha);
bool graphics_draw_square(char* filename, uint32_t x1, uint32_t y1,
			  uint32_t x2, uint32_t y2,
			  uint32_t red, uint32_t green, uint32_t blue,
			  uint32_t alpha);
bool graphics_draw_line(char* filename, uint32_t x1, uint32_t y1,
			uint32_t x2, uint32_t y2,
			uint32_t red, uint32_t green, uint32_t blue,
			uint32_t alpha);
bool graphics_save_file(char* filename);
bool graphics_destroy(char* filename);
bool graphics_fill_image(char* filename, uint32_t red, uint32_t green,
			 uint32_t blue, uint32_t alpha);
bool graphics_text(char* filename, char* text, uint16_t xpos,
		   uint16_t ypos, uint32_t red, uint32_t green,
		   uint32_t blue, uint32_t alpha,
		   char* font);
bool graphics_draw_barcode(char* filename, uint16_t type, char* data,
			   uint16_t xpos, uint16_t ypos,
			   uint32_t red, uint32_t green, uint32_t blue,
			   uint32_t alpha);
