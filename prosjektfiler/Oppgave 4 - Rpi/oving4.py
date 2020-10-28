#!/usr/bin/python
from gpiozero import LED, Button
from time import sleep
from signal import pause
import os
import threading

wait = 8
led = LED(4)
btn = Button(21)
btnspeedup = Button(16)
btnspeeddown = Button(20)

def take_pic():
    led.on()
    print("taking pic")
    os.system('fswebcam --no-banner /var/www/html/img.jpg')
    sleep(0.2)
    led.off()

def speed_up():
    global wait
    if(wait > 1):
        wait += -1
    print("Current wait:", wait)
def speed_down():
    global wait
    if(wait < 30):
        wait += 1
    print("Current wait:", wait)


btn.when_pressed = take_pic
btnspeedup.when_pressed = speed_up
btnspeeddown.when_pressed = speed_down


def loop():
    while True:
        print("taking loop pic")
        take_pic()
        print("current wait", wait)
        sleep(wait-0.2)

if __name__ == "__main__":
    t1 = threading.Thread(target=loop)
    t1.start()
    t1.join()


pause