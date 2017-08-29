budgie-rd
---------

[![License](https://img.shields.io/badge/license-GNULGPLGv2.1-blue.svg)](https://opensource.org/licenses/LGPL-2.1)

Simple R&D test repo for some Budgie 11 stuff ...

Building
--------

Check the root `meson.build` for build dependencies. The `pkg-config` names are:

 - Qt5Widgets
 - Qt5Quick

Additionally you will need development headers for `KWindowSystem`, as well as
the `meson` and `ninja` build tools.

To install these on Solus:

    sudo eopkg up
    sudo eopkg it -c system.devel qt5-base-devel qt5-declarative-devel kwindowsystem-devel


Now, let's configure the project:

    meson build
    ninja -j$(($(getconf _NPROCESSORS_ONLN)+1)) build

Testing
-------

For now, just run from git as we're not currently installing. This may change in
the near future, but we'll update the README to reflect this

    ./build/src/shell/budgie-shell

Using KWin
----------

Currently we're testing integration with KWin. Note that this will break integration
in your existing Budgie desktop install (Or other non-KWin desktops). We're testing
various effects (such as blur behind) and considering it for the Wayland angle,
given the use of the `KWindowSystem` KF5 module.


To temporarily switch to Kwin:

    kwin_x11 --replace --no-kactivities &

If you're using bash, prepend the command with `nohup`, if you're using zsh,
suffix it with an extra bang (`!`) to ensure that when you close the terminal with CTRL+D
the `kwin_x11` process isn't aborted.

To restore `budige-wm`, use the above hints but with this command:

    budgie-wm --replace &


License
-------

budgie-rd is available under the terms of the LGPL-2.1 license. This will be changed
in future to a split GPL-2.0/LGPL-2.1 model to match Budgie Desktop.

Authors
=======

Copyright © 2017 Budgie Desktop Developers

Budgie Desktop is primarily authored by the [Solus](https://solus-project.com) project which oversees
the development and leadership of the Budgie Desktop to ensure the delivery of a distribution agnostic
and open source Desktop Environment for everyone to enjoy and contribute to.
