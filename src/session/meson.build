session_sources = [
    'main.cpp',
]

session_includes = [
    config_h_dir,
    include_directories('.'),
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
        dep_qtcore,
    ],
)
