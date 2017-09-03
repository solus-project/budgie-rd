budgie-rd
---------

[![License](https://img.shields.io/badge/license-GNULGPLv2.1-blue.svg)](https://opensource.org/licenses/LGPL-2.1)

Research & Development repository for Budgie 11. Budgie 11 will be [based on Qt](https://budgie-desktop.org/2017/01/25/kicking-off-budgie-11/) and this
repository will help us to flesh out some concepts and architectural requirements for the
upcoming desktop work.

Here Be Derghuns
-----------------

![derghuns](https://github.com/budgie-desktop/budgie-rd/raw/master/.github/landing.jpg)


Note that this repository **in no way** should be considered representative of the
final work, nor does inclusion of a feature or technology in this repository mean
that it will be present in the final Budgie 11 tree.

Initial concerns:

 - Handle the root window display via our own `Desktop::RootWindow` class to
   take care of wallpaper settings, and in future, desktop icons.
 - Investigate the viability of KWin (or others)
 - Provide a new Raven (plugin based `Raven::Window`)
 - Port (conceptually) the PanelManager and Panel(Window) instance management,
   also plugin based.
 - Investigate the viability of Qt Quick (QML) to determine if the overhead continues
   to grow and whether it is justified.
 - Favour C++ native-code where possible
 - Keep tree modular with various libraries linked into a final shell process
 - Ensure compositor is separate to the shell!
 - Begin establishing a stable ABI pattern (`dptr` based headers, etc.)

Long story short we're looking to get to the "cheapest" MVP 0.0.1 in the shortest
amount of time, so that we can determine what a full (not complete..) session looks like.
This is an action-driven approach to solving some of the more tertiary issues early
on before committing to the "big works".

![logo](https://solus-project.com/imgs/budgie-small.png)

IRC: #budgie-desktop-dev on irc.freenode.net


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
    ninja -j$(($(getconf _NPROCESSORS_ONLN)+1)) -C build

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
