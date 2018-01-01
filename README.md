budgie-rd
---------

[![License](https://img.shields.io/badge/license-GNULGPLv2.1-blue.svg)](https://opensource.org/licenses/LGPL-2.1)

Research & Development repository for Budgie 11. Budgie 11 will be [based on Qt](https://budgie-desktop.org/2017/01/25/kicking-off-budgie-11/) and this
repository will help us to flesh out some concepts and architectural requirements for the
upcoming desktop work.

But yeah this will basically evolve into Budgie 11. Jump in. :P

Here Be Derghuns
-----------------

![derghuns](https://github.com/budgie-desktop/budgie-rd/raw/master/.github/landing.jpg)


Plan (rough)

 - Create `budgie-rd-session` component. This will load XDG autostart entries and
   any `desktop` session components from `/usr/share/budgie-session/desktop/*.desktop`
   We'll scope to allow multiple session _types_.
 - Have the session launch `kwin_x11` and `budgie-rd-shell`
 - Make `budgie-rd-shell` capable of launching a terminal and exiting the session
 - Factor reusable bits into libs (xdg, session comms, etc.)
 - Flesh out RD Shell with primitives (plugin building) and open the floor to
   rapid expansion. :P
 - Add our QPA plugins to provide consistent experience across the shell and
   all Qt applications.
 - Extend GTK to use our own stylised dialogs to match those of our QPA dialogs.


Core notions:

 - While Budgie Desktop is.. well, a desktop, it shouldn't scope limit itself to
   executing a pure-breed desktop session. The Budgie Shell should provide a
   data and service driven execution environment, exposing data and objects to
   any shell UX implementation.
 - In effect, this will allow us to support multiple Budgie modes, such as for
   OEM installers, first run, tutorial, "big screen", etc.
 - Basic widget providers (such as OSD and notification windows) should be reusable
   to help build these extra session types.
 


![logo](https://solus-project.com/imgs/budgie-small.png)

IRC: #budgie-desktop-dev on irc.freenode.net


Building
--------

Check the root `meson.build` for build dependencies. The `pkg-config` names are:

 - Qt5Widgets
 - Qt5Quick
 - Qt5QuickControls2

Additionally you will need development headers for `KWindowSystem`, as well as
the `meson` and `ninja` build tools.

To install these on Solus:

    sudo eopkg up
    sudo eopkg it -c system.devel qt5-base-devel qt5-declarative-devel qt5-quickcontrols2-devel kwindowsystem-devel


Now, let's configure the project (set libdir to appropriate libdir for your distro):

    meson build --prefix=/usr --sysconfdir=/etc --libdir=/usr/lib64
    ninja -j$(($(getconf _NPROCESSORS_ONLN)+1)) -C build

Testing
-------

For now, just run from git as we're not currently installing. This may change in
the near future, but we'll update the README to reflect this

    ./build/src/desktop/shell/budgie-rd-shell

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

To restore `budgie-wm`, use the above hints but with this command:

    budgie-wm --replace &


License
-------

budgie-rd is available under the terms of the LGPL-2.1 license. This will be changed
in future to a split GPL-2.0/LGPL-2.1 model to match Budgie Desktop.

Authors
=======

Copyright © 2017-2018 Budgie Desktop Developers

Budgie Desktop is primarily authored by the [Solus](https://solus-project.com) project which oversees
the development and leadership of the Budgie Desktop to ensure the delivery of a distribution agnostic
and open source Desktop Environment for everyone to enjoy and contribute to.
