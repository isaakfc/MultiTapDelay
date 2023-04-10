#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin/Debug/validator -selftest
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin/Release/validator -selftest
fi

