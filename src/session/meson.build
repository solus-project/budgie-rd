session_mocs = qt5.preprocess(
    moc_headers: [
        'manager.h',
    ],
)

session_sources = [
    'manager.cpp',
    'main.cpp',
]

session = executable(
    'budgie-rd-session',
    sources: [
        session_sources,
        session_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
    ],
)
