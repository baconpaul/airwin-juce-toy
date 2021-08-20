cmake_minimum_required(VERSION 3.10)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11 CACHE STRING "Build for 10.11")

project(airwindow-juce-toy VERSION 0.9.0 LANGUAGES CXX)

add_subdirectory(libs/JUCE)

set( BUILD_VST2 FALSE )
if( BUILD_VST2 )
    set( EXTRA_FORMATS VST )
    juce_set_vst2_sdk_path( "../VST2_SDK")
else()
    set( EXTRA_FORMATS "" )
endif()

message( STATUS "Extra Formats : ${EXTRA_FORMATS}" )

juce_add_plugin(airwindow-juce-toy
    PRODUCT_NAME "AirwindowJuceToyExample"
    COMPANY_NAME "BaconPaul"  
    BUNDLE_ID "org.baconpaul.airwindow-juce-toy"
    PLUGIN_MANUFACTURER_CODE BcnP
    PLUGIN_CODE AWjE

    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    
    FORMATS AU VST3 Standalone ${EXTRA_FORMATS}
)

juce_generate_juce_header( airwindow-juce-toy )

target_include_directories(airwindow-juce-toy 
  PUBLIC
  src
)

target_sources(airwindow-juce-toy PRIVATE
  src/PluginEditor.cpp
  src/PluginProcessor.cpp
)

target_compile_definitions(airwindow-juce-toy PUBLIC
    JUCE_ALLOW_STATIC_NULL_VARIABLES=0
    JUCE_STRICT_REFCOUNTEDPOINTER=1

    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0

    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_REPORT_APP_USAGE=0

    JUCE_ALSA=1
    JUCE_JACK=1

    DONT_SET_USING_JUCE_NAMESPACE=1
)

target_link_libraries(airwindow-juce-toy PRIVATE
    juce::juce_audio_processors
    juce::juce_audio_devices
    juce::juce_audio_utils
    juce::juce_gui_basics
)
