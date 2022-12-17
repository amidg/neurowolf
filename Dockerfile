FROM ubuntu:latest
# run latest LTS ubuntu, aka 22.04 image

RUN apt-get -qq update && \
    apt-get -qq install -y g++ make binutils cmake libssl-dev libboost-system-dev libcurl4-openssl-dev zlib1g-dev git 

RUN git clone --recurse-submodules https://github.com/amidg/neurowolf.git -b gen2

# setup telegram bot C++ libraries
WORKDIR /usr/src/neurowolf

WORKDIR /usr/src/tgbot-cpp
COPY include include
COPY src src
COPY CMakeLists.txt ./

RUN cmake . && \
    make -j$(nproc) && \
    make install && \
    rm -rf /usr/src/tgbot-cpp/*

# setup OpenCV libraries


# compile the neurowolf code 


# run neurowolf bot
