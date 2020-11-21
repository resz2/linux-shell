#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<sys/errno.h>
#include<sys/stat.h>
#include<sys/types.h>

void simple(char *path, mode_t mode, int v);
void recursive(char *path, mode_t mode, int v);

int main(int argc, char **argv) {
    if(argc==1) {
        perror("missing operand");
        exit(EXIT_FAILURE);
    }
    mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH;
    int p = 0, v = 0;
    int i = 1;
    int slash = '/';
    while(argv[i]!=NULL) {
        if(i<3) {
            if(strcmp(argv[i], "-v")==0)    {
                v = 1;
                ++i;
                continue;
            }
            if(strcmp(argv[i], "-p")==0)    {
                p = 1;
                ++i;
                continue;
            }
        }
        if(strcmp(argv[i], "-v")!=0 && strcmp(argv[i], "-p")!=0)    {
            if(strchr(argv[i], slash)!=NULL)  {
                if(p)   recursive(argv[i], mode, v);
                else    simple(argv[i], mode, v);
            }
            else    {
                simple(argv[i], mode, v);
            }
        }
        ++i;
    }
    return 0;
}

void simple(char *path, mode_t mode, int v)    {
    if(mkdir(path, mode)==-1)   {
        if(errno==EEXIST)   {
            printf("mkdir: cannot create directory '%s': File exists\n", path);
        }
        if(errno==ENOENT)   {
            printf("mkdir: cannot create directory '%s': No such file or directory\n", path);
        }
    }
    else if(v)   printf("mkdir: created directory '%s'\n", path);
}

void recursive(char *path, mode_t mode, int v) {
    char *last;
    assert(path && *path);
    for(char *p = strchr(path, '/');p;p = strchr(p+1, '/')) {
        *p = '\0';
        if(mkdir(path, mode)==-1)   {
            if(errno!=EEXIST)   {
                *p = '/';
                perror("error during file creation");
                exit(errno);
            }
        }
        else if(v)  printf("mkdir: created directory '%s'\n", path);
        *p = '/';
        last = p;
    }
    mkdir(path, mode);
    if(v)   printf("mkdir: created directory '%s'\n", path);
}