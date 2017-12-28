session_module_shell_mocs = qt5.preprocess(
    moc_headers: [
        'service.h',
    ],
    include_directories: interface_include_directories,
)

session_module_shell_sources = [
    'service.cpp',
    session_module_shell_mocs,
]

session_module_shell_includes = [
    config_h_dir,
    interface_include_directories,
    include_directories('.'),
]

# Windowing. It helps
session_module_shell = shared_module(
    'shell',
    install: true,
    install_dir: path_session_module_dir,
    sources: [
        session_module_shell_sources,
    ],
    include_directories: session_module_shell_includes,
    dependencies: [
        dep_qtcore,
    ],
)
