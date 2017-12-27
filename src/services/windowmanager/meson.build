plugin_windowmanager_mocs = qt5.preprocess(
    moc_headers: [
        'service.h',
    ],
    include_directories: interface_include_directories,
)

plugin_windowmanager_sources = [
    'service.cpp',
    plugin_windowmanager_mocs,
]

plugin_windowmanager_includes = [
    config_h_dir,
    interface_include_directories,
    include_directories('.'),
]

# Windowing. It helps
plugin_windowmanager = shared_module(
    'windowmanager',
    install: true,
    install_dir: path_service_plugin_dir,
    sources: [
        plugin_windowmanager_sources,
    ],
    include_directories: plugin_windowmanager_includes,
    dependencies: [
        dep_qtwidgets,
    ],
)
