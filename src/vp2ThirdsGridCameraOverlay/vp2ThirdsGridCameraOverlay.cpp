//-
// Copyright (c) 2024 jet-misoshil-h.
// All rights reserved.
//
// vp2ThirdsGridCameraOverlay
// Repository: https://github.com/jet-misoshil-h/vp2ThirdsGirdRenderOverride
// Author: jet_misoshil (jet-misoshil-h)
//+

#include "vp2ThirdsGridCameraOverlay.h"
#include <maya/MFnCamera.h>
#include <maya/MCommonRenderSettingsData.h>
#include <maya/MRenderUtil.h>

// For override creation we return a UI name so that it shows up in as a
// renderer in the 3d viewport menus.
// 
vp2ThirdsGridCameraOverlay::vp2ThirdsGridCameraOverlay( const MString & name )
: MRenderOverride( name )
, mUIName("VP2 Thirds Grid Camera Overlay")
, mCurrentOperation(-1)
{
	mOperations[0] = mOperations[1] = mOperations[2] = NULL;
	mOperationNames[0] = "vp2ThirdsGridCameraOverlay_Scene";
	mOperationNames[1] = "vp2ThirdsGridCameraOverlay_HUD";
	mOperationNames[2] = "vp2ThirdsGridCameraOverlay_Present";

}

// On destruction all operations are deleted.
//
vp2ThirdsGridCameraOverlay::~vp2ThirdsGridCameraOverlay()
{
	for (unsigned int i=0; i<3; i++)
	{
		if (mOperations[i])
		{
			delete mOperations[i];
			mOperations[i] = NULL;
		}
	}
}
	
// Drawing uses all internal code so will support all draw APIs
//
MHWRender::DrawAPI vp2ThirdsGridCameraOverlay::supportedDrawAPIs() const
{
	return MHWRender::kAllDevices;
}

// Basic iterator methods which returns a list of operations in order
// The operations are not executed at this time only queued for execution
//
// - startOperationIterator() : to start iterating
// - renderOperation() : will be called to return the current operation
// - nextRenderOperation() : when this returns false we've returned all operations
//
bool vp2ThirdsGridCameraOverlay::startOperationIterator()
{
	mCurrentOperation = 0;
	return true;
}

MHWRender::MRenderOperation*
vp2ThirdsGridCameraOverlay::renderOperation()
{
	if (mCurrentOperation >= 0 && mCurrentOperation < 3)
	{
		if (mOperations[mCurrentOperation])
		{
			return mOperations[mCurrentOperation];
		}
	}
	return NULL;
}

bool 
vp2ThirdsGridCameraOverlay::nextRenderOperation()
{
	mCurrentOperation++;
	if (mCurrentOperation < 3)
	{
		return true;
	}
	return false;
}

//
// On setup we make sure that we have created the appropriate operations
// These will be returned via the iteration code above.
//
// The only thing that is required here is to create:
//
//	- One scene render operation to draw the scene.
//	- One "stock" HUD render operation to draw the HUD over the scene
//	- One "stock" presentation operation to be able to see the results in the viewport
//
MStatus vp2ThirdsGridCameraOverlay::setup( const MString & destination )
{
	MHWRender::MRenderer *theRenderer = MHWRender::MRenderer::theRenderer();
	if (!theRenderer)
		return MStatus::kFailure;

	// Create a new set of operations as required
	if (!mOperations[0])
	{
		mOperations[0] = (MHWRender::MRenderOperation *) new simpleViewRenderSceneRender( mOperationNames[0] );
		mOperations[1] = (MHWRender::MRenderOperation *) new viewRenderHUDOperation();
		mOperations[2] = (MHWRender::MRenderOperation *) new MHWRender::MPresentTarget( mOperationNames[2] );
	}
	if (!mOperations[0] || 
		!mOperations[1] ||
		!mOperations[2])
	{
		return MStatus::kFailure;
	}

	return MStatus::kSuccess;
}

// On cleanup we just return for returning the list of operations for
// the next render
//
MStatus vp2ThirdsGridCameraOverlay::cleanup()
{
	mCurrentOperation = -1;
	return MStatus::kSuccess;
}
	
// The only customization for the scene render (and hence derivation)
// is to be able to set the background color.
//
simpleViewRenderSceneRender::simpleViewRenderSceneRender(const MString &name)
: MSceneRender( name )
{
}

