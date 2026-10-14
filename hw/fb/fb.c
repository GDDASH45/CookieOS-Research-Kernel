#include <stdint.h>
#include <stddef.h>

#include <hw/fb/fb.h>

static struct crk_framebuffer crk_fb;

int crk_fb_init(uintptr_t address,
                uint32_t width,
                uint32_t height,
                uint32_t pitch,
                uint32_t bpp)
{
    if (address == 0 || width == 0 || height == 0)
        return -1;

    if (bpp != 24 && bpp != 32)
        return -1;

    if (pitch < width * (bpp / 8))
        return -1;

    crk_fb.address = (volatile uint8_t *)address;
    crk_fb.width = width;
    crk_fb.height = height;
    crk_fb.pitch = pitch;
    crk_fb.bpp = bpp;
    crk_fb.initialized = 1;

    return 0;
}

void crk_fb_putpixel(uint32_t x, uint32_t y, uint32_t color)
{
    if (!crk_fb.initialized)
        return;

    if (x >= crk_fb.width || y >= crk_fb.height)
        return;

    uint32_t bytes_per_pixel = crk_fb.bpp / 8;
    volatile uint8_t *pixel =
        crk_fb.address + (size_t)y * crk_fb.pitch
        + (size_t)x * bytes_per_pixel;

    pixel[0] = (uint8_t)(color & 0xFF);
    pixel[1] = (uint8_t)((color >> 8) & 0xFF);
    pixel[2] = (uint8_t)((color >> 16) & 0xFF);

    if (bytes_per_pixel == 4)
        pixel[3] = (uint8_t)((color >> 24) & 0xFF);
}

void crk_fb_clear(uint32_t color)
{
    if (!crk_fb.initialized)
        return;

    for (uint32_t y = 0; y < crk_fb.height; y++) {
        for (uint32_t x = 0; x < crk_fb.width; x++) {
            crk_fb_putpixel(x, y, color);
        }
    }
}

const struct crk_framebuffer *crk_fb_get_info(void)
{
    return &crk_fb;
}