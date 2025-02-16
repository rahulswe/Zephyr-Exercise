#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#ifdef CONFIG_CALC
#include "calc.h"
#endif

int main()
{
    while(1)
    {
#ifdef CONFIG_CALC
        printk("Hello World %d\n", sum(5, 7));
#else
        printk("Hello World\n");
#endif
        k_msleep(100);
    }
}