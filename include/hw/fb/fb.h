#ifndef CRK_INCLUDE_HW_FB_FB_H
#define CRK_INCLUDE_HW_FB_FB_H

#include <stdint.h>

struct crk_framebuffer {
    volatile uint8_t *address;

    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint32_t bpp;

    uint8_t initialized;
};

/*
 * Initialize the framebuffer.
 *
 * address: Framebuffer memory address.
 * width:   Visible width in pixels.
 * height:  Visible height in pixels.
 * pitch:   Bytes per scanline.
 * bpp:     Bits per pixel (24 or 32).
 *
 * Returns 0 on success, -1 on failure.
 */
int crk_fb_init(uintptr_t address,
                uint32_t width,
                uint32_t height,
                uint32_t pitch,
                uint32_t bpp);

/* Write a pixel using a 0xAARRGGBB color value. */
void crk_fb_putpixel(uint32_t x, uint32_t y, uint32_t color);

/* Fill the entire framebuffer with a color. */
void crk_fb_clear(uint32_t color);

/* Return the framebuffer information. */
const struct crk_framebuffer *crk_fb_get_info(void);

#endif /* CRK_INCLUDE_HW_FB_FB_H */