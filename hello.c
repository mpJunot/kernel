#include "hello.h"

MODULE_LICENSE("IDK");
MODULE_DESCRIPTION("My firt kernel module");
MODULE_AUTHOR("You");

static int n = 0;
static int major = 0;
static char *name = NULL;
static char *output = NULL;

module_param(name, charp, S_IRUSR | S_IWUSR);
module_param(n, int, S_IRUSR | S_IWUSR);

static int my_dev_open(struct inode *inode, struct file *file);
static int my_dev_close(struct inode *inode, struct file *file);
static ssize_t my_dev_read(struct file *file, char *buf, size_t len, loff_t *off);
static ssize_t my_dev_write(struct file *file, const char *buf, size_t len, loff_t *off);

static struct file_operations fops = {
	.read = my_dev_read,
	.write = my_dev_write,
	.open = my_dev_open,
	.release = my_dev_close
};

static int my_dev_open(struct inode *inode, struct file *file)
{
	printk("Device is open\n");
	return 0;
}

static int my_dev_close(struct inode *inode, struct file *file)
{
	printk("Device is closed");
	return 0;

}

static ssize_t my_dev_read(struct file *file, char *buf, size_t len, loff_t *off) {
	return 0;
}

static ssize_t my_dev_write(struct file *file, const char *buf, size_t len, loff_t *off) {
	return 0;
}

static int __init my_init(void)
{
	int x = 0;

	while (x < n) {
		printk("Hello: %s\n", name);
		x++;
	}
	major = register_chrdev(0, "toto", &fops);
	printk("%d\n", major);
	return 0;
}

static void __exit my_exit(void)
{
	int x = 0;

	while (x < n) {
		printk("Goodbye: %s\n", name);
		x++;
	}
	unregister_chrdev(major, "toto");
}

module_init(my_init);
module_exit(my_exit);
