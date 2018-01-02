renderer_opengl_mocs = qt5.preprocess(
    moc_headers: [
        'renderer.h',
        'renderer-display.h',
    ],
    include_directories: interface_include_directories,
)

renderer_opengl_sources = [
    'renderer.cpp',
    'renderer-display.cpp',
    renderer_opengl_mocs,
]

renderer_opengl_includes = [
    config_h_dir,
    interface_include_directories,
    include_directories('.'),
]

# Notification renderer
renderer_opengl = shared_module(
    'opengl-renderer',
    install: true,
    install_dir: path_renderer_plugin_dir,
    sources: [
        renderer_opengl_sources,
    ],
    include_directories: renderer_opengl_includes,
    dependencies: [
        link_libcompositor,
        dep_qtwidgets,
        dep_qt_compositor,
    ],
)
