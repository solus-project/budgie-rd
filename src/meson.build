# We need to declare the interface directory first
# for the include_directories
subdir('interfaces')

# Various parts of Budgie use libbudgie-common API
subdir('common')

# Build primary shell and services
subdir('shell')
subdir('services')

# Build our scaffolding components for the faces to make use of
subdir('scaffolding')

# Now build our actual desktop
subdir('faces')

# Compositor so we can show things to The People
subdir('compositor')

# Now the session to wrap it all up
subdir('session')
