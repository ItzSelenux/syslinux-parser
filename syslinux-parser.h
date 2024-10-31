#ifndef SYSLINUX_PARSER_H
#define SYSLINUX_PARSER_H

#include <stdio.h>
#include <string.h>

#define MAX_ENTRIES 65536
#define ML 512
#define MAX_TOKEN_SIZE 40
unsigned int entry_count;
struct SYSLINUX_ENTRY
{
	char label[ML];
	char menulabel[ML];
	char command[ML];
	char append[ML];
	char com32[ML];
	char initrd[ML];
};

char SYSLINUX_CONF_DEFAULT[ML], SYSLINUX_CONF_PROMPT[ML],
	SYSLINUX_CONF_TIMEOUT[ML], SYSLINUX_CONF_UI[ML], 
	SYSLINUX_CONF_BACKGROUND[ML], SYSLINUX_CONF_TITLE[ML],

	SYSLINUX_COLOR_SCREEN[ML], SYSLINUX_COLOR_BORDER[ML],
	SYSLINUX_COLOR_TITLE[ML], SYSLINUX_COLOR_SEL[ML],
	SYSLINUX_COLOR_UNSEL[ML], SYSLINUX_COLOR_HELP[ML],
	SYSLINUX_COLOR_TIMEOUT_MSG[ML], SYSLINUX_COLOR_TIMEOUT[ML],
	SYSLINUX_COLOR_TABMSG[ML],

	SYSLINUX_COLOR_SCREEN_OLDMENU[ML], SYSLINUX_COLOR_BORDER_OLDMENU[ML],
	SYSLINUX_COLOR_TITLE_OLDMENU[ML], SYSLINUX_COLOR_SEL_OLDMENU[ML],
	SYSLINUX_COLOR_UNSEL_OLDMENU[ML], SYSLINUX_COLOR_HELP_OLDMENU[ML],
	SYSLINUX_COLOR_TIMEOUT_MSG_OLDMENU[ML], SYSLINUX_COLOR_TIMEOUT_OLDMENU[ML],
	SYSLINUX_COLOR_TABMSG_OLDMENU[ML],

	SYSLINUX_COLOR_SCREEN_VESAMENU[ML], SYSLINUX_COLOR_BORDER_VESAMENU[ML],
	SYSLINUX_COLOR_TITLE_VESAMENU[ML], SYSLINUX_COLOR_SEL_VESAMENU[ML],
	SYSLINUX_COLOR_UNSEL_VESAMENU[ML], SYSLINUX_COLOR_HELP_VESAMENU[ML],
	SYSLINUX_COLOR_TIMEOUT_MSG_VESAMENU[ML], SYSLINUX_COLOR_TIMEOUT_VESAMENU[ML],
	SYSLINUX_COLOR_TABMSG_VESAMENU[ML],

	SYSLINUX_COLOR_SCREEN_SHADOW[ML], SYSLINUX_COLOR_BORDER_SHADOW[ML],
	SYSLINUX_COLOR_TITLE_SHADOW[ML], SYSLINUX_COLOR_SEL_SHADOW[ML],
	SYSLINUX_COLOR_UNSEL_SHADOW[ML], SYSLINUX_COLOR_HELP_SHADOW[ML],
	SYSLINUX_COLOR_TIMEOUT_MSG_SHADOW[ML], SYSLINUX_COLOR_TIMEOUT_SHADOW[ML],
	SYSLINUX_COLOR_TABMSG_SHADOW[ML];

void parse_syslinux_line(char *line)
{
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '\t')
		{
			line[i] = ' ';
		}
	}
}

