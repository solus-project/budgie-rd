#!/bin/bash

LIBDIR="/usr/lib"
MULTIARCH64="/usr/lib/x86_64-linux-gnu"
MULTIARCH32="/usr/lib/i686-linux-gnu"

if [[ -e /etc/os-release ]]; then
    source /etc/os-release
elif [[ -e /usr/lib/os-release ]]; then
    source /usr/lib/os-release
fi

if [[ "$ID" == "solus" ]]; then
    LIBDIR="/usr/lib64"
elif [[ "$ID" == "ubuntu" ]] || [[ "$ID_LIKE" == "ubuntu" ]]; then
    # Can likely simplify this jank and ask dpkg for the architecture
    if [[ `uname -m` == "x86_64" ]]; then
        LIBDIR="$MULTIARCH64"
    else
        LIBDIR="$MULTIARCH32"
    fi
else
    if [[ `uname -m` == "x86_64" ]] && [[ -e "/usr/lib64" ]]; then
        LIBDIR="/usr/lib64"
    fi
fi

if [[ ! -d build ]]; then
    echo "Configuring budgie-rd"
    meson build --prefix=/usr --sysconfdir=/etc --libdir=$LIBDIR
fi

echo "Building budgie-rd"
JOBCOUNT=$(getconf _NPROCESSORS_ONLN)
ninja -C build -j${JOBCOUNT}
