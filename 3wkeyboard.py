//Raspberry pi code to run 3 wheeled bot using keyboard

import RPi.GPIO as GPIO
import time
import math
import numpy as np
from numpy.linalg import invdef calc(x,y,w):
    a1=math.radians(120)
    a2=math.radians(240)
    a3=math.radians(360)    x1=math.cos(a1)
    x2=math.cos(a2)
    x3=math.cos(a3)
    y1=math.sin(a1)
    y2=math.sin(a2)
    y3=math.sin(a3)    #x=int(input("Enter x:"))
    #y=int(input("Enter y:"))
    #w=int(input("Enter w:"))    I=np.array([[x], [y], [w]])
    X=np.array([[x1, x2, x3], [y1, y2, y3], [1, 1, 1]])
    invx=inv(X)    S=np.matmul(invx, I)    s1=S[0]
    s2=S[1]
    s3=S[2]    print "S1, S2, S3:", s1, s2, s3motor1_dir = 11
motor1_pwm = 8
motor2_dir = 13
motor2_pwm = 10
motor3_dir = 15
motor3_pwm = 12
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(motor1_dir,GPIO.OUT)
GPIO.setup(motor1_pwm,GPIO.OUT)
GPIO.setup(motor2_dir,GPIO.OUT)
GPIO.setup(motor2_pwm,GPIO.OUT)
GPIO.setup(motor3_dir,GPIO.OUT)
GPIO.setup(motor3_pwm,GPIO.OUT)motor_1=GPIO.PWM(motor1_pwm,1500)
motor_2=GPIO.PWM(motor2_pwm,1500)
motor_3=GPIO.PWM(motor3_pwm,1500)
motor_1.start(0)
motor_2.start(0)
motor_3.start(0)
max_speed =70
min_speed = 0
def forward():
   GPIO.output(motor1_dir ,0)
   GPIO.output(motor2_dir,0)
   GPIO.output(motor3_dir,0)
   calc(0,1,0)
   motor_1.ChangeDutyCycle(s1)
   motor_2.ChangeDutyCycle(s2)
   motor_3.ChangeDutyCycle(s3)def left():
   GPIO.output(motor1_dir,0)
   GPIO.output(motor2_dir,0)
   GPIO.output(motor3_dir,1)
   calc(-1,0,0)
   motor_1.ChangeDutyCycle(s1)
   motor_2.ChangeDutyCycle(s2)
   motor_3.ChangeDutyCycle(s3)
 
def right():
   GPIO.output(motor1_dir,1)
   GPIO.output(motor2_dir,1)
   GPIO.output(motor3_dir,0)
   calc(1,0,0)
   motor_1.ChangeDutyCycle(s1)
   motor_2.ChangeDutyCycle(s2)
   motor_3.ChangeDutyCycle(s3)
 
def rotate():
   GPIO.output(motor1_dir,0)
   GPIO.output(motor2_dir,1)
   GPIO.output(motor3_dir,1)
   calc(0,0,1)
   motor_1.ChangeDutyCycle(s1)
   motor_2.ChangeDutyCycle(s2)
   motor_3.ChangeDutyCycle(s3)
def backward():
    GPIO.output(motor1_dir,1)
    GPIO.output(motor2_dir,1)
    GPIO.output(motor3_dir,0)
    calc(0,-1,0)  
    motor_1.ChangeDutyCycle(s1)
    motor_2.ChangeDutyCycle(s2)
    motor_3.ChangeDutyCycle(s3)def stop():
   motor_1.ChangeDutyCycle(min_speed)
   motor_2.ChangeDutyCycle(min_speed)
   motor_3.ChangeDutyCycle(min_speed)while 1:
    ch = raw_input()
    if ch == 'w':
        forward()
        print "Forward"
    elif ch == 's':
        backward()
        print "Backward"
    elif ch == 'a':
        left()
        print "Left"
    elif ch == 's':
        stop()
        print "Stop"
    elif ch == 'q':
        quit()
        print "Quit"
    elif ch == 'r':
        rotate()
        print "Rotate"
    elif ch == 'd':
        right()
        print "Right"