int parse_syslinux_color_entry(char INPUT[ML], char OUTPUT_OLDMENU[ML],
	char OUTPUT_VESAMENU[ML],char OUTPUT_SHADOW[ML])
{
	char tmpvesa2[MAX_TOKEN_SIZE]; 
	int step = 0;

	OUTPUT_OLDMENU[0] = '\0';
	OUTPUT_VESAMENU[0] = '\0';
	OUTPUT_SHADOW[0] = '\0';

	char *token = strtok(INPUT, " ");

	while (token != NULL)
	{
		if (step == 0)
		{
			strncpy(OUTPUT_OLDMENU, token, ML - 1);
			OUTPUT_OLDMENU[ML - 1] = '\0';
		} 
		else if (step == 1)
		{
			strncpy(OUTPUT_VESAMENU, token, ML - 1);
			OUTPUT_VESAMENU[ML - 1] = '\0';
		} 
		else if (step == 2)
		{
			strncpy(tmpvesa2, token, sizeof(tmpvesa2) - 1);
			tmpvesa2[sizeof(tmpvesa2) - 1] = '\0';
		} 
		else if (step == 3)
		{
			strncpy(OUTPUT_SHADOW, token, ML - 1);
			OUTPUT_SHADOW[ML - 1] = '\0';
		}
		step++;
		token = strtok(NULL, " ");
	}

	strncat(OUTPUT_VESAMENU, " ", ML - strlen(OUTPUT_VESAMENU) - 1);
	strncat(OUTPUT_VESAMENU, tmpvesa2, ML - strlen(OUTPUT_VESAMENU) - 1);

	return step;
}

