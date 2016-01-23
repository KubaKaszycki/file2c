#include <file2c/genfile.h>
#include <file2c/settings.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>

char* hex2s(unsigned int i) {
	if(i < 512) {
		char* buf = (char*) malloc(4);
		snprintf(buf, 4, "%03o", i);
		return buf;
	}
	int i1 = (i & 0x0000f000) >> 12;
	int i2 = (i & 0x00000f00) >> 8;
	int i3 = (i & 0x000000f0) >> 4;
	int i4 = (i & 0x0000000f);
	char* buf = (char*) malloc(6);
	snprintf(buf, 6, "u%hhx%hhx%hhx%hhx", i1, i2, i3, i4);
	return buf;
}

ssize_t copy_escaped(FILE* in, FILE* out) {
	char ch;
	size_t size = 1024;
	char* buf = (char*) malloc(size);
	char* hexstr;
	if(buf == NULL) {
		if(errno == ENOMEM) {
			size = 1;
			buf = &ch;
		} else {
			return -1;
		}
	}
	size_t copied = 0LL;
	while(!feof(in)) {
		size_t nchars = fread(buf, sizeof(char), size, in);
		for(size_t i = 0; i < nchars; i++) {
			if(isalnum(buf[i])) {
				putc(buf[i], out);
			} else {
				putc('\\', out);
				switch(buf[i]) {
				case '\n':
					putc('n', out);
					break;
				case '\r':
					putc('r', out);
					break;
				case '\b':
					putc('b', out);
					break;
				case '\f':
					putc('f', out);
					break;
				case '\t':
					putc('t', out);
					break;
				case '\'':
					putc('\'', out);
					break;
				case '"':
					putc('"', out);
					break;
				case '\a':
					if(!use_java_escapes) {
						putc('a', out);
					} else {
						hexstr = hex2s(buf[i]);
						fprintf(out, "%s", hexstr);
						free(hexstr);
					}
					break;
				case '\v':
					if(!use_java_escapes) {
						putc('v', out);
					} else {
						hexstr = hex2s(buf[i]);
						fprintf(out, "%s", hexstr);
						free(hexstr);
					}
					break;
				default:
					hexstr = hex2s(buf[i]);
					fprintf(out, "%s", hexstr);
					free(hexstr);
				}
			}
		}
		copied++;
	}
	return copied;
}
