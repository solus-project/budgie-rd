plugin_default_face_mocs = qt5.preprocess(
    moc_headers: [
        'face.h',
    ],
    include_directories: interface_include_directories,
)

plugin_default_face_sources = [
    'face.cpp',
    plugin_default_face_mocs,
]

plugin_default_face_includes = [
    config_h_dir,
    interface_include_directories,
    include_directories('.'),
]

# Notification plugin
plugin_default_face = shared_module(
    'default',
    install: true,
    install_dir: path_face_plugin_dir,
    sources: [
        plugin_default_face_sources,
    ],
    include_directories: plugin_default_face_includes,
    dependencies: [
        link_libpanel,
        link_libraven,
        dep_qtwidgets,
    ],
)
