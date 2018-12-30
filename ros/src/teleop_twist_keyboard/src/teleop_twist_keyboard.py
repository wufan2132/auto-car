#!/usr/bin/env python

from __future__ import print_function

import roslib; roslib.load_manifest('teleop_twist_keyboard')
import rospy

from car_msgs.msg import control_cmd

import sys, select, termios, tty

msg = """
Reading from the keyboard  and Publishing to Twist!
---------------------------
Moving around:
   q    w     
   a         d
        s     

CTRL-C to quit
"""

moveBindings = {
		'w':(0.5,0,0),
		'a':(0,0,300),
		'd':(0,0,-300),
		's':(0,1.5,0),
		'q':(0,2,0),
		}

def getKey():
	tty.setraw(sys.stdin.fileno())
	select.select([sys.stdin], [], [], 0)
	key = sys.stdin.read(1)
	termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
	return key

if __name__=="__main__":
	settings = termios.tcgetattr(sys.stdin)
	
	pub = rospy.Publisher('prius', control_cmd, queue_size = 1)
	rospy.init_node('teleop_twist_keyboard')
	throttle = 0
	throttle = 0
	brake = 0
	steer = 0
	status = 0

	try:
		print(msg)
		while(1):
			key = getKey()
			if key in moveBindings.keys():
				throttle += moveBindings[key][0]
				brake = moveBindings[key][1]
				steer = moveBindings[key][2]

			else:
				throttle = 0
				brake = 0
				steer = 0
				if (key == '\x03'):
					break

			twist = control_cmd()
			twist.throttle = throttle
			twist.brake = brake
			twist.steer = steer
			pub.publish(twist)

	except Exception as e:
		print(e)

	finally:
		twist = control_cmd()
		twist.throttle = 0
		twist.brake = 0
		twist.steer = 0
		pub.publish(twist)
		termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)


