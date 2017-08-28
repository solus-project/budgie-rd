kde_wanted_components = [
    'WindowSystem',
]

dep_kf5 = []

foreach kde_component: kde_wanted_components
    dep_tmp_lib = compiler.find_library('KF5' + kde_component)
    dep_tmp_kf5 = declare_dependency(
        dependencies: [
            dep_tmp_lib,
        ],
        include_directories: [
            include_directories('/usr/include/KF5/K' + kde_component),
        ],
    )
    dep_kf5 += dep_tmp_kf5
endforeach

shell_mocs = qt5.preprocess(
    moc_headers: [
        'desktop-manager.h',
        'root-window.h',
    ],
)

shell_qrc = qt5.preprocess(
    qresources: [
        'shell.qrc'
    ]
)

shell_sources = [
    'desktop-manager.cpp',
    'main.cpp',
    'root-window.cpp',
]

shell = executable(
    'budgie-shell',
    sources: [
        shell_sources,
        shell_qrc,
        shell_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
        dep_kf5,
        dep_qml,
        link_panel,
        link_raven,
    ],
)
