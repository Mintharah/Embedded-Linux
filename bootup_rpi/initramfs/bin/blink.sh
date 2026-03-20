#!/bin/sh

# The "Shifted" Pin Number
PIN="528" 
GPIO_PATH="/sys/class/gpio/gpio$PIN"

# 1. Export the shifted pin
if [ ! -d "$GPIO_PATH" ]; then
    echo "$PIN" > /sys/class/gpio/export
    sleep 0.5
fi

# 2. Set direction and blink
echo "out" > "$GPIO_PATH/direction"

while true; do
    echo 1 > "$GPIO_PATH/value"
    echo "GPIO $PIN (Hardware 36) HIGH"
    sleep 1
    echo 0 > "$GPIO_PATH/value"
    echo "GPIO $PIN (Hardware 36) LOW"
    sleep 1
done