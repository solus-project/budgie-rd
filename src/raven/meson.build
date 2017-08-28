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
        dep_kf5,
    ],
)

link_raven = declare_dependency(
    link_with: raven,
    include_directories: include_directories('.'),
)
