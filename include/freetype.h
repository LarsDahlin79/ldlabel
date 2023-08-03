

bool ft_init(void);
void ft_draw_string(char* bitmap, int x, int y, int width, 
		    int height, uint32_t red, uint32_t green, uint32_t blue,
		    char* str, int size, char* font);
bool ft_set_font(char* fontname);
