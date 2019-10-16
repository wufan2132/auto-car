#!/usr/bin/env python
'''debugger ROS Node'''
import rospy
from std_msgs.msg import String
from car_msgs.msg import trajectory

def callback(data):
    '''debugger Callback Function'''
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.total_path_length)

def listener():
    '''debugger Subscriber'''
    # In ROS, nodes are uniquely named. If two nodes with the same
    # node are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('debugger', anonymous=True)

    rospy.Subscriber("trajectory_topic", trajectory, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()