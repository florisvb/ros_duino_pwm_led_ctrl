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
pwm_intensity_ctrl.set_pwm(-1, 10) # set intensity of all channels to 10%
```
4. The following code will allow you to manually control individual LEDs in an ipython terminal
```python
import pwm_intensity_controller
pic = pwm_intensity_controller.PWM_Intensity_Ctrl()
pwm_intensity_ctrl.set_pwm(3, 10) # set intensity of channel 3 10%
```