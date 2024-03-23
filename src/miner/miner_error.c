#include "../../include/miner.h"

int	arguments_error(t_error error, char **argv)
{
	switch (error)
	{
		case ARG_COUNT:
			printf("Argument error!\n\tUsage: %s <ROUNDS> <LAG>\n", argv[0]);
			break ;

		case ARG_ROUND:
			printf("Incorrect number to search! (\"%s\")\n", argv[1]);
			break ;

		case ARG_LAG:
			printf("Incorrect time of cooldown! (\"%s\")\n", argv[2]);
			break ;
		
		default:
			break ;
	}
	return (1);
}
