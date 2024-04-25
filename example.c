#include "syslinux-parser.h"

int main() {
	// Declarate an internal struct to read the entries
	struct SYSLINUX_ENTRY entries[MAX_ENTRIES];

	// Parse the syslinux config file
	if (parse_syslinux_config("syslinux.cfg", entries) != 0) {
		printf("Error: Unable to open syslinux config file.\n");
		return 1;
	}

	// Print the parsed entries
	printf("SYSLINUX CONFIG: \nDEFAULT: %s\nPROMPT: %s\nTIMEOUT: %s\nUI: %s\n\n",
		SYSLINUX_CONF_DEFAULT, SYSLINUX_CONF_PROMPT, SYSLINUX_CONF_TIMEOUT, SYSLINUX_CONF_UI);
	printf("Entries:\n");
	for (int i = 0; i < entry_count; i++) {
		if (entries[i].label[0] != '\0') {
			printf("Label: %s\n", entries[i].label);
			printf("Menu Label: %s\n", entries[i].menulabel);
			if (strlen(entries[i].command) > 0) {
				printf("Command: %s\n", entries[i].command);
			}
			if (strlen(entries[i].append) > 0) {
				printf("Append: %s\n", entries[i].append);
			}
			if (strlen(entries[i].com32) > 0) {
				printf("Com32: %s\n", entries[i].com32);
			}
			if (strlen(entries[i].initrd) > 0) {
				printf("Initrd: %s\n", entries[i].initrd);
			}
			printf("\n");
		}
	}
	return 0;
}