#!/bin/sh

libtoolize
autoheader
aclocal $ACLOCAL_FLAGS
automake
autoconf
