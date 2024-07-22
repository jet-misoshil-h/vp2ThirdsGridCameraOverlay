# vp2ThirdsGridCameraOverlay
Plug-in to display thirds grid in Maya viewport

![plaview](/images/cameraoverlay_02.gif)

## required Maya version
Maya 2023

Currently 2023 ONLY, but another version will be released soon!

# Install
Store vp2ThirdsGridCameraOverlay.mll from the plug-ins folder to a folder that has a path that recognizes Maya's plug-ins.

Example:\
Documents/maya/2023/plug-ins/

# Usage
1, Load “vp2ThirdsGridCameraOverlay.mll” in the Plug-in Manager.

![image01.png](/images/image01.png)

2, Change the renderer to “VP2 Thirds Grid Camera Overlay” for the viewport to which you want to apply the ThirdsGridHUD.

![image02.png](/images/image02.png)

# Feature
## v1.0.0
* Display a ThirdsGrid HUD with the following FitResolution when using FilmGate
* ThirdsGrid HUD display in the Gate display

> [!NOTE]
> It says v1.0.0 but the version is 0.1.2a when I loaded the plugin. Sorry.

## v1.1.0
* Display a 3-division grid HUD with the following FitResolution when using ResolutionGate

## Fit Resolution Gate
* kFillFilmFit
* kHorizontalFilmFit
* kVerticalFilmFit
* kOverscanFilmFit

# Issue
Known Issues

> [!NOTE]
> FilmFitOffset
> I'm not able to deal with the inch offset of the center coordinates of the trisection line due to this parameter.
> I'll deal with it when I figure out how to get the DPI of Maya's viewport to vary according to the user's settings.

> [!NOTE]
> lensSqueezeRatio
> The ratio of the gate mask area by this parameter is not supported.
> As usual, it is out of alignment.

> [!WARNING]
> ResolutionGate
> Fill and OverscanFilmFit settings slightly shift the trisection line