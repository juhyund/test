#ifndef _CONFIG_H_
#define _CONFIG_H_

#define DELIM "="

int isBlank(char ch);
char *trim(char *s);
int setConfig(struct instance *ins);

#endif
