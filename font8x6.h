const byte font6x8[][6] PROGMEM =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // Space
    { 0x00, 0x06, 0xDF, 0xDF, 0x06, 0x00 },   // !
    { 0x00, 0x0E, 0x00, 0x00, 0x0E, 0x00 },   // "
    { 0x24, 0x7e, 0x24, 0x24, 0x7e, 0x24 },   // #
    { 0x04, 0x4a, 0x4a, 0xcb, 0x4a, 0x30 },   // $
    { 0xc3, 0x23, 0x10, 0x08, 0xc4, 0xc3 },   // %
    { 0x6c, 0x92, 0xac, 0x40, 0xa0, 0x00 },   // &
    { 0x04, 0x03, 0x00, 0x00, 0x00, 0x00 },   // '
    { 0x00, 0x00, 0x7e, 0x81, 0x00, 0x00 },   // (
    { 0x00, 0x00, 0x81, 0x7e, 0x00, 0x00 },   // )
    { 0x00, 0x28, 0x1c, 0x1c, 0x28, 0x00 },   // *
    { 0x10, 0x10, 0x7c, 0x10, 0x10, 0x00 },   // +
    { 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00 },   // ,
    { 0x10, 0x10, 0x10, 0x10, 0x10, 0x00 },   // -
    { 0x00, 0x80, 0x00, 0x00, 0x00, 0x00 },   // .
    { 0x40, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x7c, 0xa2, 0x92, 0x8a, 0x7c, 0x00 },   // 0
    { 0x00, 0x84, 0xfe, 0x80, 0x00, 0x00 },   // 1
    { 0xc4, 0xa2, 0x92, 0x92, 0x8c, 0x00 },   // 2
    { 0x00, 0x82, 0x92, 0x92, 0x6c, 0x00 },   // 3
    { 0x1e, 0x10, 0x10, 0xfe, 0x10, 0x00 },   // 4
    { 0x9e, 0x92, 0x92, 0x92, 0x62, 0x00 },   // 5
    { 0x78, 0x94, 0x92, 0x92, 0x60, 0x00 },   // 6
    { 0x02, 0x22, 0xf2, 0x2a, 0x06, 0x00 },   // 7     Without strikethrough: { 0x02, 0x02, 0xf2, 0x0a, 0x06, 0x00 },
    { 0x6c, 0x92, 0x92, 0x92, 0x6c, 0x00 },   // 8
    { 0x0c, 0x92, 0x92, 0x52, 0x3c, 0x00 },   // 9
    { 0x00, 0x44, 0x00, 0x00, 0x00, 0x00 },   // :
    { 0x00, 0xc4, 0x00, 0x00, 0x00, 0x00 },   // ;
    { 0x00, 0x10, 0x28, 0x44, 0x82, 0x00 },   // <
    { 0x00, 0x28, 0x28, 0x28, 0x28, 0x00 },   // =
    { 0x00, 0x82, 0x44, 0x28, 0x10, 0x00 },   // >
    { 0x04, 0xa2, 0x12, 0x0c, 0x00, 0x00 },   // ?
    { 0x7c, 0x82, 0xba, 0xaa, 0x7c, 0x00 },   // @
    { 0xfc, 0x12, 0x12, 0x12, 0xfc, 0x00 },   // A
    { 0xfe, 0x92, 0x92, 0x92, 0x7c, 0x00 },   // B
    { 0x7c, 0x82, 0x82, 0x82, 0x44, 0x00 },   // C
    { 0xfe, 0x82, 0x82, 0x82, 0x7c, 0x00 },   // D
    { 0xfe, 0x92, 0x92, 0x92, 0x00, 0x00 },   // E
    { 0xfe, 0x12, 0x12, 0x12, 0x00, 0x00 },   // F
    { 0x7c, 0x82, 0xa2, 0xa2, 0xe2, 0x00 },   // G
    { 0xfe, 0x10, 0x10, 0x10, 0xfe, 0x00 },   // H
    { 0x82, 0x82, 0xfe, 0x82, 0x82, 0x00 },   // I
    { 0x40, 0x82, 0x82, 0x7e, 0x02, 0x00 },   // J
    { 0xfe, 0x10, 0x28, 0x44, 0x82, 0x00 },   // K
    { 0xfe, 0x80, 0x80, 0x80, 0x00, 0x00 },   // L
    { 0xfe, 0x04, 0x08, 0x04, 0xfe, 0x00 },   // M
    { 0xfe, 0x04, 0x18, 0x20, 0xfe, 0x00 },   // N
    { 0x7c, 0x82, 0x82, 0x82, 0x7c, 0x00 },   // O
    { 0xfe, 0x12, 0x12, 0x12, 0x0c, 0x00 },   // P
    { 0x7c, 0x82, 0x82, 0x42, 0xbc, 0x00 },   // Q
    { 0xfe, 0x12, 0x32, 0xd2, 0x0c, 0x00 },   // R
    { 0x4c, 0x92, 0x92, 0x92, 0x64, 0x00 },   // S
    { 0x02, 0x02, 0xfe, 0x02, 0x02, 0x00 },   // T
    { 0x7e, 0x80, 0x80, 0x80, 0x7e, 0x00 },   // U
    { 0x3e, 0x40, 0x80, 0x40, 0x3e, 0x00 },   // V
    { 0x7e, 0x80, 0x60, 0x80, 0x7e, 0x00 },   // W
    { 0xc6, 0x28, 0x10, 0x28, 0xc6, 0x00 },   // X
    { 0x06, 0x08, 0xf0, 0x08, 0x06, 0x00 },   // Y
    { 0xc2, 0xa2, 0x92, 0x8a, 0x86, 0x00 },   // Z
    { 0xfe, 0x82, 0x82, 0x00, 0x00, 0x00 },   // [
    { 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 },   // Backslash
    { 0x00, 0x00, 0x00, 0x82, 0x82, 0xfe },   // ]
    { 0x08, 0x04, 0x02, 0x04, 0x08, 0x00 },   // ^
    { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 },   // _
    { 0x00, 0x02, 0x04, 0x08, 0x00, 0x00 },   // `
    { 0x60, 0x90, 0x90, 0x70, 0x80, 0x00 },   // a
    { 0xfe, 0x90, 0x90, 0x60, 0x00, 0x00 },   // b
    { 0x60, 0x90, 0x90, 0x00, 0x00, 0x00 },   // c
    { 0x60, 0x90, 0x90, 0xfe, 0x00, 0x00 },   // d
    { 0x70, 0xa8, 0xa8, 0x30, 0x00, 0x00 },   // e
    { 0x20, 0xf8, 0x24, 0x08, 0x00, 0x00 },   // f
    { 0x18, 0xa4, 0xa4, 0x7c, 0x00, 0x00 },   // g
    { 0xfe, 0x10, 0x10, 0xe0, 0x00, 0x00 },   // h
    { 0x00, 0x00, 0xe8, 0x00, 0x00, 0x00 },   // i
    { 0x40, 0x80, 0x74, 0x00, 0x00, 0x00 },   // j
    { 0xfc, 0x20, 0xd0, 0x00, 0x00, 0x00 },   // k
    { 0x00, 0x78, 0x80, 0x00, 0x00, 0x00 },   // l
    { 0xf8, 0x08, 0x10, 0x08, 0xf0, 0x00 },   // m
    { 0xf0, 0x10, 0x10, 0xe0, 0x00, 0x00 },   // n
    { 0x60, 0x90, 0x90, 0x60, 0x00, 0x00 },   // o
    { 0xf0, 0x28, 0x28, 0x10, 0x00, 0x00 },   // p
    { 0x10, 0x28, 0x28, 0xf0, 0x00, 0x00 },   // q
    { 0x00, 0xf8, 0x08, 0x00, 0x00, 0x00 },   // r
    { 0x10, 0xa8, 0xa8, 0x40, 0x00, 0x00 },   // s
    { 0x10, 0xf8, 0x10, 0x00, 0x00, 0x00 },   // t
    { 0x70, 0x80, 0x80, 0xf0, 0x00, 0x00 },   // u
    { 0x70, 0x80, 0x80, 0x70, 0x00, 0x00 },   // v
    { 0x70, 0x80, 0x40, 0x80, 0x70, 0x00 },   // w
    { 0xd8, 0x20, 0x20, 0xd8, 0x00, 0x00 },   // x
    { 0x98, 0x60, 0x18, 0x00, 0x00, 0x00 },   // y
    { 0xc8, 0xa8, 0xa8, 0x98, 0x00, 0x00 },   // z
};