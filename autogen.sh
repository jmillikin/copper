#!/bin/sh

libtoolize --force --copy
autoheader
aclocal $ACLOCAL_FLAGS
automake --add-missing
autoconf
