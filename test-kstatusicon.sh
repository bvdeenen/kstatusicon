#!/bin/bash

set -ex

./kstatusicon &
dbusid=org.kde.kstatusicon-$!
sleep 2
for x in arrow-left arrow-right arrow-up arrow-down
do
	qdbus $dbusid /TopLevel Set com.vandeenensupport.TopLevel icon $x
	sleep 1
done

qdbus $dbusid /MainApplication quit

