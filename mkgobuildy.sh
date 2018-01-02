#!/bin/bash

# Brain-dead default library directory
LIBDIR="/usr/lib"

if [[ -e /etc/os-release ]]; then
    source /etc/os-release
elif [[ -e /usr/lib/os-release ]]; then
    source /usr/lib/os-release
fi

# Let's deal with the Debian family special case, since they like being different...
if [[ "$ID_LIKE" == "debian" ]]; then
    # We'll just ask dpkg for the architecture
    LIBDIR=`dpkg-architecture -qDEB_HOST_MULTIARCH`
else
    # Everyone but Debian follows LSB FHS, so we'll just check if it's a known 64-bit arch and /usr/lib64 is in use...
    if ([[ `uname -m` == "x86_64" ]] || [[ `uname -m` == "aarch64" ]] || [[ `uname -m` =~ "ppc64" ]]) && [[ -e "/usr/lib64" ]]; then
        LIBDIR="/usr/lib64"
    fi
fi

if [[ ! -d build ]]; then
    echo "Configuring budgie-rd"
    meson build --prefix=/usr --sysconfdir=/etc --libdir=$LIBDIR --buildtype debugoptimized
fi

echo "Building budgie-rd"
JOBCOUNT=$(getconf _NPROCESSORS_ONLN)
ninja -C build -j${JOBCOUNT}
