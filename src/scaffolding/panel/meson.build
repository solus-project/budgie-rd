libpanel_mocs = qt5.preprocess(
    moc_headers: [
        'manager.h',
        'window.h',
    ],
    include_directories: interface_include_directories,
)

libpanel_sources = [
    'manager.cpp',
    'window.cpp',
    libpanel_mocs,
]

libpanel_includes = [
    config_h_dir,
    interface_include_directories,
    include_directories('.'),
]

# Notification plugin
libpanel = shared_library(
    'budgie-panel',
    version: '0.0.0',
    install: true,
    sources: [
        libpanel_sources,
    ],
    include_directories: libpanel_includes,
    dependencies: [
        dep_qtwidgets,
        kf5_deps,
    ],
)

link_libpanel = declare_dependency(
    link_with: libpanel,
    include_directories: libpanel_includes,
    dependencies: dep_qtwidgets,
)
