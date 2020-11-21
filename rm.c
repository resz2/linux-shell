#define _XOPEN_SOURCE 500

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/errno.h>
#include<unistd.h>
#include<ftw.h>

void normal(char *path, int d);
int recursor(char *path);
int deletor(const char *path, const struct stat *sb, int tflag, struct FTW *ftwbuf);

int main(int argc, char **argv) {
    if(argc==1) {
        perror("missing operand");
        exit(EXIT_FAILURE);
    }
    int d = 0, r = 0;
    int i = 1;
    int slash = '/';

    while(argv[i]!=NULL) {
        if(i<3) {
            if(strcmp(argv[i], "-r")==0)    {
                r = 1;
                ++i;
                continue;
            }
            if(strcmp(argv[i], "-d")==0)    {
                d = 1;
                ++i;
                continue;
            }
        }
        if(strcmp(argv[i], "-r")!=0 && strcmp(argv[i], "-d")!=0)    {
            if(r)   recursor(argv[i]);
            else    normal(argv[i], d);
        }
        ++i;
    }
    return 0;   
}

void normal(char *path, int d)  {
    int status;
    if(d)   {
        if(status = remove(path)==-1)   {
            if(errno==ENOTEMPTY)    {
                printf("cannot remove '%s': Directory not empty\n", path);
            }
        }
    }
    else    {
        if(status = unlink(path)==-1)   {
            if(errno==EISDIR)   {
                printf("rm: cannot remove '%s': Is a directory\n", path);
            }
        }
    }
}

int recursor(char *path)   {
    return nftw(path, deletor, 64, FTW_DEPTH | FTW_PHYS);
}

int deletor(const char *path, const struct stat *sb, int tflag, struct FTW *ftwbuf) {
    int rv = remove(path);
    if(rv)  {
        perror(path);
    }
    return rv;
}