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

#include "Activity.h"
#include "Intent.h"
#include "WindowManager.h"

#include "jutils-details.hpp"

#include <android/native_activity.h>

using namespace jni;

CJNIActivity::CJNIActivity(const jobject& clazz) : CJNIContext(clazz)
{
}

CJNIActivity::~CJNIActivity()
{
}

CJNIWindowManager CJNIActivity::getWindowManager()
{
  return call_method<jhobject>(m_object,
    "getWindowManager", "()Landroid/view/WindowManager;");
}

bool CJNIActivity::moveTaskToBack(bool nonRoot)
{
  return call_method<jboolean>(m_object,
    "moveTaskToBack", "(Z)Z",
    nonRoot);
}

void CJNIActivity::startActivityForResult(const CJNIIntent &intent, int requestCode)
{
  call_method<void>(m_object,
    "startActivityForResult", "(Landroid/content/Intent;I)V",
                    intent.get_raw(), requestCode);
}

bool CJNIActivity::requestVisibleBehind(bool visible)
{
  return call_method<jboolean>(m_object,
    "requestVisibleBehind", "(Z)Z",
                               visible);
}

void CJNIActivity::enterPictureInPictureMode()
{
  if (CJNIBase::GetSDKVersion() < 24)
    return;

  call_method<void>(m_object,
    "enterPictureInPictureMode", "()V");
}

