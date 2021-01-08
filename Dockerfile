# Copyright (c) 2021, Evgeniy Morozov
# All rights reserved.
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
FROM ubuntu:latest

RUN apt-get update && \
    apt-install -y build-essential nasm grub2 xorriso

CMD bash