#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define TRUE 1
#define MAX_COMANDO 100
#define MAX_PARAMETROS 10

void print_command_and_parameters(char *command, char **parameters)
{
    printf("Command: %s\n", command);
    printf("Parameters:\n");
    for (int i = 0; parameters[i] != NULL; i++)
    {
        printf("  - %s\n", parameters[i]);
    }
}

void ler_comando(char *comando, char *parametro[])
{
    char input[MAX_COMANDO];
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    char *token = strtok(input, " ");
    if (token != NULL)
    {
        strcpy(comando, token);
    }

    if (strcmp(comando, "exit") == 0)
    {
        printf("\nSaindo do shell...\n\n");
        exit(0);
    }

    int i = 0;
    while (token != NULL && i < MAX_PARAMETROS)
    {
        parametro[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    parametro[i] = NULL;
}

int main()
{
    char comando[MAX_COMANDO];
    char *parametro[MAX_PARAMETROS + 1];
    int status;

    system("clear");
    printf("Bem vindo ao shell simplificado!\n\n");

    while (TRUE)
    {
        printf(">: ");
        ler_comando(comando, parametro);
        // print_command_and_parameters(command, parameters);

        if (fork() != 0)
        {
            waitpid(-1, &status, 0);
        }
        else
        {
            if (execvp(comando, parametro) < 0)
            {
                perror("execvp");
                printf("Falha ao executar o comando.\n");
                break;
            }
        }
    }
    return 0;
}
