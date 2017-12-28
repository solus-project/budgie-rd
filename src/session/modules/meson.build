# In future we may allow disabling some modules
enabled_modules = [
    'windowmanager',
    'shell',
]

path_session_module_dir = join_paths(path_plugin_dir, 'session')

foreach module : enabled_modules
    subdir(module)
endforeach
