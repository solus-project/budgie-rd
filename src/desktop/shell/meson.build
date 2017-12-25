shell_mocs = qt5.preprocess(
    moc_headers: [
        'desktop-manager.h',
        'icon-provider.h',
        'root-window.h',
    ],
)

shell_qrc = qt5.preprocess(
    qresources: [
        join_paths(meson.current_source_dir(), 'shell.qrc'),
    ]
)

shell_sources = [
    'desktop-manager.cpp',
    'icon-provider.cpp',
    'main.cpp',
    'root-window.cpp',
]

shell = executable(
    'budgie-rd-shell',
    install: true,
    sources: [
        shell_sources,
        shell_qrc,
        shell_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
        kf5_deps,
        dep_qml,
        dep_qml_controls,
        link_panel,
        link_raven,
    ],
)
