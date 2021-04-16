#!/usr/bin/env python
import rospy
import math
import numpy as np
import random
import time
import sympy as sym
from optparse import OptionParser
from std_msgs.msg import Int32MultiArray
import numpy as np

class PWM_Intensity_Ctrl(object):
    def __init__(self,topic='pwm_intensity_ctrl'):
        rospy.init_node('pwm_intensity_controller')

        self.publisher = rospy.Publisher(topic, Int32MultiArray, queue_size=100)
        rospy.on_shutdown(self.turn_off_pwm)

    def set_all_pwm(self, intensity):
        mode=-1
        msg=Int32MultiArray()
        msg.data=[mode,intensity]
        self.publisher.publish(msg)

    def set_pwm(self, pin, intensity):
        mode=pin
        msg=Int32MultiArray()
        msg.data=[mode,intensity]
        self.publisher.publish(msg)

    def turn_off_pwm(self):
        # r = rospy.Rate(1)
        mode=-1
        msg=Int32MultiArray()
        msg.data=[mode,0]
        # while not rospy.is_shutdown():
        self.publisher.publish(msg)
    def set_pwm_blink(self, intensity, duration, frame):
        mode =-2
        msg = Int32MultiArray()
        msg.data =[mode, intensity, duration, frame]
        self.publisher.publish(msg)



if __name__ == '__main__':

    pwm_intensity_ctrl = PWM_Intensity_Ctrl()