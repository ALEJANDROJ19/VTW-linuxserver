#!/bin/sh

#curl -H "Content-Type: application/json" -X POST -d '{"VTWCONTROL":[{"REQUEST":"DISCOVERY"}]}' localhost:21211

#curl -H "Content-Type: application/json" -X POST -d '{"VTWCONTROL":[{"REQUEST":"APP-REQUEST"}]}' localhost:21211

curl -H "Content-Type: application/json" -X POST -d '{"VTWCONTROL":[{"REQUEST":"START"},{"ID":"1"},{"OPTIONS":[]}]}' localhost:21211

#curl -H "Content-Type: application/json" -X POST -d '{"VTWCONTROL":[{"REQUEST":"STOP"},{"ID":"1"},{"OPTIONS":[]}]}' localhost:21211