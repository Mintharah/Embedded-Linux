# /proc/led kernel module — Raspberry Pi 3
A minimal kernel module that creates /proc/led. Writing 1 turns an LED on,
0 turns it off, by writing directly to the BCM2837 GPIO registers
(no gpiolib, no sysfs, no device tree).

## 1. Wire the LED

BCM GPIO 17 = physical pin 11.

```
GPIO17 (pin 11) ---[ 220-330 ohm resistor ]---|>|--- GND (pin 6)
                                              LED
```

Long leg (anode, +) toward the resistor; short leg (cathode, -) to GND.

---

## 2. Load and test (on the Pi)


```bash
make
sudo insmod led.ko                    # gpio=17 by default
dmesg | tail -5                       # expect "led: init, BCM GPIO 17" ... "ready"
sudo sh -c 'echo 1 > /proc/led'       # LED ON
sudo sh -c 'echo 0 > /proc/led'       # LED OFF
sudo rmmod led
```

---
