session_module_windowmanager_mocs = qt5.preprocess(
    moc_headers: [
        'service.h',
    ],
    include_directories: interface_include_directories,
)

session_module_windowmanager_sources = [
    'service.cpp',
    session_module_windowmanager_mocs,
]

session_module_windowmanager_includes = [
    config_h_dir,
    interface_include_directories,
    include_directories('.'),
]

# Windowing. It helps
session_module_windowmanager = shared_module(
    'windowmanager',
    install: true,
    install_dir: path_session_module_dir,
    sources: [
        session_module_windowmanager_sources,
    ],
    include_directories: session_module_windowmanager_includes,
    dependencies: [
        dep_qtcore,
    ],
)
