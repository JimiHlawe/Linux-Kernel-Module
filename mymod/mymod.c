
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

// Store the device number
static dev_t dev_num;

static int __init mymod_init(void)
{
    int ret;

    // Allocate a device number
    ret = alloc_chrdev_region(&dev_num, 0, 1, "mymod");

    if (ret < 0)
        return ret;

    printk(KERN_INFO "Hello World\n");
    printk(KERN_INFO "Major: %d\n", MAJOR(dev_num));

    return 0;
}

static void __exit mymod_exit(void)
{
    // Release the device number
    unregister_chrdev_region(dev_num, 1);

    printk(KERN_INFO "Bye Bye World\n");
}

module_init(mymod_init);
module_exit(mymod_exit);

MODULE_LICENSE("GPL");
