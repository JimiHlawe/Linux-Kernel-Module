
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/err.h>

// Device number
static dev_t dev_num;

// Character Device
static struct cdev my_cdev;

// Device class
static struct class *my_class;

// File operations
static const struct file_operations my_fops = {
    .owner = THIS_MODULE,
};

static int __init mymod_init(void)
{
    int ret;
    struct device *my_device;

    // Allocate device number
    ret = alloc_chrdev_region(&dev_num, 0, 1, "mymod");
    if (ret < 0)
        return ret;

    // Initialize and register cdev
    cdev_init(&my_cdev, &my_fops);

    ret = cdev_add(&my_cdev, dev_num, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    // Create device class
    my_class = class_create("mymod_class");

    if (IS_ERR(my_class)) {
        ret = PTR_ERR(my_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    // Create device file
    my_device = device_create(my_class, NULL,
                              dev_num, NULL, "mymod");

    if (IS_ERR(my_device)) {
        ret = PTR_ERR(my_device);
        class_destroy(my_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    printk(KERN_INFO "Hello World\n");
    printk(KERN_INFO "Major: %d\n", MAJOR(dev_num));

    return 0;
}

static void __exit mymod_exit(void)
{
    // Remove device file and class
    device_destroy(my_class, dev_num);
    class_destroy(my_class);

    // Remove cdev and device number
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);

    printk(KERN_INFO "Bye Bye World\n");
}

module_init(mymod_init);
module_exit(mymod_exit);

MODULE_LICENSE("GPL");
