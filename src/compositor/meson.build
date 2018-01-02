compositor_includes = [
    config_h_dir,
    include_directories('.'),
    interface_include_directories,
]

libcompositor_mocs = qt5.preprocess(
    moc_headers: [
        'window.h',
    ],
    include_directories: interface_include_directories,
)

libcompositor_sources = [
    'display.cpp',
    libcompositor_mocs,
]

# Shared library contains various stub implementations to help in writing
# our plugins. 
libcompositor = shared_library(
    'budgie-compositor-shared',
    version: '0.0.0',
    install: true,
    sources: [
        libcompositor_sources,
    ],
    include_directories: compositor_includes,
    dependencies: [
        dep_qtcore,
        dep_qt_compositor,
    ],
)

link_libcompositor = declare_dependency(
    link_with: libcompositor,
    include_directories: compositor_includes,
    dependencies: [
        dep_qtcore,
        dep_qt_compositor,
    ]
)

compositor_mocs = qt5.preprocess(
    moc_headers: [
        'compositor-registry.h',
        'manager.h',
        'server.h',
    ],
    include_directories: interface_include_directories,
)

compositor_sources = [
    'compositor-registry.cpp',
    'manager.cpp',
    'main.cpp',
    'server.cpp',
    compositor_mocs,
]

# Main compositor binary
compositor = executable(
    'budgie-rd-compositor',
    install: true,
    sources: [
        compositor_sources,
    ],
    include_directories: compositor_includes,
    dependencies: [
        link_libcommon,
        link_libcompositor,
        dep_qt_compositor,
        dep_qtcore,
    ],
)
