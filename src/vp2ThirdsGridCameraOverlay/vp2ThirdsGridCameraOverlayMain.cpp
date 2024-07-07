//-
// Copyright (c) 2024 jet-misoshil-h.
// All rights reserved.
//
// vp2ThirdsGridCameraOverlay
// Repository: https://github.com/jet-misoshil-h/vp2ThirdsGirdRenderOverride
// Author: jet_misoshil (jet-misoshil-h)
//+

#include <stdio.h>

#include <maya/MString.h>
#include <maya/MFnPlugin.h>
#include <maya/MViewport2Renderer.h>
#include "vp2ThirdsGridCameraOverlay.h"

//
// On plug-in initialization we register a new override
//
MStatus initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj, "jet_misoshil", "0.1.2a", "Any");

	MHWRender::MRenderer* renderer = MHWRender::MRenderer::theRenderer();
	if (renderer)
	{
		// We register with a given name
		vp2ThirdsGridCameraOverlay *overridePtr = new vp2ThirdsGridCameraOverlay("vp2ThirdsGridCameraOverlay");
		if (overridePtr)
		{
			renderer->registerOverride(overridePtr);
		}
	}
	return status;
}

//
// On plug-in de-initialization we deregister a new override
//
MStatus uninitializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj);

	MHWRender::MRenderer* renderer = MHWRender::MRenderer::theRenderer();
	if (renderer)
	{
		// Find override with the given name and deregister
		const MHWRender::MRenderOverride* overridePtr = renderer->findRenderOverride("vp2ThirdsGridCameraOverlay");
		if (overridePtr)
		{
			renderer->deregisterOverride( overridePtr );
			delete overridePtr;
		}
	}

	return status;
}
