#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Nahian");
MODULE_VERSION("0.1"); 
// function 
static void pp(void);
//param
static int num;

//input 
module_param(num,int,S_IRUSR | S_IWUSR);
static int __init showme(void){
    int i ;
    
    printk(KERN_INFO "Hello Nahian\n"); 
    for (i=1;i<num;i++){
       printk(KERN_INFO "Looping  %d",i); 
    }
    
    pp();
    return 0;
}

static void pp(void){
 printk(KERN_INFO "Loop End"); 
}
	
static void __exit cleanme(void){
    printk(KERN_INFO "Goodbye Nahian\n"); 
}

module_init(showme);
module_exit(cleanme);
