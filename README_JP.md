# vp2ThirdsGridCameraOverlay
このプラグインはMayaのビューポートに3分割グリッドHUDを表示します

![plaview](/images/cameraoverlay_02.gif)

## required Maya version
Maya 2023

現在は2023オンリーですが、そのうち別のバージョンも公開予定です

# Install
plug-insフォルダ以下よりvp2ThirdsGridCameraOverlay.mllをMayaのpluginを認識するパスが通っているフォルダ以下に格納する

例：\
Documents/maya/2023/plug-ins/

# Usage
1, プラグインマネージャーで"vp2ThirdsGridCameraOverlay.mll"をロードします
![image01.png](/images/image01.png)

2, ThirdsGridHUDを適応したいビューポートのRendererを"VP2 Thirds Grid Camera Overlay"に変更します
![image02.png](/images/image02.png)

# Feature
## v1.0.0
* FilmGate利用時の以下のFitResolutionで3分割グリッドHUDを表示する
* Gate表示の内状態の3分割グリッドHUD表示

> [!NOTE]
> v1.0.0といいつつプアグインを読み込んだときのバージョンが0.1.2aです。すみません

## v1.1.0
* ResolutionGate利用時の以下のFitResolutionで3分割グリッドHUDを表示する

## Fit Resolution Gate
* kFillFilmFit
* kHorizontalFilmFit
* kVerticalFilmFit
* kOverscanFilmFit

# Issue
既知の問題

> [!NOTE]
> FilmFitOffset
> このパラメーターによる3分割線の中央座標のインチオフセットに対応できていません
> MayaのビューポートのDPIがユーザーの設定によって可変する部分の取得対策をどうするか考えたら対応します

> [!NOTE]
> lensSqueezeRatio
> このパラメーターによるゲートマスク領域の比率可変に対応できていません
> 例によってズレます

> [!WARNING]
> ResolutionGate
> Fillおよび、OverscanFilmFit設定では微妙に3分割線がずれます
