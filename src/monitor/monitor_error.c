# include "../../include/monitor.h"

int	argument_error(t_error error, char **argv)
{
	switch (error)
	{
		case ARG_COUNT:
			printf("Argument error!\n\tUsage: %s <LAG>\n", argv[0]);
			break;
		
		case ARG_LAG:
			printf("Incorrect time of cooldown! (\"%s\")\n", argv[1]);

		default:
			break;
	}
	return 1;
}
