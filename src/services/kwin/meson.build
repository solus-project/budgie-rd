plugin_kwin_mocs = qt5.preprocess(
    moc_headers: [
        'service.h',
        '../service-interface.h'
    ],
)

plugin_kwin_sources = [
    'service.cpp',
    plugin_kwin_mocs,
]

plugin_kwin_includes = [
    config_h_dir,
    shell_includes,
    include_directories('.'),
]

# Our main plugin_kwin is the execution environment
plugin_kwin = shared_module(
    'kwin',
    sources: [
        plugin_kwin_sources,
    ],
    include_directories: plugin_kwin_includes,
    dependencies: [
        dep_qtwidgets,
    ],
)
