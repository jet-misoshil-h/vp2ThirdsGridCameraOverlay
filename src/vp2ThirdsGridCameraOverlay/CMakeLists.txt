#-
# ==========================================================================
# Copyright (c) 2024 jet-misoshil-h.
# All rights reserved.
# ==========================================================================
#+


cmake_minimum_required(VERSION 3.13)

# set env variable DEVKIT_LOCATION to the location of Maya devkit
set(ENV{DEVKIT_LOCATION} C:/work/maya_devkit/devkitBase)

# include the project setting file
include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

# specify project name
set(PROJECT_NAME vp2ThirdsGridCameraOverlay)

# set SOURCE_FILES
set(SOURCE_FILES
   vp2ThirdsGridCameraOverlay.cpp
   vp2ThirdsGridCameraOverlayMain.cpp
   vp2ThirdsGridCameraOverlay.h
)

# set linking libraries
set(LIBRARIES
     OpenMaya
     OpenMayaRender
     Foundation

)

# Build plugin
build_plugin()

