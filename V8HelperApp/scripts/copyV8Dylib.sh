#!/bin/sh
CONFIGURATION=$1
BASE_DIR=`dirname $0`"/../.."
cp "$BASE_DIR"/lib/mac/libv8.dylib "$BASE_DIR"/V8Helper/bin/MacOSX/$CONFIGURATION