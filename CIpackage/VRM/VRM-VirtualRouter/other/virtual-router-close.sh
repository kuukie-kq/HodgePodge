#!/bin/bash
ps -ef | grep VirtualNorth.jar | awk '{print $2}' | xargs kill -9
ps -ef | grep VirtualSouth.jar | awk '{print $2}' | xargs kill -9
