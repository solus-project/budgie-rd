libraven_mocs = qt5.preprocess(
    moc_headers: [
        'raven-window.h',
    ],
    include_directories: interface_include_directories,
)

libraven_sources = [
    'raven-window.cpp',
    libraven_mocs,
]

libraven_includes = [
    config_h_dir,
    interface_include_directories,
    include_directories('.'),
]

# Notification plugin
libraven = shared_library(
    'budgie-raven',
    version: '0.0.0',
    install: true,
    sources: [
        libraven_sources,
    ],
    include_directories: libraven_includes,
    dependencies: [
        dep_qtwidgets,
        kf5_deps,
    ],
)

link_libraven = declare_dependency(
    link_with: libraven,
    include_directories: libraven_includes,
    dependencies: dep_qtwidgets,
)
