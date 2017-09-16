xdg_mocs = qt5.preprocess(
    moc_headers: [
        'desktop-file.h',
    ],
)

xdg_sources = [
    'desktop-file.cpp',
]

xdg = static_library(
    'xdg',
    sources: [
        xdg_sources,
        xdg_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
    ],
)

link_xdg = declare_dependency(
    link_with: xdg,
    include_directories: include_directories('.'),
)
