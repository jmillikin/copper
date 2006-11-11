#!/bin/sh

libtoolize --force
autoheader
aclocal $ACLOCAL_FLAGS
automake
autoconf
