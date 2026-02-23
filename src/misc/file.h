#ifndef FILE_IO_H
#define FILE_IO_H

#include "../core/world.h"

int read_legacy_file(World *w, char *path);
void write_file(char *path);

#endif
