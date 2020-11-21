#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void standard(int n, int E);
void file(char* fname, int n, int E);

int main(int argc, char **argv)  {
    int n = 0, E = 0;
    switch (argc)   {
    case 1:
        standard(0, 0);
        break;
    case 2:
        if(argv[1][0]=='-')   {
            if(strlen(argv[1])==1)  standard(0, 0);
            else    {
                if(argv[1][1]=='n') {
                    standard(1, 0);
                }
                else if(argv[1][1]=='E')    {
                    standard(0, 1);
                }
                else    {
                    perror("option not supported");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else    {
            file(argv[1], 0, 0);
        }
        break;
    case 3:
        if(argv[1][0]!='-') {
            perror("invalid input, enter flags before filename");
            exit(EXIT_FAILURE);
        }
        if(strlen(argv[1])==1)  {
            perror("invalid input, enter flags before stdout indicator('-')");
            exit(EXIT_FAILURE);
        }
        if(argv[1][1]=='n') {
            n = 1;
        }
        else if(argv[1][1]=='E')    {
            E = 1;
        }
        else    {
            perror("option not supported");
            exit(EXIT_FAILURE);
        }

        if(argv[2][0]=='-')   {
            if(strlen(argv[2])==1)  {
                standard(n, E);
                exit(EXIT_SUCCESS);
            }
            else    {
                if(argv[2][1]=='n') {
                    n = 1;
                }
                else if(argv[2][1]=='E')    {
                    E = 1;
                }
                else    {
                    perror("option not supported");
                    exit(EXIT_FAILURE);
                }
                standard(n, E);
            }
        }
        file(argv[2], n, E);
        break;
    case 4:
        if(argv[1][0]!='-' || argv[2][0]!='-')  {
            perror("invalid input, enter flags first");
            exit(EXIT_FAILURE);
        }
        if(strlen(argv[1])==1 || strlen(argv[2])==1)    {
            perror("invalid input, enter flags first");
            exit(EXIT_FAILURE);
        }
        if(argv[1][1]=='n') {
            n = 1;
        }
        else if(argv[1][1]=='E')    {
            E = 1;
        }
        else    {
            perror("option not supported");
            exit(EXIT_FAILURE);
        }
        if(argv[2][1]=='n') {
            n = 1;
        }
        else if(argv[2][1]=='E')    {
            E = 1;
        }
        else    {
            perror("option not supported");
            exit(EXIT_FAILURE);
        }
        if(argv[3][0]=='-' && strlen(argv[3])==1)   {
            standard(n, E);
        }
        else    {
            file(argv[3], n, E);
        }
        break;
    default:
        perror("invalid command, max number of words should be 4");
        exit(EXIT_FAILURE);
    }
    return 0;
}

void standard(int n, int E) {
    char *line;
    size_t sz = 0;
    int cnt = 1;
    while(!feof(stdin)) {
        getline(&line, &sz, stdin);
        if(feof(stdin)) {
            exit(EXIT_SUCCESS);
        }
        if(n==1 && E==1)    {
            printf("     %d   ", cnt);
            ++cnt;
            for(int i=0;i<strlen(line)-1;i++) {
                printf("%c", line[i]);
            }
            printf("$\n");

        }
        else if(n==1)   {
            printf("      %d   %s", cnt, line);
            ++cnt;
        }
        else if(E==1)   {
            for(int i=0;i<strlen(line)-1;i++) {
                printf("%c", line[i]);
            }
            printf("$\n");
        }
        else    {
            printf("%s", line);
        }
    }
}

void file(char *fname, int n, int E) {
    FILE *f;
    f = fopen(fname, "r");
    if(!f)  {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }

    int cnt = 1;
    while(!feof(f)) {
        char line[200];
        fgets(line, 200, f);
        if(n==1 && E==1)    {
            printf("     %d   ", cnt);
            ++cnt;
            for(int i=0;i<strlen(line)-1;i++) {
                printf("%c", line[i]);
            }
            printf("$\n");

        }
        else if(n==1)   {
            printf("      %d   %s", cnt, line);
            ++cnt;
        }
        else if(E==1)   {
            for(int i=0;i<strlen(line)-1;i++) {
                printf("%c", line[i]);
            }
            printf("$\n");
        }
        else    {
            printf("%s", line);
        }
    }
    printf("\n\n\n");
}