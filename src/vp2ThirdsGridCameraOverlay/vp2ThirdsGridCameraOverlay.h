#ifndef vp2ThirdsGridCameraOverlay_h_
#define vp2ThirdsGridCameraOverlay_h_
//-
// Copyright (c) 2024 jet-misoshil-h.
// All rights reserved.
//
// vp2ThirdsGridCameraOverlay
// Repository: https://github.com/jet-misoshil-h/vp2ThirdsGridCameraOverlay
// Author: jet_misoshil (jet-misoshil-h)
//+
#include <maya/MString.h>
#include <maya/MViewport2Renderer.h>


class vp2ThirdsGridCameraOverlay : public MHWRender::MRenderOverride
{
public:
	vp2ThirdsGridCameraOverlay( const MString & name );
	~vp2ThirdsGridCameraOverlay() override;
	MHWRender::DrawAPI supportedDrawAPIs() const override;

	// Basic setup and cleanup
	MStatus setup( const MString & destination ) override;
	MStatus cleanup() override;

	// Operation iteration methods
	bool startOperationIterator() override;
	MHWRender::MRenderOperation * renderOperation() override;
	bool nextRenderOperation() override;

	// UI name
	MString uiName() const override
	{
		return mUIName;
	}

protected:
	// UI name 
	MString mUIName;

	// Operations and operation names
	MHWRender::MRenderOperation* mOperations[3];
	MString mOperationNames[3];

	// Temporary of operation iteration
	int mCurrentOperation;
};

class simpleViewRenderSceneRender : public MHWRender::MSceneRender
{
public:
    simpleViewRenderSceneRender(const MString &name);
    MHWRender::MClearOperation & clearOperation() override;
};

class viewRenderHUDOperation : public MHWRender::MHUDRender
{
public:
	viewRenderHUDOperation()
	{
		mTargets = NULL;
	}

	// Target override
	MHWRender::MRenderTarget* const* targetOverrideList(unsigned int &listSize) override
	{
		if (mTargets)
		{
			listSize = 2;
			return &mTargets[0];
		}
		listSize = 0;
		return NULL;
	}

	bool hasUIDrawables() const override
	{
		return true;
	}

	void addUIDrawables( MHWRender::MUIDrawManager& drawManager2D, const MHWRender::MFrameContext& frameContext ) override;

	void setRenderTargets(MHWRender::MRenderTarget **targets)
	{
		mTargets = targets;
	}

	void updateThirdsLine(
		int ow, int oh, int ew, int wh,
		const MPoint& thirds, const MPoint& thirdsLength, MHWRender::MUIDrawManager& drawManager2D );

	~viewRenderHUDOperation() override
	{
		mTargets = NULL;
	}

protected:
	MHWRender::MRenderTarget** mTargets;
};

#endif
