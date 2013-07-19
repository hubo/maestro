#!/bin/bash
#
# This utility script houses some common environment-checking code meant to
# make scripts more robust. Includes functions to attempt to find files and
# folders in current directory, as well as crawl through dependencies and
# blacklists.
#
# Author: Solis Knight
# Date: July 2013
#
#

VERSION="2.0"

# Exit Error Codes
SUCCESS=0
WRONG_NUMBER_ARGUMENTS=1
BAD_ARGUMENTS=2
NOT_FOUND=3
BLACKLIST_VIOLATED=4

# Function see
# Attempts to find an item, given a qualified name. (Including path)
#
# Arguments: 2
# $1: Mode: either "file" or "dir"
# $2: Name: name of file or directory to see
#
# Returns: 4
# $SUCCESS - item was found.
# $WRONG_NUMBER_ARGUMENTS - there were not exactly 2 arguments provided.
# $BAD_ARGUMENTS - The first argument was not a valid record type.
# $NOT_FOUND - The item was not found.
#
# Author: Solis Knight
# Date: July 2013
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

        return $SUCCESS
}

# Function check
# Crawls through a list of files or directories, and reports issues. Supports
# dependency checks and blacklisting.
# Dependencies will throw an error if not found.
# Blacklisted items will throw an error if found.
#
# Arguments: 3
# $1: Mode: either "dependency" or "blacklist"
# $2: Type: either "file" or "dir" - see function "see"
# $3: Names: list of files or directories to check
#
# Returns: 5
# $SUCCESS - dependencies satisfied, blacklist not violated.
# $WRONG_NUMBER_ARGUMENTS - there were not exactly 3 arguments provided.
# $BAD_ARGUMENTS - The mode or type specified was not valid.
# $NOT_FOUND - A required dependency was not found.
# $BLACKLIST_VIOLATED - A blacklisted item was found.
#
# Author: Solis Knight
# Date: July 2013
function check() {
	if [[ $# != 3 ]]; then
                return $WRONG_NUMBER_ARGUMENTS
        fi

	DEPENDENCY=0
	BLACKLIST=1

	case "$1" in
	"dependency" )
		MODE=$DEPENDENCY;;
	"blacklist" )
		MODE=$BLACKLIST;;
	*)
		return $BAD_ARGUMENTS
	esac

	for item in $3; do
		see "$2" "$item"
		retval=$?
		case $retval in
		$WRONG_NUMBER_ARGUMENTS )
			return $retval;;
		$BAD_ARGUMENTS )
			return $retval;;
		$NOT_FOUND )
			if [[ $MODE = $DEPENDENCY ]]; then
				echo "Required dependency $item was not found."
				return $NOT_FOUND
			fi 
			;;
		$SUCCESS )
			if [[ $MODE = $BLACKLIST ]]; then
				echo "Blacklsited $1 $item was found."
				return $BLACKLIST_VIOLATED
			fi
			;;
		*)
			return $NOT_FOUND
		esac
        done
	return $SUCCESS
}

# Function cdHere
# Normalizes the current working directory by moving to the directory of the 
# calling script.
#
# Arguments: 1
# $1: Script path - this function should be called with "$0" as the argument.
#
# Returns: 3
# $SUCCESS - Successful cd
# $WRONG_NUMBER_ARGUMENTS - there was not exactly 1 argument provided.
# $? - If cd returns an error, it will be passed to the caller.
#
# Author: Solis Knight
# Date: July 2013
function cdHere() {
	if [[ $# != 1 ]]; then
                return $WRONG_NUMBER_ARGUMENTS
        fi

	cd ${1%/*}
	return $?
}

# Function currentBranch
# Stores the name of the current git branch into the passed-in variable.
#
# Arguments: 1
# $1: Return_val - variable to store the branch name into.
#
# Returns: 1
# $SUCCESS - Successful `git branch`
# $WRONG_NUMBER_ARGUMENTS - there was not exactly 1 argument provided.
# $? - If `git branch` returns an error, it will be passed to the caller.
#
# Author: Solis Knight
# Date: July 2013
function currentBranch() {
	#if [[ $# != 1 ]]; then
	#	return $WRONG_NUMBER_ARGUMENTS
    #fi

	# Store the name of the current branch into the passed-in variable
	#Command Substitution Method
	OUTPUT=`git branch`
	if [[ $? != 0 ]]; then return $?; fi
	OUTPUT=${OUTPUT##*\*\ }
	OUTPUT=${OUTPUT%%[[:space:]]*}
	eval "$1=$OUTPUT"
	return $SUCCESS

	# Store the name of the current branch into passed-in variable
	# Grep | Sed method
	#eval "$1=`git branch | grep "^\*" | sed "s/..//"`"
	#return $SUCCESS
}
