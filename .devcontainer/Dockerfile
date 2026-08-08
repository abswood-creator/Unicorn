FROM ubuntu:rolling

RUN apt-get update && apt-get upgrade && apt-get install -y \
    sudo \
    
RUN sudo apt-get install -y \
    build-essential \
    g++ \
    git \
    && rm -rf /var/lib/apt/lists/*
