#!/usr/bin/env python

from __future__ import print_function

import roslib; roslib.load_manifest('teleop_twist_keyboard')
import rospy

from car_msgs.msg import control

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
		'w':(10,0,0),
		'a':(10,0,3),
		'd':(10,0,-3),
		's':(-10,0,0),
		'q':(0,10,0),
		}

def getKey():
	tty.setraw(sys.stdin.fileno())
	select.select([sys.stdin], [], [], 0)
	key = sys.stdin.read(1)
	termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
	return key

if __name__=="__main__":
	settings = termios.tcgetattr(sys.stdin)
	
	pub = rospy.Publisher('chassisCommand_topic', car_msgs, queue_size = 1)
	rospy.init_node('teleop_twist_keyboard')
	throttle = 0
	throttle = 0
	brake = 0
	steering = 0
	status = 0

	try:
		print(msg)
		while(1):
			key = getKey()
			if key in moveBindings.keys():
				throttle = moveBindings[key][0]
				brake = moveBindings[key][1]
				steering = moveBindings[key][2]

			else:
				throttle = 0
				brake = 0
				steering = 0
				if (key == '\x03'):
					break

			twist = car_msgs()
			twist.throttle = throttle
			twist.brake = brake
			twist.steering = steering
			pub.publish(twist)

	except Exception as e:
		print(e)

	finally:
		twist = car_msgs()
		twist.throttle = 0
		twist.brake = 0
		twist.steering = 0
		pub.publish(twist)

		termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)


