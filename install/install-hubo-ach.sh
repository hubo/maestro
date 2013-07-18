#!/bin/bash
#
# This script installs Hubo-Ach and the Hubo-Ach-Ros interface for use with
# various ROS stacks. Additionally, the hubo-ach-ros-visualization package
# will be installed and configured.
#
# Options:
#
# Dependencies:
#
# Blacklist:
#
# Author: Solis Knight
# Date: July 2013

# Exit Error Codes
WRONG_NUMBER_ARGUMENTS=1
BAD_ARGUMENTS=2
NOT_FOUND=3
BLACKLIST_VIOLATED=4

# Change directory to the script's directory.
cd ${0%/*}

# Stop execution on any significant error.
#set -e

echo "Hubo-ACH - Maestro installation script"
echo "Version 1.0"
echo ""

DEPENDENCY_DIRS="/opt /opt/ros /opt/ros/fuerte /opt/ros/fuerte/stacks"
DEPENDENCY_FILES="/opt/ros/fuerte/setup.bash"
BLACKLISTED_DIRS="/opt/ros/fuerte/stacks/hubo-ach-ros
/opt/ros/fuerte/stacks/hubo-ach-ros-visualization"
BLACKLISTED_FILES=""

function see() {
        if [[ $# != 2 ]]; then
                return $WRONG_NUMBER_ARGUMENTS
        fi

        if [[ "$1" == "file" ]]; then
                if [[ ! -e "$2" || ! -f "$2" ]]; then
                        return $NOT_FOUND
                fi

        elif [[ "$1" == "dir" ]]; then
                if [[ ! -e "$2" || ! -d "$2" ]]; then
                        return $NOT_FOUND
                fi
        else
                return $BAD_ARGUMENTS
        fi

        return 0
}

for dir in $DEPENDENCY_DIRS; do
        see "dir" "$dir"
        retval=$?
        if [[ "$retval" != 0 ]]; then
                echo "Required dependency $dir was not found."
                exit $NOT_FOUND
        fi
done

for file in $DEPENDENCY_FILES; do
        see "file" "$file"
        retval=$?
        if [[ "$retval" != 0 ]]; then
                echo "Required dependency $file was not found."
                exit $NOT_FOUND
        fi
done

for dir in $BLACKLISTED_DIRS; do
        see "dir" "$dir"
        retval=$?
        if [[ "$retval" == 0 ]]; then
                echo "Blacklisted directory $dir was found."
                exit $BLACKLIST_VIOLATED
        fi
done

for file in $BLACKLISTED_FILES; do
        see "file" "$file"
        retval=$?
        if [[ "$retval" == 0 ]]; then
                echo "Blacklisted file $file was found."
                exit $BLACKLIST_VIOLATED
        fi
done


#Hubo-Ach
add-apt-repository "deb http://code.golems.org/ubuntu precise golems.org"
add-apt-repository "deb http://www.repo.danlofaro.com/release precise main"
apt-get update
apt-get install -y --force-yes --no-remove libach1 libach-dev ach-utils hubo-ach hubo-ach-dev

source /opt/ros/fuerte/setup.bash

#Hubo-Ach-Ros
cd /opt/ros/fuerte/stacks
git clone http://github.com/isaacgaretmia/hubo-ach-ros.git
cd hubo-ach-ros
git checkout maestro
rosmake hubo_ros

#Hubo-Ach-Ros-Visualization
cd /opt/ros/fuerte/stacks
git clone http://github.com/isaacgaretmia/hubo-ach-ros-visualization.git
cd hubo-ach-ros-visualization
git checkout maestro

cd /opt/ros/fuerte/stacks
rosmake hubo_ros hubo_ros_visualization maestro

