#ifndef _NMDBG_NMICTRL_H
#define _NMDBG_NMICTRL_H

#include <linux/cpumask.h>
#include <asm/ptrace.h>

#include "define.h"

#define NMICTRL_HANDLER_NAMESZ 32

typedef enum {
	NMICTRL_HANDLED,
	NMICTRL_FORWARD,
	NMICTRL_ERROR,
} nmictrl_ret_t;

typedef nmictrl_ret_t (*nmictrl_fn_t)(struct pt_regs *);

typedef struct {
	char handler_name[NMICTRL_HANDLER_NAMESZ];
	cpumask_t handler_mask;
	nmictrl_fn_t handler_fn;
	struct list_head handler_list;
	struct rcu_head handler_rcu;
} nmictrl_handler_t;

int nmictrl_add_handler(const char *handler_name, nmictrl_fn_t nmi_handler);
void nmictrl_del_handler(const char *handler_name);
void nmictrl_trigger(const char *handler_name);

#endif