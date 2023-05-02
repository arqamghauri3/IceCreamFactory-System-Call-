#include <linux/kernel.h>

#include <linux/syscalls.h>




asmlinkage long printStatus( char *str ,int no)

{

	printk("Customer %d has: %s",no,str);

	return 0;

}
