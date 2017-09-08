session_mocs = qt5.preprocess(
    moc_headers: [
        'desktop-file.h',
        'manager.h',
    ],
)

session_sources = [
    'desktop-file.cpp',
    'manager.cpp',
    'main.cpp',
]

session = executable(
    'budgie-rd-session',
    sources: [
        session_sources,
        session_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
    ],
)

# X11 window manager
install_data(
    'wm.desktop',
    install_dir: sessiondir_desktop,
)
