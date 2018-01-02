# In future we may allow more than one renderer
enabled_renderers = [
    'opengl',
]

path_renderer_plugin_dir = join_paths(path_plugin_dir, 'compositor')

foreach renderer : enabled_renderers
    subdir(renderer)
endforeach
