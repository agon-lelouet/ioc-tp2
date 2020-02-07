#include <linux/fs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/io.h>
#include <mach/platform.h>

static const int LED0 = 4;

#define GPIO_LED0 4
#define GPIO_LED1 17

#define GPIO_FSEL_INPUT 0
#define GPIO_FSEL_OUTPUT 1

struct gpio_s
{
  uint32_t gpfsel[7];
  uint32_t gpset[3];
  uint32_t gpclr[3];
  uint32_t gplev[3];
  uint32_t gpeds[3];
  uint32_t gpren[3];
  uint32_t gpfen[3];
  uint32_t gphen[3];
  uint32_t gplen[3];
  uint32_t gparen[3];
  uint32_t gpafen[3];
  uint32_t gppud[1];
  uint32_t gppudclk[3];
  uint32_t test[1];
} volatile *gpio_regs = (struct gpio_s *)__io_address(GPIO_BASE);

static int major;

static void gpio_fsel(int pin, int fun)
{
  uint32_t reg = pin / 10;
  uint32_t bit = (pin % 10) * 3;
  uint32_t mask = 0b111 << bit;
  gpio_regs->gpfsel[reg] = (gpio_regs->gpfsel[reg] & ~mask) | ((fun << bit) & mask);
}

static void gpio_write(int pin, bool val)
{
  if (val)
    gpio_regs->gpset[pin / 32] = (1 << (pin % 32));
  else
    gpio_regs->gpclr[pin / 32] = (1 << (pin % 32));
}

static int gpio_read(int pin)
{
  return (gpio_regs->gplev[pin / 32] >> (pin % 32)) & 0x1;
}

static int
open_ledbp(struct inode *inode, struct file *file) {
  printk (KERN_DEBUG "Ouverture LED\n");
  return 0;
}

static ssize_t
read_ledbp(struct file *file, char *buf, size_t count, loff_t *ppos) {
  gpio_fsel(GPIO_LED0, GPIO_FSEL_INPUT);
  printk (KERN_DEBUG "LED : %d\n", gpio_read(GPIO_LED0));
  return count;
}

static ssize_t
write_ledbp(struct file *file, const char *buf, size_t count, loff_t *ppos) {
  gpio_fsel(GPIO_LED0, GPIO_FSEL_OUTPUT);
  if (*buf == '1')
    gpio_write(GPIO_LED0, 1);
  else
    gpio_write(GPIO_LED0, 0);
  printk (KERN_DEBUG "LED : écriture\n");
  return count;
}

static int
release_ledbp(struct inode *inode, struct file *file) {
  printk(KERN_DEBUG "LED : Release");
  return 0;
}

struct file_operations fops_ledbp =
  {
    .open       = open_ledbp,
    .read       = read_ledbp,
    .write      = write_ledbp,
    .release    = release_ledbp
  };


static int __init ledbp_init(void)
{
  major = register_chrdev(0, "ledbpAL", &fops_ledbp);
  printk(KERN_DEBUG "Insertion !\n");
  return 0;
}

static void __exit ledbp_exit(void)
{
  unregister_chrdev(major, "ledbpAL");
  printk(KERN_DEBUG "Enlèvement !\n");
}

module_init(ledbp_init);
module_exit(ledbp_exit);
