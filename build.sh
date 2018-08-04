#!/bin/bash

IMAGE_NAME="ask/augrel"
IMAGE_VERSION="0.1"
CONTAINER_NAME="augrel_c1"
MOUNT_PATH="/home/augrel"


## Build image
if [[ $1 -eq 0 ]]; then
	docker stop $CONTAINER_NAME
	docker rm $CONTAINER_NAME
	docker rmi $(docker images --filter "dangling=true" -q --no-trunc)
	# docker rmi $(docker images -a|grep "<none>"|awk '$1=="<none>" {print $3}')
	docker rmi $IMAGE_NAME:$IMAGE_VERSION
	docker build --build-arg DISPLAY=$DISPLAY -t $IMAGE_NAME:$IMAGE_VERSION .
fi

## Start container
if [[ $1 -eq 1 ]]; then
	docker stop $CONTAINER_NAME
	docker rm $CONTAINER_NAME

	## If docker image does not start sshd daemon
	# xhost +
	# docker run --rm -dit -p 3022:22 -p 7777:7777 -p 9999:9999 -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY --security-opt seccomp:unconfined --name $CONTAINER_NAME -v "$(pwd)":$MOUNT_PATH $IMAGE_NAME:$IMAGE_VERSION
	# docker attach $CONTAINER_NAME

	## If docker image starts sshd daemon
	docker run --rm -d -p 3022:22 -p 7777:7777 -p 9999:9999 -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY --security-opt seccomp:unconfined --name $CONTAINER_NAME -v "$(pwd)":$MOUNT_PATH $IMAGE_NAME:$IMAGE_VERSION
	ssh -X root@127.0.0.1 -p 3022
fi
