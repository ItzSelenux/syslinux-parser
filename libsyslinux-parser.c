#include "libsyslinux-parser.h"
#include <stdio.h>
#include <string.h>

unsigned int entry_count;

char SYSLINUX_CONF_DEFAULT[MAX_LINE_LENGTH];
char SYSLINUX_CONF_PROMPT[MAX_LINE_LENGTH];
char SYSLINUX_CONF_TIMEOUT[MAX_LINE_LENGTH];
char SYSLINUX_CONF_UI[MAX_LINE_LENGTH];

int parse_syslinux_config(const char *filename, struct SYSLINUX_ENTRY *entries)
{
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		return 1;
	}

	char line[MAX_LINE_LENGTH];

	while (fgets(line, sizeof(line), file))
	{
		int i = 0;
		while (line[i] == ' ' || line[i] == '\t')
		{
			i++;
		}
		char *trimmed_line = line + i;
		size_t len = strlen(trimmed_line);

		if (len > 0 && trimmed_line[len - 1] == '\n')
		{
			trimmed_line[len - 1] = '\0';
			len--;
		}

		//SYSLINUX CONFIG
		if (strncmp(trimmed_line, "DEFAULT ", 8) == 0)
		{
			strncpy(SYSLINUX_CONF_DEFAULT, trimmed_line + 8, len);
			SYSLINUX_CONF_DEFAULT[len] = '\0';
		}
		else if (strncmp(trimmed_line, "PROMPT ", 7) == 0)
		{
			strncpy(SYSLINUX_CONF_PROMPT, trimmed_line + 7, len);
			SYSLINUX_CONF_PROMPT[len] = '\0';
		}
		else if (strncmp(trimmed_line, "TIMEOUT ", 8) == 0)
		{
			strncpy(SYSLINUX_CONF_TIMEOUT, trimmed_line + 8, len);
			SYSLINUX_CONF_TIMEOUT[len] = '\0';
		}
		else if (strncmp(trimmed_line, "UI ", 3) == 0)
		{
			strncpy(SYSLINUX_CONF_UI, trimmed_line + 3, len);
			SYSLINUX_CONF_UI[len] = '\0';
		}

		//SYSLINUX ENTRIES
		if (strncmp(trimmed_line, "LABEL ", 6) == 0)
		{
			strncpy(entries[entry_count].label, trimmed_line + 6, len);
			entries[entry_count].label[len] = '\0';
			entry_count++;
		}
		else if (strncmp(trimmed_line, "MENU LABEL ", 11) == 0)
		{
			strncpy(entries[entry_count - 1].menulabel, trimmed_line + 11, len);
			entries[entry_count - 1].menulabel[len] = '\0';
		}
		else if (strncmp(trimmed_line, "LINUX ", 6) == 0)
		{
			strncpy(entries[entry_count - 1].command, trimmed_line + 6, len);
			entries[entry_count - 1].command[len] = '\0';
		}
		else if (strncmp(trimmed_line, "APPEND ", 7) == 0)
		{
			strncpy(entries[entry_count - 1].append, trimmed_line + 7, len);
			entries[entry_count - 1].append[len] = '\0';
		}
		else if (strncmp(trimmed_line, "COM32 ", 6) == 0)
		{
			strncpy(entries[entry_count - 1].com32, trimmed_line + 6, len);
			entries[entry_count - 1].com32[len] = '\0';
		}
		else if (strncmp(trimmed_line, "INITRD ", 7) == 0)
		{
			strncpy(entries[entry_count - 1].initrd, trimmed_line + 7, len);
			entries[entry_count - 1].initrd[len] = '\0';
		}
	}
	fclose(file);
	return 0;
}
