#include "vga.h"

void kmain(void);

void kmain(void) {
  Reset();
  print("Hello from the Kernel!!\r\n");
  print("I'm writing directly into video memory\r\n");
  print(":)\n");
}