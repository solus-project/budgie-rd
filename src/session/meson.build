session_mocs = qt5.preprocess(
    moc_headers: [
        'session.h',
        'session-registry.h',
    ],
    include_directories: interface_include_directories,
)

session_sources = [
    'main.cpp',
    'session.cpp',
    'session-registry.cpp',
    session_mocs,
]

session_includes = [
    config_h_dir,
    include_directories('.'),
    interface_include_directories,
]

# Our main session binary launches the shell and xdg apps
session = executable(
    'budgie-rd-session',
    install: true,
    sources: [
        session_sources,
    ],
    include_directories: session_includes,
    dependencies: [
        link_libcommon,
        dep_qtcore,
    ],
)
