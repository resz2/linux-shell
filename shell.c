#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void cd(char **tokens);
void echo(char **tokens);
void history(char **tokens);
void pwd(char **tokens);
void exiter(char **tokens);

void (*internalFunc[]) (char **) = {&cd, &echo, &history, &pwd, &exiter};
char *internalStr[] = {"cd", "echo", "history", "pwd", "exit"};

void runShell(void);
char *cwdget(void);
char *reader(void);
void addHistory(char *cmd);
char **splitter(char *line);
void executor(char **tokens);
void external(char **tokens);
void freader(FILE *f);

int main()  {
    runShell();
    return 0;
}

void runShell(void) {
    char *input;
    char **args;
    printf("Simple Shell\n\n");
    do  {
        printf("%s$ ", cwdget());
        input = reader();
        if(strcmp(input, "\n")==0) {
            continue;
        }
        addHistory(input);
        args = splitter(input);
        executor(args);
        free(input);
        free(args);
    } while(1);
}

char *cwdget(void) {
    static char cwd[200];
    getcwd(cwd, 200);
    return cwd;
}

char *reader(void)  {
    char *line;
    size_t size = 0;

    if(getline(&line, &size, stdin)==-1)    {
        if(feof(stdin)) {
            printf("\n");
            perror("end of file");
            exit(EXIT_SUCCESS);
        }
        else    {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}

void addHistory(char *cmd)  {
    FILE *f = fopen("history.txt", "a");
    if(!f)  perror("Error opening file");
    fprintf(f, "%s", cmd);
    fclose(f);
}

char **splitter(char *line) {
    char **tokens = malloc(100*sizeof(char *));
    char *lcpy = line;
    char *token;
    int i = 0;

    if(!tokens) {
        perror("allocation");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \n");
    while(token!=NULL)  {
        tokens[i] = token;
        ++i;
        token = strtok(NULL, " \n");
    }

    tokens[i] = NULL;
    return tokens;
}

void executor(char **tokens)    {
    if(tokens==NULL)  {
        perror("empty command");
        return;
    }

    for(int i=0;i<5;i++)    {
        if(strcmp(tokens[0], internalStr[i])==0)  {
            (*internalFunc[i])(tokens);
            return;
        }
    }

    if(tokens[1]!=NULL && strcmp(tokens[1], "--help")==0)  {
        char path[15];
        strcpy(path, "help/");
        strcat(strcat(path, tokens[0]), ".txt");
        FILE *f = fopen(path, "r");
        freader(f);
        fclose(f);
    }
    else    external(tokens);
}

void cd(char **tokens)  {
    if(tokens[1]==NULL) {
        puts("expected argument to cd");
    }
    else if(strcmp(tokens[1], "--help")==0)  {
        FILE *f = fopen("help/cd.txt", "r");
        freader(f);
        fclose(f);
    }
    else if(chdir(tokens[1])!=0)   {
        perror("invalid address");
    }
}

void echo(char **tokens)  {
    if(tokens[1]==NULL)  {
        printf("\n");
    }
    else if(strcmp(tokens[1], "--help")==0)  {
        FILE *f = fopen("help/echo.txt", "r");
        freader(f);
        fclose(f);
    }
    else    {
        int i = 2;
        printf("%s", tokens[1]);
        while(tokens[i]!=NULL)   {
            printf(" %s", tokens[i]);
            ++i;
        }
        if(strcmp(tokens[1], "-n")!=0)     printf("\n");
    }
}

void history(char **tokens)  {
    if(tokens[1]!=NULL && strcmp(tokens[1], "-c")==0)  {
        FILE *f = fopen("history.txt", "w");
        fclose(f);
        return;
    }
    else if(tokens[1]!=NULL && strcmp(tokens[1], "--help")==0)  {
        FILE *f = fopen("help/hist.txt", "r");
        freader(f);
        fclose(f);
        return;
    }
    int i = 1;
    FILE *f = fopen("history.txt", "r");
    if(!f)  perror("error opening file");
    while(!feof(f))    {
        char s[140];
        fgets(s, 140, f);
        printf(" %d   %s", i, s);
        ++i;
    }
    fclose(f);
}

void pwd(char **tokens)  {
    if(tokens[1]!=NULL && strcmp(tokens[1], "--help")==0)  {
        FILE *f = fopen("help/pwd.txt", "r");
        freader(f);
        fclose(f);
        return;
    }
    printf("%s\n", cwdget());
}

void exiter(char **tokens)  {
    if(tokens[1]==NULL)  exit(EXIT_SUCCESS);
    else {
        int code;
        sscanf(tokens[1], "%d", &code);
        printf("exited with value %d\n", code);
        exit(code);
    }
}

void external(char **tokens)    {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid==0)  {
        // Child Process
        if(execv(tokens[0], tokens)==-1)    {
            perror("error in creating process");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid<0)  {
        // Error forking
        perror("error while forking");
    }
    else    {
        // Parent process
        do  {
            wpid = waitpid(pid, &status, WUNTRACED);
        }   while(!WIFEXITED(status) && WIFSIGNALED(status));
    }
}

void freader(FILE *f)   {
    if(f==NULL) {
        printf("cannot open file\n");
        return;
    }
    char c;
    c = fgetc(f);
    while(c!=EOF)   {
        printf("%c", c);
        c = fgetc(f);
    }
    printf("\n\n\n");
}