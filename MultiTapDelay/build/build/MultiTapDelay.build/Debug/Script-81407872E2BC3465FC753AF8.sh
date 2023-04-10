#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin
  /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin/Debug/moduleinfotool -create -version 1.0.0.0 -path /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/VST3/Debug/MultiTapDelay.vst3 -output /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/VST3/Debug/MultiTapDelay.vst3/Contents/moduleinfo.json
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin
  codesign -f -s - -v /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/VST3/Debug/MultiTapDelay.vst3/Contents/moduleinfo.json
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin
  /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin/Debug/validator /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/VST3/Debug/MultiTapDelay.vst3 
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build
  /Applications/CMake.app/Contents/bin/cmake -E make_directory /Users/isaac/Library/Audio/Plug-Ins/VST3
  ln -svfF /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/VST3/Debug/MultiTapDelay.vst3 /Users/isaac/Library/Audio/Plug-Ins/VST3
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin
  /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin/Release/moduleinfotool -create -version 1.0.0.0 -path /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/VST3/Release/MultiTapDelay.vst3 -output /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/VST3/Release/MultiTapDelay.vst3/Contents/moduleinfo.json
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin
  codesign -f -s - -v /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/VST3/Release/MultiTapDelay.vst3/Contents/moduleinfo.json
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin
  /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/bin/Release/validator  /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/VST3/Release/MultiTapDelay.vst3
  cd /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build
  /Applications/CMake.app/Contents/bin/cmake -E make_directory /Users/isaac/Library/Audio/Plug-Ins/VST3
  ln -svfF /Users/isaac/Documents/UWLDAE/SEMESTER2/AP2/ASSESMENT1/C++PROJECT/MultiTapDelay/build/VST3/Release/MultiTapDelay.vst3 /Users/isaac/Library/Audio/Plug-Ins/VST3
fi

