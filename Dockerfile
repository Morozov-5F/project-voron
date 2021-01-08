FROM ubuntu:latest

RUN apt-get update && \
    apt-install -y build-essential nasm grub2 xorriso

CMD bash