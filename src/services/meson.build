libservice_interface_includes = [
    include_directories('.'),
]

# In future we may allow disabling some services
enabled_services = [
    'kwin',
    'notifications',
]

foreach service : enabled_services
    subdir(service)
endforeach
