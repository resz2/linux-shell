#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

void lister(char *add, int a, int m);

int main(int argc, char **argv)  {
    if(argc==1) {
        lister(".", 0, 0);
    }
    else if(argc==2)    {
        if(argv[1][0]=='-') {
            if(argv[1][1]=='a') {
                lister(".", 1, 0);
            }
            else if(argv[1][1]=='m')    {
                lister(".", 0, 1);
            }
            else    {
                perror("option not supported");
                exit(EXIT_FAILURE);
            }
        }
        else    {
            lister(argv[1], 0, 0);
        }
    }
    else if(argc==3)    {
        int a = 0, m = 0;
        if(argv[1][0]!='-') {
            perror("invalid input, enter flags before directory");
            exit(EXIT_FAILURE);
        }
        if(argv[2][0]=='-') {
            if(argv[1][1]=='a') {
                a = 1;
            }
            else if(argv[1][1]=='m')    {
                m = 1;
            }
            else    {
                perror("option not supported");
                exit(EXIT_FAILURE);
            }

            if(argv[2][1]=='a') {
                a = 1;
            }
            else if(argv[2][1]=='m')    {
                m = 1;
            }
            else    {
                perror("option not supported");
                exit(EXIT_FAILURE);
            }
            lister(".", a, m);
        }
        else    {
            if(argv[1][1]=='a') {
                a = 1;
            }
            else if(argv[1][1]=='m')    {
                m = 1;
            }
            else    {
                perror("option not supported");
                exit(EXIT_FAILURE);
            }
            lister(argv[2], a, m);
        }
    }
    else if(argc==4)    {
        int a = 0, m =0;
        if(argv[1][1]!='-' || argv[2][1]!='-')  {
            perror("invalid input, enter flags first");
            exit(EXIT_FAILURE);
        }
        if(argv[1][1]=='a') {
            a = 1;
        }
        else if(argv[1][1]=='m')    {
            m = 1;
        }
        else    {
            perror("option not supported");
            exit(EXIT_FAILURE);
        }
        if(argv[2][1]=='a') {
            a = 1;
        }
        else if(argv[2][1]=='m')    {
            m = 1;
        }
        else    {
            perror("option not supported");
            exit(EXIT_FAILURE);
        }

        lister(argv[3], a, m);
    }

    else    {
        perror("invalid command, max number of words should be 4");
        exit(EXIT_FAILURE);
    }
    return 0;
}

void lister(char *add, int a, int m)   {
    struct dirent *d;
    DIR *dir = opendir(add);
    if(!dir)  {
        if(errno==ENOENT)   {
            perror("directory doesn't exist");
        }
        else    {
            perror("unable to read directory");
        }
        exit(EXIT_FAILURE);
    }
    while((d = readdir(dir))!=NULL) {
        if(!a)  {
            if(d->d_name[0]=='.')   continue;
        }
        if(!m)  {
            printf("%s   ", d->d_name);
        }
        else    {
            printf("%s, ", d->d_name);
        }
    }
    printf("\n\n");
}