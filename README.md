# syslinux-parser
parse syslinux config into variables

# current support:

| Entries   |
|-          |
| LABEL     |
| MENULABEL |
| COMMAND   |
| APPEND    |
| INITRD    |
| COM32     |

| OPTIONS   |
|-          |
| DEFAULT   |
| PROMPT    |
| TIMEOUT   |
| UI        |

*all values are parsed as char, so options like TIMEOUT may be processed with atoi*
