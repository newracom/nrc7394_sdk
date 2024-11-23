#define COPYRIGHT(year) "Copyright (c) "#year \
	" Newracom Inc. All rights reserved."

#define SYSTEM_CONSOLE_READ_WORD_SIZE			4
#define SYSTEM_CONSOLE_MAX_ARGV					16
#define SYSTEM_CONSOLE_MAX_CMDLINE_SIZE			127

#define READ_REG(offset)        (*(volatile uint32_t*)(offset))

#define WRITE_REG(offset,value) \
(*(volatile uint32_t*)(offset) = (uint32_t)(value));

#define VERIFY_ARG_COUNT(n) if (argc<n+1) return CMD_RET_USAGE;

#define EQUAL_KEY       0x3D
#define ESCAPE_KEY 	0x1B
#define BACKSP_KEY 	0x08
#define TAB_KEY    	0x09
#define RETURN_KEY 	0x0D
#define NEWLINE_KEY	0x0A
#define DELETE_KEY 	0x7F
#define BELL       	0x07

typedef struct nrc_cmd {
	const char *name;
	int (*handler)(struct nrc_cmd *t, int argc, char *argv[]);
	const char *desc;
	const char *usage;
	int flag;
} cmd_tbl_t;

typedef enum cmd_ret_type {
	CMD_RET_USAGE		= -1,
	CMD_RET_SUCCESS		= 0,
	CMD_RET_FAILURE		= 1,
	CMD_RET_UNHANDLED	= 2,
	CMD_RET_HAS_RESULT	= 10
} cmd_ret_type_t;

void system_console();
bool system_console_typing();

#define ll_cmd_declare(cmd)						\
	struct nrc_cmd _nrc_cmd_2_##cmd __aligned(4)			\
	__attribute__((used, section(".nrc_cmd_2_"#cmd)))

#define ll_cmd_start()							\
({									\
	static char start[0] __aligned(4) __attribute__((used,	\
		section(".nrc_cmd_1")));			\
	(struct nrc_cmd *)&start;					\
})

#define ll_cmd_end()							\
({									\
	static char end[0] __aligned(4) __attribute__((used,		\
		section(".nrc_cmd_3")));				\
	(struct nrc_cmd *)&end;						\
})

#define ll_subcmd_declare(cmd, subcmd)					\
	struct nrc_cmd _nrc_cmd_2_##cmd##_2_##subcmd __aligned(4)	\
	__attribute__((used, 						\
		       section(".nrc_cmd_2_"#cmd"_2_"#subcmd)))

#define ll_subcmd_start(cmd)						\
({									\
	static char start[0] __aligned(4) __attribute__((used,	\
		section(".nrc_cmd_2_"#cmd"_1")));			\
	(struct nrc_cmd *)&start;					\
})

#define ll_subcmd_end(cmd)						\
({									\
	static char end[0] __aligned(4) __attribute__((used,		\
		section(".nrc_cmd_2_"#cmd"_3")));			\
	(struct nrc_cmd *)&end;						\
})

#define for_each_subcmd(s, cmd)						\
	for (s = ll_subcmd_start(cmd); s < ll_subcmd_end(cmd); s++)

#define CMD_ATTR_TOP 		(0)
#define CMD_ATTR_SUB 		(1)
#define CMD_ATTR_EXPL 		(2)

/*
CONFIG_SYSTEM_CONSOLE : 0 (No CLI Command)
CONFIG_SYSTEM_CONSOLE : 1 (Mandatory CLI Command)
CONFIG_SYSETM_CONSOLE : 2 (Full CLI Command)
*/

#if (CONFIG_SYSTEM_CONSOLE != 0) 

	#if (CONFIG_SYSTEM_CONSOLE == 1)
		#define CMD(cmd, fn, d, u)
		#define SUBCMD(cmd, subcmd,fn, d, u)
		#define SUBCMD_EXPL(cmd, subcmd,fn, d, u)

		/* Minimum CLI Set (mandatory CLI SET) : CMD_MAND SUBCMD_MAND */
		#define CMD_MAND(cmd, fn, d, u)	\
			ll_cmd_declare(cmd) = { 	\
				.name = #cmd,			\
				.handler = fn,			\
				.desc = d,				\
				.usage = u, 			\
				.flag = CMD_ATTR_TOP,	\
			}

		#define SUBCMD_MAND(cmd, subcmd,fn, d, u)	\
			ll_subcmd_declare(cmd, subcmd) = {		\
				.name = #subcmd,					\
				.handler = fn,						\
				.desc = d,							\
				.usage = u, 						\
				.flag = CMD_ATTR_SUB,				\
			}
	#else
		#define CMD(cmd, fn, d, u)			\
			ll_cmd_declare(cmd) = {			\
				.name = #cmd,				\
				.handler = fn,				\
				.desc = d,					\
				.usage = u, 				\
				.flag = CMD_ATTR_TOP,		\
			}

		#define SUBCMD(cmd, subcmd,fn, d, u)		\
			ll_subcmd_declare(cmd, subcmd) = { 		\
				.name = #subcmd,					\
				.handler = fn, 						\
				.desc = d,	 						\
				.usage = u,	 						\
				.flag = CMD_ATTR_SUB,				\
			}

		#define SUBCMD_EXPL(cmd, subcmd,fn, d, u)		\
			ll_subcmd_declare(cmd, subcmd) = {			\
				.name = #subcmd							\
				.handler = fn,							\
				.desc = d,								\
				.usage = u,								\
				.flag = CMD_ATTR_SUB | CMD_ATTR_EXPL,	\
			}

		#define CMD_MAND(cmd, fn, d, u)	CMD(cmd, fn, d, u)
		#define SUBCMD_MAND(cmd, subcmd,fn, d, u)	SUBCMD(cmd, subcmd,fn, d, u)
	#endif

#else
	#define CMD(cmd, fn, d, u)
	#define CMD_MAND(cmd, fn, d, u)
	#define CMD_HALOW(cmd, fn, d, u)
	#define SUBCMD(cmd, subcmd,fn, d, u)
	#define SUBCMD_MAND(cmd, subcmd,fn, d, u)
	#define SUBCMD_HALOW(cmd, subcmd,fn, d, u)
	#define SUBCMD_EXPL(cmd, subcmd,fn, d, u)
	#define SUBCMD_HALOW(cmd, subcmd,fn, d, u)
#endif
