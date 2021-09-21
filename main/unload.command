#!/bin/bash
#unload

dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

#thanks to aixxe.net/2016/09/shared-library-injection
sudo lldb --batch \
  -o "attach --name csgo_osx64" \
  -o "expr void* \$library = (void*)dlopen(\"$dir/libosxGlow.dylib\", 18)" \
  -o "p (int)dlclose(\$library)" \
  -o "p (int)dlclose(\$library)" \
  -o "detach" \
  -o "quit"
