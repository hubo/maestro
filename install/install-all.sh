#!/bin/bash
#
# Comprehensive install script for Maestro, and all dependencies.
# Installs Ros Fuerte, Orocos, OpenRAVE, Maestro, Hubo-Ach, OpenHubo.
#
# Options: None
# Dependencies:
#	<Maestro Install Dir>/maestro/utils.sh
#	install-fuerte.sh
#	install-hubo-ach.sh
#	install-openHubo.sh
#
# Author: Solis Knight
# Date: July 2013
#

# Change directory to the script's directory
cd ${0%/*}

source ../maestro/utils.sh

#set -e
echo "Comprehensive Install Script for Maestro"
echo "Version $VERSION"
echo ""

DEPENDENCY_DIRS=""
DEPENDENCY_FILES="install-fuerte.sh install-hubo-ach.sh install-openHubo.sh"
BLACKLISTED_DIRS=""
BLACKLISTED_FILES=""

check dependency dir "$DEPENDENCY_DIRS"
if [[ $? != 0 ]]; then exit $?; fi
check dependency file "$DEPENDENCY_FILES"
if [[ $? != 0 ]]; then exit $?; fi
check blacklist dir "$BLACKLISTED_DIRS"
if [[ $? != 0 ]]; then exit $?; fi
check blacklist file "$BLACKLISTED_FILES"
if [[ $? != 0 ]]; then exit $?; fi

echo "Dependencies satisfied."
echo "Installing ROS-Orocos-Maestro..."
sudo bash install-fuerte.sh -y
echo "Installing Hubo-ACH..."
sudo bash install-hubo-ach.sh
echo "Installing OpenHUBO..."
bash install-openHubo.sh

echo "Install Complete. Exiting..."