//------------------------------------------------------------------------
// Custom HUD operation
//
void viewRenderHUDOperation::addUIDrawables( MHWRender::MUIDrawManager& drawManager2D, const MHWRender::MFrameContext& frameContext )
{
	// Start draw UI
	drawManager2D.beginDrawable();
	// // Set font color
	drawManager2D.setColor( MColor( 0.455f, 0.212f, 0.596f ) );
	// // Set font size
	// drawManager2D.setFontSize( MHWRender::MUIDrawManager::kSmallFontSize );

	// Draw renderer name
	int x=0, y=0, w=0, h=0;
	frameContext.getViewportDimensions( x, y, w, h );
	drawManager2D.text( MPoint(w*0.5f, h*0.91f), MString("Camera Overlay Enabled"), MHWRender::MUIDrawManager::kCenter );

	// Draw lines
	drawManager2D.setColor( MColor( 0.05f, 0.32f, 0.05f ) );

	// TODO: Get camera aspect ratio
	// Get image ratio
	// MCommonRenderSettingsData data;
	// MRenderUtil::getCommonRenderSettings(data);

	// Get current camera
	MFnCamera camera( frameContext.getCurrentCameraPath() );
	MPoint thirdsLength, thirds;
	MPoint origin, end, center, rOrigin, rEnd;

	// Get view rectangle
	origin = MPoint(x, y);
	end = MPoint(w, h);
	center = MPoint((w/2), (h/2));

	// Get relative origin and end
	rOrigin = origin - center;
	rEnd = end - center;
	
	// Get overscan value
	const double oversacan = camera.overscan();

	// Apply overscan
	rOrigin = oversacan > 0 ? rOrigin / oversacan : rOrigin;
	rEnd = oversacan > 0 ? rEnd / oversacan : rEnd;

	// return to center rectangle
	origin = center + rOrigin;
	end = center + rEnd;

	MPoint endV = (end - origin);

	// if filmgate is true
	if (camera.isDisplayFilmGate())
	{
		const double aspect = camera.aspectRatio();
		const double viewAspect = endV.x / endV.y;

		// double hfa = camera.horizontalFilmAperture();
		// double vfa = camera.verticalFilmAperture();
		// drawManager2D.text( MPoint(w*0.5f, h*0.81f), MString(std::to_string(viewAspect).c_str()), MHWRender::MUIDrawManager::kCenter );

		const MFnCamera::FilmFit filmFit = camera.filmFit();
		switch (filmFit)
		{
			case MFnCamera::kFillFilmFit:
				// Fill
				if (viewAspect > aspect)
				{
					// Horizontal
					endV = MPoint( endV.x, endV.x / aspect);
				}
				else
				{
					// Vertical
					endV = MPoint( endV.y * aspect, endV.y);
				}
				break;
			case MFnCamera::kHorizontalFilmFit:
				// Horizontal
				endV = MPoint( endV.x, endV.x / aspect);
				break;
			case MFnCamera::kVerticalFilmFit:
				// Vertical
				endV = MPoint( endV.y * aspect, endV.y);
				break;
			case MFnCamera::kOverscanFilmFit:
				// Overscan
				if (viewAspect > aspect)
				{
					// Horizontal
					endV = MPoint( endV.x, endV.x / aspect);
				}
				else
				{
					// Vertical
					endV = MPoint( endV.y * aspect, endV.y);
				}
				break;
			default:
				drawManager2D.text( MPoint(w*0.5f, h*0.81f), MString("InValid Camera FilmFit"), MHWRender::MUIDrawManager::kCenter );
				break;
		}

		const MPoint harfEnd = center + (endV / 2);
		const MPoint harfOrig = center - (endV / 2);
		thirdsLength = endV / 3;
		thirds = harfOrig + thirdsLength;

		this->updateThirdsLine(
			harfOrig.x, harfOrig.y, harfEnd.x, harfEnd.y, thirds, thirdsLength, drawManager2D);
	}
	else
	{
		x = (int)origin.x;
		y = (int)origin.y;
		w = (int)end.x;
		h = (int)end.y;
		// if filmgate is false
		thirdsLength = endV / 3;
		thirds = origin + thirdsLength;

		this->updateThirdsLine(
			x, y, w, h, thirds, thirdsLength, drawManager2D);
	}

	// End draw UI
	drawManager2D.endDrawable();
}

void viewRenderHUDOperation::updateThirdsLine(
	int ow, int oh, int ew, int eh, 
	const MPoint& thirds, const MPoint& thirdsLength, ::MUIDrawManager& drawManager2D )
{
	// Vertical line
	drawManager2D.line2d( MPoint( thirds.x, oh), MPoint( thirds.x, eh) );
	drawManager2D.line2d( MPoint( thirds.x+thirdsLength.x, oh), MPoint( thirds.x+thirdsLength.x, eh) );

	// Horizontal line
	drawManager2D.line2d( MPoint( ow, thirds.y), MPoint( ew, thirds.y) );
	drawManager2D.line2d( MPoint( ow, thirds.y+thirdsLength.y), MPoint( ew, thirds.y+thirdsLength.y) );
}

// Background color override. We get the current colors from the 
// renderer and use them
//
MHWRender::MClearOperation &
simpleViewRenderSceneRender::clearOperation()
{
	MHWRender::MRenderer* renderer = MHWRender::MRenderer::theRenderer();
	bool gradient = renderer->useGradient();
	MColor color1 = renderer->clearColor();
	MColor color2 = renderer->clearColor2();

	float c1[4] = { color1[0], color1[1], color1[2], 1.0f };
	float c2[4] = { color2[0], color2[1], color2[2], 1.0f };

	mClearOperation.setClearColor( c1 );
	mClearOperation.setClearColor2( c2 );
	mClearOperation.setClearGradient( gradient);
    return mClearOperation;
}
