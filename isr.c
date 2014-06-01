#include"interrupt.h"
void isr()
{
	breakpoint();
	__asm__("ld		wq,1\n\t"\
			"aqw_ld void,26");
	schedule();
	__asm__("ld		wq,0\n\t"\
			"aqw_ld void,26");
	returnBreakpoint();
}
