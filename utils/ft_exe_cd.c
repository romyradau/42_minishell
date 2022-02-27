
#include "../minishell.h"


int prep_cd(t_package *package)
{

	int		i;
	char	curdir[255];
	// char	lastdir[255];
	
	i = 1;
	//printing current working dir
	if (!getcwd(curdir, sizeof(curdir)))
		return (0);
	if (package->cmd_args[i] == NULL)
	{
		// printf("\e[0;31m CD fialed here!\033[0m\n");
		if (chdir(curdir) != 0)
		{
			perror("chdir() to /usr faild");
			return (0);
		}
		printf("%s\n", getcwd(curdir, sizeof(curdir)));
		return (1);
	}
	if (!ft_strncmp(package->cmd_args[i], "..", 2))
	{
		if (chdir("..") != 0)
			return (0);
		// ft_strlcpy(lastdir, curdir, 100);
		printf("%s\n", getcwd(curdir, 100));
		return (1);
	}
	else
		return (1);

	//printing current working dir
	return (1);
}