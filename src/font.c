#include <SDL_ttf.h>
#include "simple_logger.h"

#include "gfc_list.h"
#include "gf2d_graphics.h"
#include "font.h"

typedef struct
{
	List* fonts;
}FontManager;

static FontManager font_manager = { 0 };

void font_close()
{
	TTF_Font* font;
	int i, c;
	c = gfc_list_get_count(font_manager.fonts);
	for (i = 0; i < c; i++)
	{
		font = gfc_list_get_nth(font_manager.fonts, i);
		if (!font)continue;
		TTF_CloseFont(font);
	}
	gfc_list_delete(font_manager.fonts);
	memset(&font_manager, 0, sizeof(FontManager));
	TTF_Quit();
}

void font_init()
{
	int i;
	TTF_Font* font;
	if (TTF_Init() != 0)
	{
		slog("Failed to initialize TTF system");
		return;
	}
	font_manager.fonts = gfc_list_new();
	for ( i = 0; i < FS_MAX; i++)
	{
		font = TTF_OpenFont("fonts/Cascade Free.otf", 20 + (i + 4));
		if (!font)
		{
			slog("Faield to open font");
			continue;
		}
		gfc_list_append(font_manager.fonts, font);
	}
	atexit(font_close);
}

void font_draw_test(const char* text, FontStyles style, Color color, Vector2D position)
{
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Color fg;
	SDL_Rect rect;
	font = gfc_list_get_nth(font_manager.fonts, style);
	if (!font)
	{
		slog("Faield to render '%s', missing font style %i", text, style);
		return;
	}
	fg = gfc_color_to_sdl(color);
	surface = TTF_RenderUTF8_Blended_Wrapped(font,text,fg,0);
	surface = gf2d_graphics_screen_convert(&surface);
	texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), surface);
	if (!texture)
	{
		SDL_FreeSurface(surface);
		return;
	}
	rect.x = position.x;
	rect.y = position.y;
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_RenderCopy(gf2d_graphics_get_renderer(),
		texture,
		NULL,
		&rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}