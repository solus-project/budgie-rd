panel_mocs = qt5.preprocess(
    moc_headers: [
        'manager.h',
        'window.h',
    ],
)

panel_sources = [
    'manager.cpp',
    'window.cpp',
]

panel = static_library(
    'panel',
    sources: [
        panel_sources,
        panel_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
        link_taskmon,
        kf5_deps,
    ],
)

link_panel = declare_dependency(
    link_with: panel,
    include_directories: include_directories('.'),
)
