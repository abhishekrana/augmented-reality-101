FROM ubuntu:18.04

WORKDIR /home/lib

## Install dependencies
RUN apt-get update && apt-get install -y \
	openssh-server \
	vim \
	locate \
 	git \
    wget \
 	cmake \
	unzip \
	gdbserver \
	build-essential
# 	firefox


## SSH config. Username:root, Password:root
RUN mkdir /var/run/sshd
RUN echo 'root:root' | chpasswd
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

## SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd


# Prevents GLFW init failure (if we ssh into the container and initialize GLFW)
ARG DISPLAY
RUN echo "export DISPLAY="$DISPLAY >> /etc/profile


## Install OpenGL and dependencies
RUN apt-get install -y \
	build-essential \
	libgl1-mesa-dev \
	xorg-dev
#	freeglut3-dev

## Install GLEW
RUN wget https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.tgz && \
	tar -xzvf glew-2.1.0.tgz && \
	rm -rf glew-2.1.0.tgz && \
	cd glew-2.1.0/build/cmake && \
	cmake . && \
	make && \
	make install

## Install GLFW
RUN wget https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip && \
	unzip glfw-3.2.1.zip && \
	rm -rf glfw-3.2.1.zip && \
	cd glfw-3.2.1 && \
	mkdir build && \
	cd build && \
	cmake .. && \
	make && \
	make install

## Install GLM
RUN wget https://github.com/g-truc/glm/releases/download/0.9.9.0/glm-0.9.9.0.zip && \
	unzip glm-0.9.9.0.zip && \
	rm -rf glm-0.9.9.0.zip && \
	cd glm && \
	mkdir build && \
	cd build && \
	cmake .. && \
	make && \
	make install

## Install GLM
RUN wget ftp://ftp.freedesktop.org/pub/mesa/glu/glu-9.0.0.tar.bz2 && \
	tar -xjvf glu-9.0.0.tar.bz2 && \
	rm -rf glu-9.0.0.tar.bz2 && \
	cd glu-9.0.0 && \
	./configure --disable-static && \
	make && \
	make install


WORKDIR /home/augrel


# Port 22 will be used to SSH into the container,
# Port 7777 is used to run gdbserver program that allows to debug the program remotely.
# Port 9999 can be used to connect to the program from outside
EXPOSE 22 7777 9999
CMD ["/usr/sbin/sshd", "-D"]


## NOTE:
# Using the sshd daemon to spawn shells makes it complicated to pass environment variables to the user’s shell via the normal Docker mechanisms, as sshd scrubs the environment before it starts the shell.
# If you’re setting values in the Dockerfile using ENV, you need to push them to a shell initialization file like the /etc/profile example in the Dockerfile below.
# If you need to pass docker run -e ENV=value values, you need to write a short script to do the same before you start sshd -D and then replace the CMD with that script.
#ENV NOTVISIBLE "in users profile"

