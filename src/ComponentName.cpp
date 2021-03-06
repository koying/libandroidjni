/*
 *      Copyright (C) 2016 Christian Browet
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

#include "ComponentName.h"

#include "jutils-details.hpp"

using namespace jni;

const char *CJNIComponentName::m_classname = "android/content/ComponentName";

CJNIComponentName::CJNIComponentName(const std::string& pkg, const std::string& cls)
  : CJNIBase(m_classname)

{
  m_object = new_object(m_classname, "<init>",
                        "(Ljava/lang/String;Ljava/lang/String;)V",
                        jcast<jhstring>(pkg), jcast<jhstring>(cls));
  m_object.setGlobal();
}
