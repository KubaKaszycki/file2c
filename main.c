#include <config.h>
#include <main.h>
#include <settings.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <ctype.h>
#include <genfile.h>

static struct option LONG_OPTIONS[] = {
	{ "help", no_argument, NULL, 'h' },
	{ "version", no_argument, NULL, 'V' },
	{ "java", no_argument, NULL, 'j' },
	{ "java-decl", no_argument, NULL, 'J' },
	{ "variable", required_argument, NULL, 'v' },
	{ "file", required_argument, NULL, 'f' },
	{ "output", required_argument, NULL, 'o' },
	{ 0, 0, 0, 0 }
};

static void print_version() {
	printf("%s v%s\n", PACKAGE_NAME, PACKAGE_VERSION);
}

static void print_help() {
	print_version();
	printf("file2c - convert file to a C resource & more");
}

#define do_free(x) do { if(x != NULL) { free(x); x = NULL; } } while(0)

static void do_frees() {
	do_free(use_variable_name);
	do_free(file_name);
	do_free(outfile);
}

static void do_optparse(int argc, char** argv) {
	int ch;
	while((ch = getopt_long(argc, argv, "hVjJv:f:o:", LONG_OPTIONS, NULL)) != -1) {
		switch(ch) {
		case 'h':
			print_help();
			do_frees();
			exit(0);
			break;
		case 'V':
			print_version();
			do_frees();
			exit(0);
			break;
		case 'j':
			use_java_escapes = true;
			break;
		case 'J':
			use_java_escapes = true;
			use_java_decl = true;
			break;
		case 'v':
			do_free(use_variable_name);
			use_variable_name = strdup(optarg);
			break;
		case 'f':
			do_free(file_name);
			file_name = strdup(optarg);
			break;
		case 'o':
			do_free(outfile);
			outfile = strdup(optarg);
			break;
		}
	}
}

int main(int argc, char** argv) {
	return file2c_main(argc, argv);
}

int file2c_main(int argc, char** argv) {
	atexit(do_frees);
	do_optparse(argc, argv);
	if(file_name == NULL) {
		fprintf(stderr, "Error: required option -f not given\n");
		return 1;
	}
	if(use_variable_name == NULL) {
		use_variable_name = strdup(basename(file_name));
		const size_t len = strlen(use_variable_name);
		if(len > 0) {
			if(isalpha(use_variable_name[0]) || use_variable_name[0] == '_') {
				
			} else {
				use_variable_name[0] = '_';
			}
			for(size_t i = 1; i < len; i++) {
				if(isalnum(use_variable_name[i]) || use_variable_name[i] == '_') continue;
				use_variable_name[i] = '_';
			}
		}
	}
	if(outfile == NULL) {
		outfile = strdup("file2c.out");
	}
	FILE* in = fopen(file_name, "r");
	FILE* out = fopen(outfile, "w");
	if(use_java_decl) {
		fprintf(out, "final String %s = %c", use_variable_name, '"');
	} else {
		fprintf(out, "const char %s[] = %c", use_variable_name, '"');
	}
	copy_escaped(in, out);
	fprintf(out, "%c;", '"');
	fclose(in);
	fflush(out);
	fclose(out);
	return 0;
}
