#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

MODULE_LICENSE("GPL"); 
int init_module(void)
{

   printk(KERN_INFO "Hello world Nahian \n");
return 0;

}

void cleanup_module(void)
{
  printk(KERN_INFO "GoodBye world Nahian\n");

}
