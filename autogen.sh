#!/bin/sh

libtoolize --automake --force --copy
aclocal $ACLOCAL_FLAGS
automake --add-missing
autoconf
