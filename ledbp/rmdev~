#!/bin/sh
module=$1
/sbin/rmmod $module || exit 1
rm -f /dev/$module
echo "=> Device /dev/$module removed"
