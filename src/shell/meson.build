shell_mocs = qt5.preprocess(
    moc_headers: [
        'desktop-manager.h',
    ],
)

shell_sources = [
    'desktop-manager.cpp',
    'main.cpp',
]

shell = executable(
    'budgie-shell',
    sources: [
        shell_sources,
        shell_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
        link_panel,
        link_raven,
    ],
)
