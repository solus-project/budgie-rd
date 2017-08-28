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

panel_mocs = qt5.preprocess(
    moc_headers: [
        'manager.h',
        'window.h',
    ],
)

panel_sources = [
    'main.cpp',
    'manager.cpp',
    'window.cpp',
]

panel = library(
    'panel',
    sources: [
        panel_sources,
        panel_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
        dep_kf5,
    ],
)

link_panel = declare_dependency(
    link_with: panel,
    include_directories: include_directories('.'),
)
