taskmon_mocs = qt5.preprocess(
    moc_headers: [
        'task-monitor.h',
        'window.h',
    ],
)

taskmon_sources = [
    'task-monitor.cpp',
    'window.cpp',
]

taskmon = static_library(
    'taskmon',
    sources: [
        taskmon_sources,
        taskmon_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
        kf5_deps,
    ],
)

link_taskmon = declare_dependency(
    link_with: taskmon,
    include_directories: include_directories('.'),
)
