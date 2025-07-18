#include "vga.h"

uint16_t column = 0;
uint16_t line = 0;

uint16_t* vga = (uint16_t* const)0xB8000;
const uint16_t defaultColor = (COLORS_LIGHT_GREY << 8) | (COLORS_BLACK << 12);
uint16_t currentColor = defaultColor;

void Reset() {
  line = 0;
  column = 0;
  currentColor = defaultColor;

  for (uint16_t y = 0; y < height; y++) {
    for (uint16_t x = 0; x < width; x++) {
      vga[y * width + x] = ' ' | defaultColor;
    }
  }
}

void newLine() {
  if (line < height - 1) {
    line++;
    column = 0;
  } else {
    scrollUp();
    column = 0;
  }
}

void scrollUp() {
  for (uint16_t y = 0; y < height; y++) {
    for (uint16_t x = 0; x < width; x++) {
      vga[(y - 1) * width + x] = vga[y * width + x];
    }
  }

  for (uint16_t x = 0; x < width; x++) {
    vga[(height - 1) * width + x] = ' ' | currentColor;
  }
}

void print(const char* s) {
  while (*s) {
    switch (*s) {
      case '\n':
        newLine();
        break;
      case '\r':
        column = 0;
        break;
      case '\t':
        if (column == width) {
          newLine();
        }
        uint16_t tablen = 4 - (column % 4);
        while (tablen != 0) {
          vga[line * width + column++] = ' ' | currentColor;
          tablen--;
        }
        break;
      default:
        if (column == width) {
          newLine();
        }
        vga[line * width + (column++)] = *s | currentColor;
        break;
    }
    s++;
  }
}


// Print a 32-bit value as 8 hex digits (no prefix)
void print_hex(uint32_t value) {
  char buf[9];
  for (int i = 0; i < 8; i++) {
      uint8_t nibble = (value >> (28 - i*4)) & 0xF;
      buf[i] = nibble < 10 ? '0' + nibble : 'A' + (nibble - 10);
  }
  buf[8] = '\0';
  print(buf);
}