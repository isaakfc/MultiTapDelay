cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "/Users/isaac/Desktop/VST_SDK/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(MultiTapDelay
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "MultiTapDelay VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(MultiTapDelay
    source/version.h
    source/cids.h
    source/processor.h
    source/processor.cpp
    source/controller.h
    source/controller.cpp
    source/entry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ADD_VSTGUI)
    target_sources(MultiTapDelay
        PRIVATE
            resource/editor.uidesc
    )
    target_link_libraries(MultiTapDelay
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(MultiTapDelay
        RESOURCES
            "resource/editor.uidesc"
    )
endif(SMTG_ADD_VSTGUI)
# -------------------

smtg_target_add_plugin_snapshots (MultiTapDelay
    RESOURCES
        resource/77975A13F5B35D5691DE70488BF562E2_snapshot.png
        resource/77975A13F5B35D5691DE70488BF562E2_snapshot_2.0x.png
)

target_link_libraries(MultiTapDelay
    PRIVATE
        sdk
)

smtg_target_configure_version_file(MultiTapDelay)

if(SMTG_MAC)
    smtg_target_set_bundle(MultiTapDelay
        BUNDLE_IDENTIFIER com.semblance.MultiTapDelay
        COMPANY_NAME "Semblance"
    )
    smtg_target_set_debug_executable(MultiTapDelay
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(MultiTapDelay PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MultiTapDelay)

        smtg_target_set_debug_executable(MultiTapDelay
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
