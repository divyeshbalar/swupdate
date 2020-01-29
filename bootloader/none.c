/*
 * (C) Copyright 2017
 * Stefano Babic, DENX Software Engineering, sbabic@denx.de.
 *
 * SPDX-License-Identifier:     GPL-2.0-or-later
 */

#include <unistd.h>
#include <string.h>
#include "bootloader.h"
#include "swupdate_dict.h"

static struct dict environment;

int bootloader_env_set(const char __attribute__ ((__unused__)) *name,
			const char __attribute__ ((__unused__)) *value)
{
	dict_set_value(&environment, name, value);

	return 0;
}

int bootloader_env_unset(const char *name)
{
	dict_remove(&environment, name);

	return 0;
}

char *bootloader_env_get(const char __attribute__ ((__unused__)) *name)
{
	char *value = NULL, *var;

	var = dict_get_value(&environment, name);

	if (var)
		value = strdup(var);

	return value;
}

int bootloader_apply_list(const char *filename)
{
	return dict_parse_script(&environment, filename);
}
