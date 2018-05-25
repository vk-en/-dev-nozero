#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h> 
/*date 05.08.2017*/ 
MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "vk_en" );
MODULE_SUPPORTED_DEVICE( "nozero" ); /* /dev/nozero*/


#define DEVICE_NAME "nozero" 


static int device_open( struct inode *, struct file * );
static int device_release( struct inode *, struct file * );
ssize_t device_read( struct file *, char *, size_t, loff_t * );


static int major_number = 247; 
static int is_device_open = 0; 


static struct file_operations fops =
{
	.read = device_read,
  	.open = device_open,
  	.release = device_release
};


static int device_open( struct inode *inode, struct file *file )
{
	if ( is_device_open )
  		return -EBUSY;
	is_device_open++;
 	return 0;
}

static int device_release( struct inode *inode, struct file *file )
{
	is_device_open--;
	return 0;
}

ssize_t device_read(struct file *filp, char  *read_buff, size_t size, loff_t *offset)
{
	int i = 0;
	int byte_read = 0;
	unsigned char ss;
	unsigned int copy=0;
	unsigned char *B = (unsigned char*) kzalloc(size , GFP_KERNEL);

	if (B == NULL)
	{
		printk("No memory for buf");
		return 0;	
	}	

	copy = copy_from_user(B, read_buff, size);
	if (copy != 0) 
		printk("from no copy %d",copy);

	ss = 0;// 0 - 255 / 0x00 0xFF
	for (i = 0; i < size; i++){
		B[i] = ss;
		if (ss == 255) ss = 0;	
		else ss++;		
		byte_read++;	
	}

   	copy = copy_to_user(read_buff, B, size);
	if (copy != 0)
		printk("to no copy %d",copy);
		
    kfree(B);
    return byte_read;
}


static int __init nozero_init( void )
{
	register_chrdev( major_number, DEVICE_NAME, &fops );
 	printk( KERN_INFO "nozero module is load!\n" );
	return 0;
}


static void __exit nozero_exit( void )
{
 	unregister_chrdev( major_number, DEVICE_NAME );
	printk( KERN_INFO "nozero module is unload!\n" );
}


module_init(nozero_init);
module_exit(nozero_exit);
