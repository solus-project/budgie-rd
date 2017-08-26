panel_mocs = qt5.preprocess(
    moc_headers: [
        'manager.h',
    ],
)

panel_sources = [
    'main.cpp',
    'manager.cpp',
]

panel = executable(
    'panel',
    sources: [
        panel_sources,
        panel_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
    ],
)
