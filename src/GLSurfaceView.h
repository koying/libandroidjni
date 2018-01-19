#pragma once
/*
 *      Copyright (C) 2018 Christian Browet
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "JNIBase.h"
#include "SurfaceView.h"

class CJNIGL10;
class CJNIEGLConfig;

class CJNIGLSurfaceViewRenderer : virtual public CJNIBase
{
public:
  virtual void onDrawFrame(CJNIGL10 gl) = 0;
  virtual void onSurfaceCreated(CJNIGL10 gl, CJNIEGLConfig config) = 0;
  virtual void onSurfaceChanged(CJNIGL10 gl, int width, int height) = 0;
};

class CJNIGLSurfaceView : public CJNISurfaceView
{
public:
  CJNIGLSurfaceView(const jni::jhobject &object) : CJNISurfaceView(object) {}
  ~CJNIGLSurfaceView() {}
};
