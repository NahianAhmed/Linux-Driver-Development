#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
#include<linux/stat.h>

//param
static int num;
module_param(num,int,S_IRUSR | S_IWUSR);

static int __init showme(void){

    int i;
     printk(KERN_INFO "Hello Nahian\n"); 
     printk(KERN_INFO "loop start\n"); 
     for (i=0;i<num;i++){
       printk(KERN_INFO "Looping  %d",i); 
    }
     printk(KERN_INFO "loop end\n"); 
    
    return 0;
}


	
static void __exit cleanme(void){
    printk(KERN_INFO "Goodbye Nahian\n"); 
}

module_init(showme);
module_exit(cleanme);
