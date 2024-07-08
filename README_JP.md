# vp2ThirdsGirdCameraOverride
このプラグインはMayaのビューポートに3分割グリッドHUDを表示します

## required Maya version
Maya 2023

現在は2023オンリーですが、そのうち別のバージョンも公開予定です

# Install
plug-insフォルダ以下よりvp2ThirdsGridCameraOverlay.mllをMayaのpluginを認識するパスが通っているフォルダ以下に格納する

例：\
Documents/maya/2023/plug-ins/

# Usage
プラグインマネージャーで"vp2ThirdsGridCameraOverlay.mll"をロードし、ThirdsGridHUDを適応したいビューポートのRendererを"VP2 Thirds Grid Camera Overlay"に変更します

# Feature
* FIlmGate利用時の以下のFitResolutionで3分割グリッドHUDを表示する
* Gate表示の内状態の3分割グリッドHUD表示

## Fit Resolution Gate
* kFillFilmFit
* kHorizontalFilmFit
* kVerticalFilmFit
* kOverscanFilmFit