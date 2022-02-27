
#include "../minishell.h"

char lastdir[255]; //*wird gebraucht um denn lezten path abzu speichern, für cd

int prep_cd(t_package *package)
{

	int i;
	char curdir[255];
	i = 1;
	//printing current working dir
	if (!getcwd(curdir, 100))
		return (0);
	if (!ft_strncmp(package->cmd_args[i], "..", 2))
	{
		chdir("..");
		ft_strlcpy(lastdir, curdir, 100);
	}
	else
		return (1);

	//printing current working dir
	printf("%s\n", getcwd(lastdir, 100));
	(void)package;
	return (1);
}