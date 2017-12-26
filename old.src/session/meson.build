session_mocs = qt5.preprocess(
    moc_headers: [
        'manager.h',
    ],
)

session_sources = [
    'manager.cpp',
    'main.cpp',
]

session = executable(
    'budgie-rd-session',
    install: true,
    sources: [
        session_sources,
        session_mocs,
    ],
    dependencies: [
        link_xdg,
        dep_qtwidgets,
    ],
)

# X11 window manager
install_data(
    'wm.desktop',
    install_dir: sessiondir_desktop,
)
