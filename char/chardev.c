#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/string.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/semaphore.h>
#include<asm/uaccess.h>


struct fake_device {
	char data[100];
	struct semaphore sem;
} virtual_device;


struct cdev *mcdev;
int major_number;
int ret;

dev_t dev_num;

#define DEVICE_NAME   "UXBD"

int device_open(struct inode *inode, struct file *filep){

	if(down_interruptible(&virtual_device.sem) != 0){
		printk(KERN_ALERT "UXBD: could not lock device during open");
	return -1;
	}
	
	printk(KERN_INFO "UXBD: opened device");
	return 0;
}

ssize_t device_read(struct file *filp,char *bufStoreData,size_t bufCount,loff_t *curOffset){
 
	printk(KERN_INFO "UXBD : Reading from device");
	ret=raw_copy_to_user(bufStoreData,virtual_device.data,bufCount);
	return ret;
}

ssize_t device_write(struct file *filp,const char *bufSourceData,size_t bufCount,loff_t *curOffset){
 
	printk(KERN_INFO "UXBD : writing to device");
	ret=raw_copy_from_user(virtual_device.data, bufSourceData, bufCount);
	return ret;
}

int device_close(struct inode *inode, struct file *filep){

	up(&virtual_device.sem);
	
	printk(KERN_INFO "UXBD: closed device");
	return 0;
}


static struct file_operations fops = {
	.owner=THIS_MODULE,
	.read=device_read,
	.open=device_open,
	.write=device_write,
	.release=device_close,
};


static int driver_entry(void){


	ret=alloc_chrdev_region(&dev_num,0,1,DEVICE_NAME);
	if(ret<0) 
	{
		printk(KERN_ALERT "UXBD: failed to allocate a major no");
		return ret;
	}
	major_number=MAJOR(dev_num);
	printk(KERN_INFO "UXBD: major no is %d\n",major_number);
	printk(KERN_INFO "\tuse \"mknod /dev /%s c %d 0\" for device file\n",DEVICE_NAME,major_number);

	mcdev = cdev_alloc();
	mcdev->ops = &fops;
	mcdev->owner = THIS_MODULE;

	ret=cdev_add(mcdev, dev_num, 1);
	if(ret<0) {
		printk(KERN_ALERT "UXBD: unable to add cdev to kernel");
		return ret;
	}

	sema_init(&virtual_device.sem,1);

	return 0;
}


static void driver_exit(void){


	cdev_del(mcdev);
	
	unregister_chrdev_region(dev_num, 1);
	printk(KERN_ALERT "UXBD: unloaded module");
}


module_init(driver_entry);
module_exit(driver_exit);