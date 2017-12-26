shell_sources = [
    'main.cpp',
]

shell_includes = [
    config_h_dir,
    include_directories('.'),
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
