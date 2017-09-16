panel_mocs = qt5.preprocess(
    moc_headers: [
        'applet.h',
        'manager.h',
        'window.h',
        'clock/clock.h',
        'tasklist/taskbutton.h',
        'tasklist/tasklist.h',
    ],
)

panel_sources = [
    'applet.cpp',
    'manager.cpp',
    'window.cpp',
    'clock/clock.cpp',
    'tasklist/taskbutton.cpp',
    'tasklist/tasklist.cpp',
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
