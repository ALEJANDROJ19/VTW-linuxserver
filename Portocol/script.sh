#!/bin/sh

#data=$(cat <<DATA
#{"VTWCONTROL":[{"REQUEST":"DISCOVERY"}]}
#DATA
#)
#header="Content-Type:application/json"
#wget -O- --post-data=$data --header=Content-Type:application/json "localhost:21211"

curl -H "Content-Type: application/json" -X POST -d '{"VTWCONTROL":[{"REQUEST":"DISCOVERY"}]}' localhost:21211