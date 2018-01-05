#pragma once
/*
 *      Copyright (C) 2013 Team XBMC
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

#include "jutils-details.hpp"

template <typename T>
class CJNIArrayList : public CJNIBase
{
public:
  CJNIArrayList()
    : CJNIBase("java/util/ArrayList")
  {
    m_object = jni::new_object(GetClassName(), "<init>", "()V");
    m_object.setGlobal();
  }

  CJNIArrayList(const jni::jhobject &object) : CJNIBase(object) {}
  ~CJNIArrayList() {}

  T get(int index)
  {
    return (T) jni::call_method<jni::jhobject>(m_object,
      "get", "(I)Ljava/lang/Object;",
      index);
  }

  int size()
  {
    return m_object.get() ? jni::call_method<jint>(m_object,
                                              "size", "()I") : 0;
  }

  bool add(const T& el)
  {
    return jni::call_method<jboolean>(m_object,
      "add", "(Ljava/lang/Object;)Z", el.get_raw());
  }

};

template <> std::string CJNIArrayList<std::string>::get(int index);
template <> bool CJNIArrayList<std::string>::add(const std::string& el);
