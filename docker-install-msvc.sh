#!/bin/bash
set -e

# Based on COMPILE-linux.md instructions

# Check if running in Docker or Linux
if [ ! -f "/.dockerenv" ]; then
    echo "Warning: Not running inside Docker container. This script is designed for the Docker environment."
fi

# Create directory for MSVC
mkdir -p ~/opt/msvc
cd ~/opt

# Clone msvc-wine
if [ ! -d "msvc-wine" ]; then
    echo "Cloning msvc-wine..."
    git clone https://github.com/mstorsjo/msvc-wine.git
fi

cd msvc-wine

# Download and install MSVC
echo "Downloading MSVC components (this may take a while)..."
# Note: User must accept license. We add --accept-license here assuming user agrees by running this script.
python3 ./vsdownload.py --accept-license --dest ~/opt/msvc Microsoft.VisualStudio.Workload.VCTools Microsoft.VisualStudio.Component.VC.ATL

echo "Installing MSVC..."
./install.sh ~/opt/msvc

echo "MSVC installation complete."
