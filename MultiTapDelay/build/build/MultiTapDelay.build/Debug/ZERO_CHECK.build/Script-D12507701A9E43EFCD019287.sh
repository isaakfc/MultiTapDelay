#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build
  make -f /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build
  make -f /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/CMakeScripts/ReRunCMake.make
fi

