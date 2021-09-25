#!/bin/bash

SCRIPT_DIR=$(dirname "$0")
SRC_DIR="${SCRIPT_DIR}/../src"
DST_DIR=/usr/local/bin

echo "Building program..."
gcc "${SRC_DIR}/tempalert.c" -o "${SRC_DIR}/tempalert"

if [[ $? -ne 0 ]] ; then
    echo "Failed to build program!"
    exit 1
fi

sudo mv "${SRC_DIR}/tempalert" "${DST_DIR}/tempalert"
sudo chmod 755 "${DST_DIR}/tempalert"

echo "Creating user for Tempalert..."
sudo adduser tempalert --no-create-home --disabled-login --shell /usr/sbin/nologin

if [[ ! -x /usr/lib/lsb/install_initd ]] ; then
    echo "Installing Linux Standard Base core support..."
    sudo apt install lsb_core -y
fi

sudo cp "${SCRIPT_DIR}/tempalert.sh" /etc/init.d/tempalert
sudo /usr/lib/lsb/install_initd /etc/init.d/tempalert

if [[ $? -ne 0 ]] ; then
    echo "Failed to setup init daemon!"
    exit 1
fi

sudo service tempalert start
