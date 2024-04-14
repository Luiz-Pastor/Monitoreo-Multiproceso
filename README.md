# Multi-process monitoring

## Struct of the project

```
 /root
	|
	|--	Makefile (automatic compilation using 'make' util)
	|
	|--	obj/ (folder to save the object files)
	|--	inc/ (includes folder)
	|	|- config.h (global macros)
	|	|- miner.h
	|	|- monitor.h
	|	|- msg_utils.h
	|	|- pow.h
	|	|- shared_memory_utils.h
	|
	|--	src/ (source files)
		|- miner
		|	|- miner.c
		|	|- miner_routine.c
		|
		|- monitor
		|	|- monitor.c
		|	|- monitor_routine.c
		|	|- checker_routine.c
		|
		|- common_utils
			|- pow.c
			|- msg_utils.c
			|- shared_memory_utils.c
	

```