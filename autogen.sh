#!/bin/sh
autoreconf --force --install --symlink -I m4

echo
echo "--------------------------------------------------------------------------"
echo "Initialized build system. For a common configuration please run:"
echo "./configure CFLAGS='-g -ggdb -O0 -Wall -Wextra -Werror'"
echo "--------------------------------------------------------------------------"
echo
