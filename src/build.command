#!/bin/bash
#build

cd "$( dirname "${BASH_SOURCE[0]}" )"
if [ "$(uname -m)" == "arm64" ]; then 
    arch -x86_64 gcc -framework Foundation -framework AppKit -std=c++17 -lstdc++ -dynamiclib -Os osxGlow.mm -o libosxGlow.dylib
else
    gcc -framework Foundation -framework AppKit -std=c++17 -lstdc++ -dynamiclib -Os osxGlow.mm -o libosxGlow.dylib
fi
