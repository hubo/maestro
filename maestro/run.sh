#!/bin/bash
export PYTHONPATH=/opt/ros/diamondback/stacks/openrave_planning/openrave/lib/python2.7/site-packages/:$PYTHONPATH
cp src/test.py /opt/ros/diamondback/stacks/openrave_planning/openrave_robot_control/.
roslaunch openrave_robot_control jaemi_hubo.launch.xml
