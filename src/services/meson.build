libservice_interface_includes = [
    include_directories('.'),
]

# In future we may allow disabling some services
enabled_services = [
    'windowmanager',
    'notifications',
]

path_service_plugin_dir = join_paths(path_plugin_dir, 'services')

foreach service : enabled_services
    subdir(service)
endforeach
