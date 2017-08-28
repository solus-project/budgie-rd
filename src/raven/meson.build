raven_mocs = qt5.preprocess(
    moc_headers: [
        'raven.h',
    ],
)

raven_sources = [
    'raven.cpp',
]

raven = static_library(
    'raven',
    sources: [
        raven_sources,
        raven_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
    ],
)

link_raven = declare_dependency(
    link_with: raven,
    include_directories: include_directories('.'),
)
