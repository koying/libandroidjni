#pragma once
/*
 *      Copyright (C) 2014 Team XBMC
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
#include "Context.h"
#include "Intent.h"

class CJNIWindowManager;
class CVariant;
struct ANativeActivity;

class CJNIActivity : public CJNIContext
{
public:
  CJNIActivity(const jobject& clazz);
  ~CJNIActivity();

  CJNIWindowManager getWindowManager();
  bool moveTaskToBack(bool nonRoot);
  void startActivityForResult(const CJNIIntent &intent, int requestCode);
  bool requestVisibleBehind(bool visible);
  void enterPictureInPictureMode();

  virtual void onVisibleBehindCanceled() = 0;
  virtual void onMultiWindowModeChanged(bool isInMultiWindowMode) = 0;
  virtual void onPictureInPictureModeChanged(bool isInPictureInPictureMode) = 0;

private:
  CJNIActivity();
};

