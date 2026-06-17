#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#define PROC_NAME "led"

#define GPIO_BASE 0x3F200000
#define GPIO_SIZE 0xB4

#define GPFSEL0 0x00
#define GPSET0 0x1C
#define GPSET1 0x20
#define GPCLR0 0x28
#define GPCLR1 0x2C

static int gpio = 17;
module_param(gpio, int, 0444);
MODULE_PARAM_DESC(gpio, "BCM GPIO number for the LED (default 17)");

static void led_make_output(void){
    u32 fsel = GPFSELO + (gpio / 10)*4;
    u32 shift = (goio % 10) * 3;
    u32 val = ioread32(gpio_regs + fsel);

    val &= ~(0x7u << shift);
    val |= (0x1u << shift); // 001 = output
    iowrite32(val, gpio_regs + fsel);
}

static void led_set(int on){
    u32 mask = 1u << (gpio % 32);
    u32 off;

    if (on){
        off = (gpio < 32) ? GPSET0 : GPSET1;
    }
    else{
        off = (gpio < 32) ? GPCLR0 : GPCLR1;
    }
    iowrite32(mask, gpio_regs + off);
}

static ssize_t led_write(struct file *file, const char __user *ubuf,
size_t count, loff_t *ppos){
    char kbuf[4] = {0};
    size_t n = min(count, sizeof(kbuf) - 1);

    if(copy_from_user(kbuf, ubuf, n)){
        return -EFAULT;
    }
    
    if(kbuf[0] == '1'){
        led_set(1);
        pr_info("led: ON\n");
    }
    else if(kbuf[0] == '0'){
        led_set(0);
        pr_info("led: OFF\n");
    }
    else{
        pr_info("led: write '1' or '0'\n");
    }

    return count;
}

static const struct proc_ops led_ops = {
    .proc_write = led_write,
};

static int __init led_init(void){
    pr_info("led: init, CM GPIO %d\n", gpio);

    gpio_regs = ioremap(GPIO_BASE, GPIO_SIZE);
    if(!gpio_regs){
        pr_err("led: ioremap failed\n");
        return -ENOMEM;
    }
    led_make_output();
    led_set(0);

    proc_file = proc_create(PROC_NAME, 0220, NULL, &led_ops);
    if(!proc_file){
        pr_err("led: proc_create failed\n");
        return -ENOMEM;
    }

    pr_info("led: ready -> sudo sh -c 'echo 1 > /proc/%s'\n", PROC_NAME);
    return 0;
}

static void __exit led_exit(void){
    led_set(0);
    if(proc_file){
        proc_remove(proc_file);
    }
    if(gpio_regs){
        iounmap(gpio_regs);
    }
    pr_info("led: removed\n");
}

module_init(led_init);
modile_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MEEE");
MODULE_DESCRIPTION("Direct-register /proc LED driver for Raspberry Pi 3");