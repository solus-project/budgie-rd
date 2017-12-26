service_interface_mocs = qt5.preprocess(
    moc_headers: [
        'service-interface.h',
    ],
)

libservice_interface_includes = [
    include_directories('.'),
]

libservice_interface = shared_library(
    'budgie-service',
    sources: service_interface_mocs,
    install: true,
    dependencies: dep_qtwidgets,
    include_directories: libservice_interface_includes,
)

link_libservice_interface = declare_dependency(
    link_with: libservice_interface,
    dependencies: dep_qtwidgets,
    include_directories: libservice_interface_includes,
)


subdir('kwin')
