# syslinux-parser
Parse syslinux config into variables.

## Current support:

| **General Options**           | **Color Options**                   | **Old Menu Colors**                   | **VESA Menu Colors**                  | **Shadow Colors**                     |
|-------------------------------|-------------------------------------|---------------------------------------|----------------------------------------|---------------------------------------|
| SYSLINUX_CONF_DEFAULT         | SYSLINUX_COLOR_SCREEN               | SYSLINUX_COLOR_SCREEN_OLDMENU        | SYSLINUX_COLOR_SCREEN_VESAMENU        | SYSLINUX_COLOR_SCREEN_SHADOW         |
| SYSLINUX_CONF_PROMPT          | SYSLINUX_COLOR_BORDER               | SYSLINUX_COLOR_BORDER_OLDMENU        | SYSLINUX_COLOR_BORDER_VESAMENU        | SYSLINUX_COLOR_BORDER_SHADOW         |
| SYSLINUX_CONF_TIMEOUT         | SYSLINUX_COLOR_TITLE                | SYSLINUX_COLOR_TITLE_OLDMENU         | SYSLINUX_COLOR_TITLE_VESAMENU         | SYSLINUX_COLOR_TITLE_SHADOW          |
| SYSLINUX_CONF_UI              | SYSLINUX_COLOR_SEL                  | SYSLINUX_COLOR_SEL_OLDMENU           | SYSLINUX_COLOR_SEL_VESAMENU           | SYSLINUX_COLOR_SEL_SHADOW            |
| SYSLINUX_CONF_BACKGROUND      | SYSLINUX_COLOR_UNSEL                | SYSLINUX_COLOR_UNSEL_OLDMENU         | SYSLINUX_COLOR_UNSEL_VESAMENU         | SYSLINUX_COLOR_UNSEL_SHADOW          |
| SYSLINUX_CONF_TITLE           | SYSLINUX_COLOR_HELP                 | SYSLINUX_COLOR_HELP_OLDMENU          | SYSLINUX_COLOR_HELP_VESAMENU          | SYSLINUX_COLOR_HELP_SHADOW           |
|                               | SYSLINUX_COLOR_TIMEOUT_MSG          | SYSLINUX_COLOR_TIMEOUT_MSG_OLDMENU   | SYSLINUX_COLOR_TIMEOUT_MSG_VESAMENU   | SYSLINUX_COLOR_TIMEOUT_MSG_SHADOW    |
|                               | SYSLINUX_COLOR_TIMEOUT              | SYSLINUX_COLOR_TIMEOUT_OLDMENU       | SYSLINUX_COLOR_TIMEOUT_VESAMENU       | SYSLINUX_COLOR_TIMEOUT_SHADOW        |
|                               | SYSLINUX_COLOR_TABMSG               | SYSLINUX_COLOR_TABMSG_OLDMENU        | SYSLINUX_COLOR_TABMSG_VESAMENU        | SYSLINUX_COLOR_TABMSG_SHADOW         |
