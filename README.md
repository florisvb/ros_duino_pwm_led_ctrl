# Firmare Installation

### Install ros arduino

http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

### Put this library in your arduino/libraries directory:

https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library

### Load firmware to mega

Load the firmware `ros_duino_pwm_led_ctrl/firmware/pwm_intensity_ctrl/pwm_intensity_ctrl.ino` onto the mega

### Catkin Make

After downloading this package into `~/catkin_ws/src` (or whatever your catkin workspace is called), run `catkin_make` from `~/catkin_ws`.

# Controlling the LEDs

1. Make sure `roscore` is running
2. Run rosserial: `rosrun rosserial_python serial_node.py /dev/ttyACM0` (or whatever the appropriate device ID is)
3. The following code will allow you to manually control all of the LEDs simultaneously in an ipython terminal
```python
import pwm_intensity_controller
pic = pwm_intensity_controller.PWM_Intensity_Ctrl()
pic.set_pwm(-1, 10) # set intensity of all channels to 10%
```
4. The following code will allow you to manually control individual LEDs in an ipython terminal
```python
import pwm_intensity_controller
pic = pwm_intensity_controller.PWM_Intensity_Ctrl()
pic.set_pwm(3, 10) # set intensity of channel 3 10%
```
5. To link LED control to other ROS processes, it is probably easiest to just publish directly to the appropriate topic. The code in pwm_intensity_controller can serve as a guide for how to do that. 

# Mode and Intensity

The PWM signals are controlled using messages like (mode, intensity). The firmware currently supports two modes:
1. Mode "-1" will control all of the LEDs to the same intensity.
2. Mode "integer" like mode "2" will control only channel 2. Note that the firmware needs to be updated to associate the correct board and pin number with a given channel. For example, each board has 16 pins. If you have more than 16 PWM devices, then the firmware will need to be updated so that, for example, channel 18 gets converted to board 2 pin 1. 
3. To make communication more efficient, additional modes such as "-2" could be implemented in the firmware to control several, but not all, LEDs together. 