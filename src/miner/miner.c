#include "../../include/miner.h"

int main(int argc, char *argv[])
{
	long rounds;
	long lag;

	if (argc != 3)
		return arguments_error(ARG_COUNT, argv[0]);	

	/* FIXME: move all to a specific function? */
	/* FIXME: use structs to save all the data? */

	/* TODO: change the minimun value: set it on a macro or use POW min value */
	rounds = atoi(argv[1]);
	if (rounds < 0)
		return arguments_error(ARG_ROUND, argv[1]);

	/* TODO: move the minimun time value to a macro */
	lag = atoi(argv[2]);
	if (lag < 0)
		return arguments_error(ARG_LAG, argv[2]);
	
	return 0;
}
