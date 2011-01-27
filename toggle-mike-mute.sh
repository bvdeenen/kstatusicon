#!/bin/bash

# script called via a hotkey to mute or unmute the microphone. Uses
# kstatusicon in the PATH.

set -e
qdb="qdbus org.kde.kmix /Mixer0"
mute=$($qdb mute Front_Mic:0) # true or false

if [ "$mute" == "true" ] ; then
	newmute=0
	mesg=activated
else
	newmute=1
	mesg=disabled
fi
$qdb setMute Front_Mic:0 $newmute

notify-send "Microphone is now $mesg"

myname=toggle_mike
theid=""
for dbusid in $(qdbus "org.kde.kstatusicon*" ) 
do
	thename=$(qdbus $dbusid /TopLevel Get com.vandeenensupport.TopLevel name)
	if [ $myname == "$thename" ] ; then theid=$dbusid; fi	
done

if [  "$theid" == "" ] ; then
	kstatusicon $myname &
	theid=org.kde.kstatusicon-$!
fi	

icon[0]="audio-input-microphone"
icon[1]=audio-volume-muted

qdbus $theid /TopLevel Set com.vandeenensupport.TopLevel icon ${icon[$newmute]}
