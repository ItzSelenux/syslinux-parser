#ifndef SYSLINUX_PARSER_H
#define SYSLINUX_PARSER_H

#define MAX_ENTRIES 16
#define MAX_LINE_LENGTH 512

struct SYSLINUX_ENTRY
{
	char label[MAX_LINE_LENGTH];
	char menulabel[MAX_LINE_LENGTH];
	char command[MAX_LINE_LENGTH];
	char append[MAX_LINE_LENGTH];
	char com32[MAX_LINE_LENGTH];
	char initrd[MAX_LINE_LENGTH];
};

extern unsigned int entry_count;
extern char SYSLINUX_CONF_DEFAULT[MAX_LINE_LENGTH];
extern char SYSLINUX_CONF_PROMPT[MAX_LINE_LENGTH];
extern char SYSLINUX_CONF_TIMEOUT[MAX_LINE_LENGTH];
extern char SYSLINUX_CONF_UI[MAX_LINE_LENGTH];

int parse_syslinux_config(const char *filename, struct SYSLINUX_ENTRY *entries);

#endif
