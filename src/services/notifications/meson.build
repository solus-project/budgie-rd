plugin_notifications_mocs = qt5.preprocess(
    moc_headers: [
        'service.h',
    ],
    include_directories: libservice_interface_includes,
)

plugin_notifications_sources = [
    'service.cpp',
    plugin_notifications_mocs,
]

plugin_notifications_includes = [
    config_h_dir,
    libservice_interface_includes,
    include_directories('.'),
]

# Notification plugin
plugin_notifications = shared_module(
    'notifications',
    install: true,
    install_dir: service_plugin_dir,
    sources: [
        plugin_notifications_sources,
    ],
    include_directories: plugin_notifications_includes,
    dependencies: [
        dep_qtwidgets,
    ],
)
