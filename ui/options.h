/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "../base/newzpost.h"
#include "errors.h"

extern char *optarg;
extern int optind, opterr, optopt;
extern int errno;

extern boolean writedefaults;
extern const char *EDITOR;

/* public */

SList *parse_input_files(int argc, char **argv, int optind,
			 newzpost_data *data);

void parse_environment(newzpost_data *data);

void parse_defaults(newzpost_data *data);

boolean set_defaults(newzpost_data *data);

int parse_options(int argc, char **argv, newzpost_data *data);

void check_options(newzpost_data *data);

void print_help();

#endif /* __OPTIONS_H__ */
