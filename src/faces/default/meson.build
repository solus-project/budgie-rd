plugin_default_face_mocs = qt5.preprocess(
    moc_headers: [
        'face.h',
    ],
    include_directories: libface_interface_includes,
)

plugin_default_face_sources = [
    'face.cpp',
    plugin_default_face_mocs,
]

plugin_default_face_includes = [
    config_h_dir,
    libface_interface_includes,
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
        dep_qtwidgets,
    ],
)
