/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --stride 1 --align 1 --font FiraCode-Medium.ttf --range 32-127 --format lvgl -o fire_code_16.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef FIRE_CODE_16
#define FIRE_CODE_16 1
#endif

#if FIRE_CODE_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0x3c,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x33, 0x22, 0xff, 0x66, 0x66, 0x66, 0x66, 0xff,
    0x44, 0xcc, 0xcc,

    /* U+0024 "$" */
    0x10, 0x20, 0x43, 0xef, 0xfa, 0x34, 0x78, 0x78,
    0x38, 0x58, 0xb9, 0x7f, 0x9e, 0x8, 0x10, 0x20,

    /* U+0025 "%" */
    0x71, 0x6d, 0x37, 0x8e, 0x80, 0xc0, 0x40, 0x7c,
    0x3b, 0x3d, 0x96, 0xd9, 0xc0,

    /* U+0026 "&" */
    0x7c, 0x60, 0x30, 0x18, 0x3, 0xfb, 0x33, 0x19,
    0x8c, 0xc6, 0x33, 0xf, 0x0,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x8, 0xcc, 0xc6, 0x63, 0x18, 0xc6, 0x30, 0xc6,
    0x18, 0xc3,

    /* U+0029 ")" */
    0x86, 0x18, 0x63, 0xc, 0x63, 0x18, 0xc6, 0x63,
    0x31, 0x98,

    /* U+002A "*" */
    0x18, 0x18, 0x99, 0xff, 0x3c, 0x3c, 0x66, 0x66,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18,

    /* U+002C "," */
    0xff, 0xed, 0x0,

    /* U+002D "-" */
    0xfe,

    /* U+002E "." */
    0xff, 0x80,

    /* U+002F "/" */
    0x3, 0x2, 0x6, 0x4, 0xc, 0x8, 0x18, 0x18,
    0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0x0,

    /* U+0030 "0" */
    0x3c, 0x66, 0xc7, 0xcf, 0xcb, 0xdb, 0xd3, 0xd3,
    0xe3, 0x66, 0x3c,

    /* U+0031 "1" */
    0x38, 0xf3, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x33, 0xf8,

    /* U+0032 "2" */
    0x79, 0x9c, 0x18, 0x30, 0x61, 0x87, 0x1c, 0x70,
    0xc3, 0xf8,

    /* U+0033 "3" */
    0x7d, 0xc, 0x18, 0x33, 0x81, 0x81, 0x83, 0x7,
    0x19, 0xe0,

    /* U+0034 "4" */
    0x0, 0x18, 0x18, 0x30, 0x30, 0x26, 0x66, 0x66,
    0xff, 0x6, 0x6, 0x6,

    /* U+0035 "5" */
    0x7e, 0x60, 0x60, 0x60, 0x7e, 0x7, 0x3, 0x3,
    0x3, 0x46, 0x7c,

    /* U+0036 "6" */
    0x1e, 0x60, 0x60, 0xdc, 0xe6, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0037 "7" */
    0xfe, 0xc, 0x30, 0x60, 0x83, 0x6, 0x18, 0x30,
    0xc1, 0x80,

    /* U+0038 "8" */
    0x7c, 0xc6, 0xc6, 0xc6, 0x7c, 0x3c, 0xc6, 0xc3,
    0xc3, 0xe7, 0x3c,

    /* U+0039 "9" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0x67, 0x7b, 0x6,
    0x6, 0x1c, 0x78, 0x40,

    /* U+003A ":" */
    0xff, 0x80, 0x3f, 0xe0,

    /* U+003B ";" */
    0xff, 0x80, 0x3f, 0xfb, 0x40,

    /* U+003C "<" */
    0x4, 0x1c, 0xe3, 0x8c, 0x1c, 0x1c, 0xe, 0xe,
    0x0,

    /* U+003D "=" */
    0xfe, 0x0, 0x0, 0xf, 0xe0,

    /* U+003E ">" */
    0x41, 0xc0, 0xe0, 0xe0, 0x61, 0xc7, 0x38, 0xe0,
    0x0,

    /* U+003F "?" */
    0x7d, 0x8c, 0x18, 0x71, 0xc7, 0xc, 0x0, 0x0,
    0x60, 0xc0,

    /* U+0040 "@" */
    0x3c, 0x61, 0x80, 0xc0, 0x33, 0xda, 0x6f, 0x37,
    0x9b, 0xcd, 0xe6, 0xf3, 0x6e, 0xb0, 0x30,

    /* U+0041 "A" */
    0x1c, 0xe, 0x5, 0x82, 0xc3, 0x21, 0x98, 0x8c,
    0xfe, 0x61, 0xa0, 0xf0, 0x60,

    /* U+0042 "B" */
    0xf8, 0xc6, 0xc6, 0xc6, 0xc4, 0xf8, 0xc6, 0xc3,
    0xc3, 0xc7, 0xfc,

    /* U+0043 "C" */
    0x1f, 0x61, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0x60, 0x61, 0x1f,

    /* U+0044 "D" */
    0xf8, 0xc6, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc6, 0xc6, 0xf8,

    /* U+0045 "E" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0xf8,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0047 "G" */
    0x1e, 0x62, 0x60, 0xc0, 0xc0, 0xcf, 0xc3, 0xc3,
    0xc3, 0x63, 0x3e,

    /* U+0048 "H" */
    0xc7, 0x8f, 0x1e, 0x3f, 0xf8, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+0049 "I" */
    0xfe, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18, 0x30,
    0x63, 0xf8,

    /* U+004A "J" */
    0x3e, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x7,
    0x1b, 0xe0,

    /* U+004B "K" */
    0xc3, 0xc6, 0xcc, 0xd8, 0xd8, 0xf0, 0xd8, 0xcc,
    0xce, 0xc6, 0xc3,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0xf8,

    /* U+004D "M" */
    0xe7, 0xe7, 0xe7, 0xe7, 0xdb, 0xdb, 0xdb, 0xdb,
    0xdb, 0xc3, 0xc3,

    /* U+004E "N" */
    0xe3, 0xe3, 0xf3, 0xf3, 0xd3, 0xdb, 0xcb, 0xcf,
    0xcf, 0xc7, 0xc7,

    /* U+004F "O" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0050 "P" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc6, 0xfc, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x3c, 0x33, 0x30, 0x98, 0x6c, 0x36, 0x1b, 0xd,
    0x86, 0xc3, 0x33, 0xf, 0x0, 0x60, 0x38, 0x0,

    /* U+0052 "R" */
    0xfc, 0xc6, 0xc6, 0xc6, 0xc6, 0xf8, 0xd8, 0xcc,
    0xcc, 0xc6, 0xc6,

    /* U+0053 "S" */
    0x1f, 0x30, 0x98, 0xe, 0x7, 0xc0, 0xf8, 0x1e,
    0x3, 0x1, 0xb1, 0x9f, 0x80,

    /* U+0054 "T" */
    0xff, 0x86, 0x3, 0x1, 0x80, 0xc0, 0x60, 0x30,
    0x18, 0xc, 0x6, 0x3, 0x0,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0056 "V" */
    0xc1, 0xb0, 0xd8, 0x6c, 0x22, 0x31, 0x98, 0xc8,
    0x2c, 0x1e, 0xe, 0x3, 0x0,

    /* U+0057 "W" */
    0xc0, 0xf3, 0x2c, 0xcb, 0x36, 0x5d, 0x95, 0x65,
    0x79, 0xde, 0x73, 0x1c, 0xc7, 0x30,

    /* U+0058 "X" */
    0x61, 0x91, 0x8c, 0x83, 0xc1, 0xc0, 0xe0, 0x78,
    0x6c, 0x33, 0x31, 0x98, 0x60,

    /* U+0059 "Y" */
    0x61, 0x98, 0x63, 0x30, 0xcc, 0x1e, 0x7, 0x80,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0,

    /* U+005A "Z" */
    0x7f, 0x3, 0x6, 0xc, 0xc, 0x18, 0x18, 0x30,
    0x60, 0x60, 0xff,

    /* U+005B "[" */
    0xfe, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c,
    0x63, 0xe0,

    /* U+005C "\\" */
    0xc0, 0xc0, 0x60, 0x60, 0x20, 0x30, 0x10, 0x18,
    0x8, 0xc, 0xc, 0x6, 0x6, 0x3, 0x2,

    /* U+005D "]" */
    0xf8, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8f, 0xe0,

    /* U+005E "^" */
    0x18, 0x3c, 0x6c, 0x66, 0xc2,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0xc7, 0x0,

    /* U+0061 "a" */
    0x7c, 0x6, 0x6, 0x7e, 0xe6, 0xc6, 0xc6, 0xce,
    0x7a,

    /* U+0062 "b" */
    0x1, 0x83, 0x6, 0xf, 0xdd, 0xb1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x6f, 0x80,

    /* U+0063 "c" */
    0x3e, 0xc7, 0x6, 0xc, 0x18, 0x30, 0x31, 0x3e,

    /* U+0064 "d" */
    0x0, 0xc, 0x18, 0x33, 0xec, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1b, 0x77, 0xe0,

    /* U+0065 "e" */
    0x3c, 0x66, 0xc3, 0xc3, 0xff, 0xc0, 0xc0, 0x62,
    0x3e,

    /* U+0066 "f" */
    0x1f, 0x30, 0x30, 0x30, 0x30, 0xfe, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30,

    /* U+0067 "g" */
    0x0, 0x8f, 0xd8, 0x8c, 0x66, 0x33, 0x18, 0x78,
    0x40, 0x20, 0x1f, 0x80, 0x68, 0x36, 0x19, 0xf8,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xee, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x30,

    /* U+0069 "i" */
    0x0, 0x60, 0x0, 0x0, 0x1e, 0xc, 0x18, 0x30,
    0x60, 0xc1, 0x83, 0x1f, 0xc0,

    /* U+006A "j" */
    0x8, 0x70, 0x80, 0x3, 0xf0, 0xc3, 0xc, 0x30,
    0xc3, 0xc, 0x31, 0xbc, 0xc0,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc6, 0xcc, 0xd8, 0xd8,
    0xf8, 0xd8, 0xcc, 0xc6, 0xc7,

    /* U+006C "l" */
    0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0xf,

    /* U+006D "m" */
    0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    0xdb,

    /* U+006E "n" */
    0xdd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66,
    0x3c,

    /* U+0070 "p" */
    0xfd, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe6, 0xfd,
    0x83, 0x6, 0x0,

    /* U+0071 "q" */
    0x3e, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xb7, 0x7e,
    0xc, 0x18, 0x30,

    /* U+0072 "r" */
    0xee, 0xed, 0xdb, 0x6, 0xc, 0x18, 0x30, 0xf8,

    /* U+0073 "s" */
    0x7d, 0x83, 0x7, 0x87, 0xc1, 0xc1, 0xc3, 0xf8,

    /* U+0074 "t" */
    0x30, 0x30, 0xfe, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x1f,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0x7e,

    /* U+0076 "v" */
    0xc3, 0xc2, 0x46, 0x66, 0x64, 0x2c, 0x3c, 0x38,
    0x18,

    /* U+0077 "w" */
    0xc0, 0xe6, 0x53, 0x69, 0xb5, 0xdb, 0xad, 0xdc,
    0xe6, 0x33, 0x0,

    /* U+0078 "x" */
    0xc6, 0x66, 0x2c, 0x38, 0x18, 0x3c, 0x6c, 0x66,
    0xc3,

    /* U+0079 "y" */
    0xc3, 0xc2, 0x46, 0x66, 0x64, 0x2c, 0x2c, 0x38,
    0x38, 0x18, 0x30, 0x60, 0x40,

    /* U+007A "z" */
    0x7e, 0xc, 0x30, 0xc1, 0x86, 0x1c, 0x30, 0xfe,

    /* U+007B "{" */
    0x1c, 0xc3, 0xc, 0x30, 0xc3, 0x30, 0x30, 0xc3,
    0xc, 0x30, 0xc3, 0x7,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xc0, 0x82, 0x8, 0x21, 0x83, 0x7, 0x31, 0x82,
    0x8, 0x20, 0x82, 0x30,

    /* U+007E "~" */
    0x71, 0x93, 0x8e
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 154, .box_w = 2, .box_h = 11, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 154, .box_w = 5, .box_h = 4, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 7, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 154, .box_w = 7, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 34, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 154, .box_w = 2, .box_h = 4, .ofs_x = 4, .ofs_y = 9},
    {.bitmap_index = 61, .adv_w = 154, .box_w = 5, .box_h = 16, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 71, .adv_w = 154, .box_w = 5, .box_h = 16, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 81, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 89, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 97, .adv_w = 154, .box_w = 3, .box_h = 6, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 100, .adv_w = 154, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 101, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 118, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 226, .adv_w = 154, .box_w = 3, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 235, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 154, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 249, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 154, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 283, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 390, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 154, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 471, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 546, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 594, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 609, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 619, .adv_w = 154, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 624, .adv_w = 154, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 625, .adv_w = 154, .box_w = 4, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 627, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 668, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 154, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 706, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 154, .box_w = 7, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 730, .adv_w = 154, .box_w = 6, .box_h = 17, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 743, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 756, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 778, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 806, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 817, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 833, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 844, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 852, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 872, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 881, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 894, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 902, .adv_w = 154, .box_w = 6, .box_h = 16, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 914, .adv_w = 154, .box_w = 2, .box_h = 20, .ofs_x = 4, .ofs_y = -5},
    {.bitmap_index = 919, .adv_w = 154, .box_w = 6, .box_h = 16, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 931, .adv_w = 154, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t fire_code_16 = {
#else
lv_font_t fire_code_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if FIRE_CODE_16*/
