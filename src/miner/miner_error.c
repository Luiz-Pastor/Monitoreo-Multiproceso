#include "../../include/miner.h"

int	arguments_error(t_error error, char *data)
{
	switch (error)
	{
		case ARG_COUNT:
			printf("Argument error!\n\tUsage: %s <ROUNDS> <LAG>\n", data);
			break ;

		case ARG_ROUND:
			printf("Incorrect number to search! (\"%s\")\n", data);
			break ;

		case ARG_LAG:
			printf("Incorrect time of cooldown! (\"%s\")\n", data);
			break ;
	}
	return (1);
}
