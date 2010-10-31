#!/bin/sh

libtoolize --automake --force --copy
autoheader
aclocal $ACLOCAL_FLAGS
automake --add-missing
autoconf
