#!/bin/bash
# Ensure we're formatted everywhere.
clang-format -i $(find src -name '*.cpp' -or -name '*.h' -not -path '*/build/*')

# Check we have no typos.
which misspell 2>/dev/null >/dev/null
if [[ $? -eq 0 ]]; then
    misspell -error `find src -name '*.cpp' -or -name '*.h' -not -path '*/build/*'`
fi
