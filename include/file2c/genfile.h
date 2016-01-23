#include <stdio.h>
#include <sys/types.h>

#ifndef _FILE2C_GENFILE_H
#define _FILE2C_GENFILE_H

char* hex2s(unsigned int i);
ssize_t copy_escaped(FILE* in, FILE* out);

#endif
