compositor_mocs = qt5.preprocess(
    moc_headers: [
        'manager.h',
        'server.h',
    ],
    include_directories: interface_include_directories,
)

compositor_sources = [
    'manager.cpp',
    'main.cpp',
    'server.cpp',
    compositor_mocs,
]

compositor_includes = [
    config_h_dir,
    include_directories('.'),
    interface_include_directories,
]

# Wayland compositor
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
