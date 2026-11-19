
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

// Device number
static dev_t dev_num;

// Static Character Device
static struct cdev my_cdev;

// Device operations
static const struct file_operations my_fops = {
    .owner = THIS_MODULE,
};

static int __init mymod_init(void)
{
    int ret;

    // Allocate device number
    ret = alloc_chrdev_region(&dev_num, 0, 1, "mymod");

    if (ret < 0)
        return ret;

    // Initialize cdev
    cdev_init(&my_cdev, &my_fops);

    // Register cdev
    ret = cdev_add(&my_cdev, dev_num, 1);

    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    printk(KERN_INFO "Hello World\n");
    printk(KERN_INFO "Major: %d\n", MAJOR(dev_num));

    return 0;
}

static void __exit mymod_exit(void)
{
    // Remove cdev
    cdev_del(&my_cdev);

    // Release device number
    unregister_chrdev_region(dev_num, 1);

    printk(KERN_INFO "Bye Bye World\n");
}

module_init(mymod_init);
module_exit(mymod_exit);

MODULE_LICENSE("GPL");
