shell_mocs = qt5.preprocess(
    moc_headers: [
        'plugin.h',
        'registry.h',
        'shell.h',
    ],
    include_directories: interface_include_directories,
)

shell_sources = [
    'main.cpp',
    'plugin.cpp',
    'registry.cpp',
    'shell.cpp',
    shell_mocs,
]

shell_includes = [
    config_h_dir,
    include_directories('.'),
    interface_include_directories,
]

# Our main shell is the execution environment
shell = executable(
    'budgie-rd-shell',
    install: true,
    sources: [
        shell_sources,
    ],
    include_directories: shell_includes,
    dependencies: [
        dep_qtwidgets,
    ],
)
