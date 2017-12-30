compositor_mocs = qt5.preprocess(
    moc_headers: [
        'compositor.h',
    ],
    include_directories: interface_include_directories,
)


compositor_sources = [
    'compositor.cpp',
    'main.cpp',
    compositor_mocs,
]

compositor_includes = [
    config_h_dir,
    include_directories('.'),
    interface_include_directories,
]

# Our main compositor is the execution environment
compositor = executable(
    'budgie-rd-compositor',
    install: true,
    sources: [
        compositor_sources,
    ],
    include_directories: compositor_includes,
    dependencies: [
        dep_qt_compositor,
        dep_qtcore,
    ],
)