int parse_syslinux_config(const char *filename, struct SYSLINUX_ENTRY *entries)
{
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		return 1;
	}

	char line[ML];

	while (fgets(line, sizeof(line), file))
	{
		int i = 0;
		while (line[i] == ' ' || line[i] == '\t')
		{
			i++;
		}
		char *trimmed_line = line + i;
		size_t len = strlen(trimmed_line);

		for (int i = 0; trimmed_line[i] != '\0'; i++)
		{
			if (trimmed_line[i] == '\t')
			{
				trimmed_line[i] = ' ';
			}
		}

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
		else if (strncmp(trimmed_line, "MENU TITLE ", 11) == 0)
		{
			strncpy(SYSLINUX_CONF_TITLE, trimmed_line + 11, len);
			SYSLINUX_CONF_TITLE[len] = '\0';
		}
		else if (strncmp(trimmed_line, "MENU BACKGROUND ", 16) == 0)
		{
			strncpy(SYSLINUX_CONF_UI, trimmed_line + 16, len);
			SYSLINUX_CONF_UI[len] = '\0';
		}
		//SYSLINUX COLORS 
		else if (strncmp(trimmed_line, "MENU COLOR border ", 18) == 0)
		{
			strncpy(SYSLINUX_COLOR_BORDER, trimmed_line + 18, len);
			SYSLINUX_COLOR_BORDER[len] = '\0';
			parse_syslinux_color_entry(SYSLINUX_COLOR_BORDER, SYSLINUX_COLOR_BORDER_OLDMENU, SYSLINUX_COLOR_BORDER_VESAMENU, SYSLINUX_COLOR_BORDER_SHADOW);
		}
		else if (strncmp(trimmed_line, "MENU COLOR screen ", 18) == 0)
		{
			strncpy(SYSLINUX_COLOR_SCREEN, trimmed_line + 18, len);
			SYSLINUX_COLOR_SCREEN[len] = '\0';
			parse_syslinux_color_entry(SYSLINUX_COLOR_SCREEN, SYSLINUX_COLOR_SCREEN_OLDMENU, SYSLINUX_COLOR_SCREEN_VESAMENU, SYSLINUX_COLOR_SCREEN_SHADOW);
		}
		else if (strncmp(trimmed_line, "MENU COLOR title ", 17) == 0)
		{
			strncpy(SYSLINUX_COLOR_TITLE, trimmed_line + 17, len);
			SYSLINUX_COLOR_TITLE[len] = '\0';
			parse_syslinux_color_entry(SYSLINUX_COLOR_TITLE, SYSLINUX_COLOR_TITLE_OLDMENU, SYSLINUX_COLOR_TITLE_VESAMENU, SYSLINUX_COLOR_TITLE_SHADOW);
		}
		else if (strncmp(trimmed_line, "MENU COLOR sel ", 15) == 0)
		{
			strncpy(SYSLINUX_COLOR_SEL, trimmed_line + 15, len);
			SYSLINUX_COLOR_SEL[len] = '\0';
			parse_syslinux_color_entry(SYSLINUX_COLOR_SEL, SYSLINUX_COLOR_SEL_OLDMENU, SYSLINUX_COLOR_SEL_VESAMENU, SYSLINUX_COLOR_SEL_SHADOW); // Added function call
		}
		else if (strncmp(trimmed_line, "MENU COLOR unsel ", 17) == 0)
		{
			strncpy(SYSLINUX_COLOR_UNSEL, trimmed_line + 17, len);
			SYSLINUX_COLOR_UNSEL[len] = '\0';
			parse_syslinux_color_entry(SYSLINUX_COLOR_UNSEL, SYSLINUX_COLOR_UNSEL_OLDMENU, SYSLINUX_COLOR_UNSEL_VESAMENU, SYSLINUX_COLOR_UNSEL_SHADOW); // Added function call
		}
		else if (strncmp(trimmed_line, "MENU COLOR help ", 16) == 0)
		{
			strncpy(SYSLINUX_COLOR_HELP, trimmed_line + 16, len);
			SYSLINUX_COLOR_HELP[len] = '\0';
			parse_syslinux_color_entry(SYSLINUX_COLOR_HELP, SYSLINUX_COLOR_HELP_OLDMENU, SYSLINUX_COLOR_HELP_VESAMENU, SYSLINUX_COLOR_HELP_SHADOW); // Added function call
		}
		else if (strncmp(trimmed_line, "MENU COLOR timeout_msg ", 23) == 0)
		{
			strncpy(SYSLINUX_COLOR_TIMEOUT_MSG, trimmed_line + 23, len);
			SYSLINUX_COLOR_TIMEOUT_MSG[len] = '\0';
			parse_syslinux_color_entry(SYSLINUX_COLOR_TIMEOUT_MSG, SYSLINUX_COLOR_TIMEOUT_MSG_OLDMENU, SYSLINUX_COLOR_TIMEOUT_MSG_VESAMENU, SYSLINUX_COLOR_TIMEOUT_MSG_SHADOW); // Added function call
		}
		else if (strncmp(trimmed_line, "MENU COLOR timeout ", 19) == 0)
		{
			strncpy(SYSLINUX_COLOR_TIMEOUT, trimmed_line + 19, len);
			SYSLINUX_COLOR_TIMEOUT[len] = '\0';
			parse_syslinux_color_entry(SYSLINUX_COLOR_TIMEOUT, SYSLINUX_COLOR_TIMEOUT_OLDMENU, SYSLINUX_COLOR_TIMEOUT_VESAMENU, SYSLINUX_COLOR_TIMEOUT_SHADOW); // Added function call
		}
		//else if (strncmp(trimmed_line, "MENU COLOR msg07 ", 17) == 0)
		//{
		//    strncpy(SYSLINUX_COLOR_MSG07, trimmed_line + 17, len);
		//    SYSLINUX_COLOR_MSG07[len] = '\0';
		//}
		else if (strncmp(trimmed_line, "MENU COLOR tabmsg ", 18) == 0)
		{
			strncpy(SYSLINUX_COLOR_TABMSG, trimmed_line + 18, len);
			SYSLINUX_COLOR_TABMSG[len] = '\0';
			parse_syslinux_color_entry(SYSLINUX_COLOR_TABMSG, SYSLINUX_COLOR_TABMSG_OLDMENU, SYSLINUX_COLOR_TABMSG_VESAMENU, SYSLINUX_COLOR_TABMSG_SHADOW); // Added function call
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
#endif
