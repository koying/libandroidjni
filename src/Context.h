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
#include "ApplicationInfo.h"
#include "ClassLoader.h"
#include "BroadcastReceiver.h"

struct ANativeActivity;
class CJNIBroadcastReceiver;
class CJNIContentResolver;
class CJNIIntent;
class CJNIIntentFilter;
class CJNIFile;
class CJNIPackageManager;
class CJNIWindow;

class CJNIContext : virtual public CJNIBase
{
public:
  static std::string CONNECTIVITY_SERVICE;
  static std::string NSD_SERVICE;

  CJNIPackageManager GetPackageManager();
  void startActivity(const CJNIIntent &intent);
  jni::jhobject getSystemService(const std::string &service);
  int checkCallingOrSelfPermission(const std::string &permission);
  CJNIIntent registerReceiver(const CJNIBroadcastReceiver &receiver, const CJNIIntentFilter &filter);
  CJNIIntent registerReceiver(const CJNIIntentFilter &filter);
  void unregisterReceiver(const CJNIBroadcastReceiver &receiver);
  void sendBroadcast(const CJNIIntent &intent);
  CJNIIntent getIntent();
  CJNIClassLoader getClassLoader();
  jni::CJNIApplicationInfo getApplicationInfo();
  std::string getPackageName();
  std::string getPackageResourcePath();
  CJNIFile getCacheDir();
  CJNIFile getDir(const std::string &path, int mode);
  CJNIFile getExternalFilesDir(const std::string &path);
  CJNIContentResolver getContentResolver();
  CJNIWindow getWindow();

protected:
  CJNIContext(const jobject& clazz);
  ~CJNIContext();

protected:
  CJNIContext() : CJNIBase() {}
  CJNIContext(const jni::jhobject &object) : CJNIBase(object) {}

  void PopulateStaticFields();
  void operator=(CJNIContext const&){};
};
