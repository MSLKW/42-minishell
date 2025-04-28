#include "srcs/minishell.h"
#include "libft/libft.h"

char **split_input(char *input)
{
	char **args = malloc(sizeof(char *) * 3); // max 2 args + NULL
	int i = 0;
	char *token = strtok(input, " ");
	while (token && i < 2)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return args;
}

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	builtin_cdd(char *cmd)
{
	if (!cmd)
	{
		printf("cd: missing argument\n");
		return (1);
	}
	if (chdir(cmd) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	builtin_envtest(char **envp)
{
	int i = 0;

	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int	builtin_exittest(char **args)
{
	int exit_status;

	exit_status = 0;
	printf("exit\n");

	if (args[1] && args[2])
	{
		printf("exit: too man arguments");
		return (1);
	}
	if (args[1])
		exit_status = ft_atoi(args[1]);
	exit(exit_status);
}

int builtin_exporttest(char *arg, char ***envp)
{
	int	i;
	char **new_env;

	i = 0;
	if (!arg)
	{
		//THIS PART TO PRINT ENVIRONMENT WIP
		return(0);
	}
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);

	i = 0;
	while ((*envp)[i])
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;

	free(*envp);
	*envp = new_env;

	return (0);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char input[256];
	int i = 0;
	char **my_envp;

	while (envp[i])
		i++;
	my_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		my_envp[i] = strdup(envp[i]);
		i++;
	}
	my_envp[i] = NULL;

	while (1)
	{
		printf("mini_tester> ");
		if (!fgets(input, sizeof(input), stdin))
			break;
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "pwd") == 0)
			builtin_pwd();
		
		else if (strncmp(input, "cd ", 3) == 0)
			builtin_cdd(input + 3);
		else if (strcmp(input, "env") == 0)
			builtin_envtest(envp);
		else if (strcmp(input, "exit") == 0)
		{
			char **args = split_input(input);
			builtin_exittest(args);
			free(args);
		}
		else if (strncmp(input, "export ", 7) == 0)
			builtin_exporttest(input + 7, &envp);
		else
			printf("no command");
	}
	return (0);
}
