/*
 *      Copyright (C) 2020 Team MrMC
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

#include "SkuDetails.h"

#include "jutils-details.hpp"

using namespace jni;

// Not in public API, be extra careful

std::string CJNISkuDetails::getSku() const
{
  jmethodID mid = get_method_id(m_object, "getSku", "()Ljava/lang/String;");
  if (mid != NULL)
    return jcast<std::string>(call_method<jhstring>(m_object, mid));
  else
    return "";
}

std::string CJNISkuDetails::getTitle() const
{
  jmethodID mid = get_method_id(m_object, "getTitle", "()Ljava/lang/String;");
  if (mid != NULL)
    return jcast<std::string>(call_method<jhstring>(m_object, mid));
  else
    return "";
}

std::string CJNISkuDetails::getDescription() const
{
  jmethodID mid = get_method_id(m_object, "getDescription", "()Ljava/lang/String;");
  if (mid != NULL)
    return jcast<std::string>(call_method<jhstring>(m_object, mid));
  else
    return "";
}

std::string CJNISkuDetails::getPrice() const
{
  jmethodID mid = get_method_id(m_object, "getPrice", "()Ljava/lang/String;");
  if (mid != NULL)
    return jcast<std::string>(call_method<jhstring>(m_object, mid));
  else
    return "";
}
