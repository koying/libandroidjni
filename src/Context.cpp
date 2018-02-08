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

#include "Context.h"

#include "jutils-details.hpp"

#include <android/log.h>
#include <android/native_activity.h>

#include "ApplicationInfo.h"
#include "AudioFormat.h"
#include "AudioAttributes.h"
#include "AudioDeviceInfo.h"
#include "AudioManager.h"
#include "AudioTrack.h"
#include "BaseColumns.h"
#include "BroadcastReceiver.h"
#include "Build.h"
#include "ClassLoader.h"
#include "ConnectivityManager.h"
#include "ContentResolver.h"
#include "Cursor.h"
#include "DisplayMetrics.h"
#include "Document.h"
#include "Environment.h"
#include "File.h"
#include "MediaCodec.h"
#include "MediaCodecInfo.h"
#include "MediaFormat.h"
#include "MediaMetadata.h"
#include "MediaStore.h"
#include "MediaSync.h"
#include "IBinder.h"
#include "Intent.h"
#include "IntentFilter.h"
#include "KeyEvent.h"
#include "PackageManager.h"
#include "PlaybackState.h"
#include "PowerManager.h"
#include "RecognizerIntent.h"
#include "Settings.h"
#include "Surface.h"
#include "URI.h"
#include "View.h"
#include "Window.h"

using namespace jni;

std::string CJNIContext::CONNECTIVITY_SERVICE;
std::string CJNIContext::NSD_SERVICE;

CJNIContext::CJNIContext(const jobject& clazz)
  : CJNIBase()
{
  m_object.reset(clazz);
  PopulateStaticFields();
}

CJNIContext::~CJNIContext()
{
}

void CJNIContext::PopulateStaticFields()
{
  jhclass clazz = find_class("android/content/Context");
  CONNECTIVITY_SERVICE = jcast<std::string>(get_static_field<jhstring>(clazz,"CONNECTIVITY_SERVICE"));
  NSD_SERVICE = jcast<std::string>(get_static_field<jhstring>(clazz,"NSD_SERVICE"));

  CJNIBuild::PopulateStaticFields();  // First for SetSDKVersion

  CJNIBaseColumns::PopulateStaticFields();
  CJNIMediaStoreMediaColumns::PopulateStaticFields();
  CJNIMediaStore::PopulateStaticFields();
  CJNIPowerManager::PopulateStaticFields();
  CJNIPackageManager::PopulateStaticFields();
  CJNICursor::PopulateStaticFields();
  CJNIContentResolver::PopulateStaticFields();
  CJNIConnectivityManager::PopulateStaticFields();
  CJNIAudioFormat::PopulateStaticFields();
  CJNIAudioAttributes::PopulateStaticFields();
  CJNIAudioManager::PopulateStaticFields();
  CJNIAudioTrack::PopulateStaticFields();
  CJNISurface::PopulateStaticFields();
  CJNIMediaCodec::PopulateStaticFields();
  CJNIMediaCodecInfoCodecProfileLevel::PopulateStaticFields();
  CJNIMediaCodecInfoCodecCapabilities::PopulateStaticFields();
  CJNIMediaFormat::PopulateStaticFields();
  CJNIView::PopulateStaticFields();
  CJNIDisplayMetrics::PopulateStaticFields();
  CJNIIntent::PopulateStaticFields();
  CJNIKeyEvent::PopulateStaticFields();
  CJNISettings::PopulateStaticFields();
  CJNIEnvironment::PopulateStaticFields();
  CJNIDocument::PopulateStaticFields();
  CJNIRecognizerIntent::PopulateStaticFields();
  CJNIAudioDeviceInfo::PopulateStaticFields();
  CJNIViewInputDevice::PopulateStaticFields();
  CJNIMediaSync::PopulateStaticFields();
  CJNIIBinder::PopulateStaticFields();
  CJNIMediaMetadata::PopulateStaticFields();
  CJNIPlaybackState::PopulateStaticFields();
  CJNIURI::PopulateStaticFields();
}

CJNIPackageManager CJNIContext::GetPackageManager()
{
  return call_method<jhobject>(m_object,
    "getPackageManager", "()Landroid/content/pm/PackageManager;");
}

void CJNIContext::startActivity(const CJNIIntent &intent)
{
  call_method<void>(m_object,
    "startActivity", "(Landroid/content/Intent;)V",
    intent.get_raw());
}

int CJNIContext::checkCallingOrSelfPermission(const std::string &permission)
{
  return call_method<int>(m_object,
    "checkCallingOrSelfPermission", "(Ljava/lang/String;)I",
    jcast<jhstring>(permission));
}

jhobject CJNIContext::getSystemService(const std::string &service)
{
  return call_method<jhobject>(m_object,
    "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;",
    jcast<jhstring>(service));
}

CJNIIntent CJNIContext::registerReceiver(const CJNIBroadcastReceiver &receiver, const CJNIIntentFilter &filter)
{
  return call_method<jhobject>(m_object,
    "registerReceiver", "(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)Landroid/content/Intent;",
    receiver.get_raw(), filter.get_raw());
}

CJNIIntent CJNIContext::registerReceiver(const CJNIIntentFilter &filter)
{
  return call_method<jhobject>(m_object,
    "registerReceiver", "(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)Landroid/content/Intent;",
    (jobject)NULL, filter.get_raw());
}

void CJNIContext::unregisterReceiver(const CJNIBroadcastReceiver &receiver)
{
  call_method<void>(m_object,
    "unregisterReceiver", "(Landroid/content/BroadcastReceiver;)V",
    receiver.get_raw());
}

void CJNIContext::sendBroadcast(const CJNIIntent &intent)
{
  call_method<void>(m_object,
    "sendBroadcast", "(Landroid/content/Intent;)V",
    intent.get_raw());
}

CJNIIntent CJNIContext::getIntent()
{
  return call_method<jhobject>(m_object,
    "getIntent", "()Landroid/content/Intent;");
}

CJNIClassLoader CJNIContext::getClassLoader()
{
  return call_method<jhobject>(m_object,
    "getClassLoader", "()Ljava/lang/ClassLoader;");
}

jni::CJNIApplicationInfo CJNIContext::getApplicationInfo()
{
  return call_method<jhobject>(m_object,
    "getApplicationInfo", "()Landroid/content/pm/ApplicationInfo;");
}

std::string CJNIContext::getPackageName()
{
  return jcast<std::string>(call_method<jhstring>(m_object,
    "getPackageName", "()Ljava/lang/String;"));
}

std::string CJNIContext::getPackageResourcePath()
{
  return jcast<std::string>(call_method<jhstring>(m_object,
    "getPackageResourcePath", "()Ljava/lang/String;"));
}

CJNIFile CJNIContext::getCacheDir()
{
  return call_method<jhobject>(m_object,
    "getCacheDir", "()Ljava/io/File;");
}

CJNIFile CJNIContext::getDir(const std::string &path, int mode)
{
  return call_method<jhobject>(m_object,
    "getDir", "(Ljava/lang/String;I)Ljava/io/File;",
    jcast<jhstring>(path), mode);
}

CJNIFile CJNIContext::getExternalFilesDir(const std::string &path)
{
  return call_method<jhobject>(m_object,
    "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;",
    jcast<jhstring>(path));
}

CJNIContentResolver CJNIContext::getContentResolver()
{
  return call_method<jhobject>(m_object,
    "getContentResolver", "()Landroid/content/ContentResolver;");
}

CJNIWindow CJNIContext::getWindow()
{
  return call_method<jhobject>(m_object,
    "getWindow", "()Landroid/view/Window;");
}
