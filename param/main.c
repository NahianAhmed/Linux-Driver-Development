#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Nahian");
MODULE_VERSION("0.1"); 

//param
int var_num;

//input 
module_param(var_num,int,S_IRUSR | S_IWUSR);
static int __init showme(void){
    //printk(KERN_INFO "%d",var_num);
    int i ;
    
    printk(KERN_INFO "Hello Nahian\n"); 
    for (i=1;i<var_num;++i){
       printk(KERN_INFO "Looping  %d",i); 
    }
    return 0;
}
	
static void __exit cleanme(void){
    printk(KERN_INFO "Goodbye Nahian\n"); 
}

module_init(showme);
module_exit(cleanme);
