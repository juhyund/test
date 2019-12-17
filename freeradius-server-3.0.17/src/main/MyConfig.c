#include <stdio.h>
#include <freeradius-devel/radius.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUF 1024 
#define DELIM "="


struct config get_config(char *filename)
{
        struct config configstruct;
        FILE *file = fopen (filename, "r");

        if (file != NULL)
        {
                char line[MAXBUF];
                int i = 0;

                while(fgets(line, sizeof(line), file) != NULL)
                {
                        char *cfline;
                        cfline = strstr((char *)line,DELIM);
                        cfline = cfline + strlen(DELIM);

                        if (i == 0){
                                memcpy(configstruct.kepfepcert,cfline,strlen(cfline));
                        } else if (i == 1){
                                memcpy(configstruct.kepemucert,cfline,strlen(cfline));
                        }

                        i++;
                }
                fclose(file);
        }



        return configstruct;

};

