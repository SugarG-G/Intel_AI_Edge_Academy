#!/bin/bash
SERVIP=10.10.141.248                   #xx : ubuntu nfs host ip
if ! df | grep lect_nfs > /dev/null ; then
	ping -c 1 $SERVIP > /dev/null
	if [ $? -eq 0 ] ; then
		sudo mount -t nfs $SERVIP:/srv/nfs /mnt/lect_nfs
		df | grep lect_nfs
	fi
fi
