libcommon_mocs = qt5.preprocess(
    moc_headers: [
        'plugin.h',
        'registry.h',
    ],
    include_directories: interface_include_directories,
)

libcommon_sources = [
    'plugin.cpp',
    'registry.cpp',
    libcommon_mocs,
]

libcommon_includes = [
    config_h_dir,
    interface_include_directories,
    include_directories('.'),
]

# Access to common APIs for various Budgie components
libcommon = shared_library(
    'budgie-common',
    version: '0.0.0',
    install: true,
    sources: [
        libcommon_sources,
    ],
    include_directories: libcommon_includes,
    dependencies: [
        dep_qtcore,
    ],
)

link_libcommon = declare_dependency(
    link_with: libcommon,
    include_directories: libcommon_includes,
    dependencies: dep_qtcore,
)
