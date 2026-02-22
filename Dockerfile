# Use Ubuntu 22.04 as base image
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install essential build tools and dependencies
# wine: for running Windows executables and msvc
# cmake, ninja-build: for building the project
# git, python3, curl: for setup scripts
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    python3 \
    python3-pip \
    curl \
    wget \
    unzip \
    wine \
    wine64 \
    software-properties-common \
    && rm -rf /var/lib/apt/lists/*

# Create working directory
WORKDIR /x64dbg

# Copy the current directory contents into the container
COPY . .

# Create a directory for MSVC (to be installed by user)
RUN mkdir -p /root/opt/msvc

# Set environment variables for the build (as per COMPILE-linux.md)
ENV MSVC_BIN_DIR=/root/opt/msvc/bin/x64
ENV QT_BIN_DIR=/x64dbg/build64/_deps/qt5-src/bin

# Default command
CMD ["/bin/bash"]
