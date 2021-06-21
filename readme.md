
# Nori for c/c++

#### - for 
```bash
- Apple
- Win32/64
- Linux

- Android
- iOS

- ...
```

```c++
vi foo.h

/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once
```

<br>

```c++
vi foo.cpp

/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"
```


- ### Rubber Duck
<img src="Resources/a0e32dc5c27bc87a40e04578d4db2a70.jpg" width="450px" height="300px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>

<br>

<img src="Resources/a0e32dc5c27bc87a40e04578d4db2a70.jpg" width="40%" height="30%" title="%(비율) 크기 설정" alt="RubberDuck"></img>


<br>

- #### PLATFORM=???

<br>

```c++
#if defined (__APPLE__)
    #if defined (__IPHONE_OS_VERSION_MAX_ALLOWED)
        #if defined (TARGET_OS_IPHONE)
        #endif //TARGET_OS_IPHONE

        #if defined (TARGET_IPHONE_SIMULATOR)
        #endif //TARGET_IPHONE_SIMULATOR
    #endif // __IPHONE_OS_VERSION_MAX_ALLOWED

    #if defined (__MAC_OS_X_VERSION_MAX_ALLOWED)
    #endif // __IPHONE_OS_VERSION_MAX_ALLOWED
#endif // __APPLE__

#if defined (_WIN32)
#endif // _WIN32

#if defined (_LINUX)
#endif // _LINUX

#if defined (ANDROID)
#endif // ANDROID

```

<br>

- #### CC=???
 
```c++
#define __CC__ = STR

#define __CC_VER__ = ???

#define __CC_MAJOR__ = ???
#define __CC_MINOR__ = ???
#define __CC_PATCHLEVEL__ = ???
```

<br>


# SUB MODULES
- ### ./deps
- ##### [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules)
```bash
$ git submodule --help
    add [-b <branch>] [-f|--force] [--name <name>] [--reference <repository>] [--depth <depth>] [--] <repository> [<path>]
    ...

$ git submodule add [--name <name>] <repository> [<path>]
```

<br>

```bash
$ git submodule add --name glfw https://github.com/glfw/glfw deps/glfw
$ cat .gitmodules
[submodule "glfw"]
	path = deps/glfw
	url = https://github.com/glfw/glfw

...

```

<br>

#### [GLFW]()
- ###### -DUSE_GLFW (default)
   
```bash
$ git submodule add --name glfw https://github.com/glfw/glfw deps/glfw
$ mkdir build; cd build; cmake ../; make
```

<br>

#### [freetype]()
- ##### ftf, png, tga, ...
- ###### -DUSE_FT2 (default)

```bash
$ git submodule add --name freetype https://github.com/freetype/freetype deps/freetype
$ mkdir build; cd build; cmake ../; make
```

- ##### [libpng](http://www.libpng.org/pub/png/libpng.html)
- ###### https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/

```bash
$ curl -O https://nchc.dl.sourceforge.net/project/libpng/libpng16/1.6.37/libpng-1.6.37.tar.xz
$ mkdir build; cd build; cmake ../; make
```

- ##### [zlib](https://zlib.net)
- ###### https://sourceforge.net/projects/libpng/files/zlib/1.2.11/

```bash
$ curl -O https://nchc.dl.sourceforge.net/project/libpng/zlib/1.2.11/zlib-1.2.11.tar.xz
$ mkdir build; cd build; cmake ../; make
```

- ##### [bzip2](https://www.sourceware.org/bzip2/)
- ###### https://www.sourceware.org/bzip2/downloads.html

```bash
$ git submodule add --name bzip2 git://sourceware.org/git/bzip2.git deps/bzip2
# or 
$ curl -O https://www.sourceware.org/pub/bzip2/bzip2-latest.tar.gz

# mkdir build; cd build; cmake ../
# make
# make install
```

<br>

### or

#### [stb]()
- ##### ftf, png, tga, ...
- ###### -DUSE_STB
```bash
$ git submodule add --name stb https://github.com/nothings/stb deps/stb

```

<br>

#### XML
- ##### [tinyxml2](http://www.grinninglizard.com/tinyxml2/)
```bash
$ git submodule add --name tinyxml2 https://github.com/leethomason/tinyxml2 deps/tinyxml2
```

<br>

#### JSON
- ##### [jsoncpp]()
```bash
$ git submodule add --name jsoncpp https://github.com/open-source-parsers/jsoncpp deps/jsoncpp
$ mkdir build; cd build; cmake ../; make
```

<br>

#### SCRIPT
- ##### [Lua]()
```bash
$ git submodule add --name lua https://github.com/lua/lua deps/lua
$ make a
```

- ##### [Python]()
```bash
https://www.python.org/downloads/release/python-395/
```

https://github.com/pybind/pybind11

<br>

##### [GLEW]()
- ###### -DUSE_GLEW
```bash
$ git submodule add --name glew https://github.com/nigels-com/glew deps/glew

$ make extensions
$ make
```

<br>

#### [Autodesk FBX SDK](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-2)
- ###### -DUSE_FBXSDK

```bash
# Windows
$ curl -O https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-2/fbx20202_fbxsdk_vs2019_win.exe

# Mac
$ curl -O https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-2/fbx20202_fbxsdk_clang_mac.pkg.tgz


```

<br>

```bash
$ git submodule init
$ git submodule update

$ git submodule update --init --recursive

$ git clone --recurse-submodules https://github.com/chaconinc/MainProject

$ git submodule add https://github.com/open-source-parsers/jsoncpp deps/jsoncpp

git status

```

# ????
*single asterisks*
_single underscores_
**double asterisks**
__double underscores__
~~cancelline~~


<br>

# ???? 
<style>
r { color: Red }
o { color: Orange }
g { color: Green }
</style>

# TODOs:

- ###### <g>DONE:</g> Firebase
- ###### <g>DONE:</g> Firebase.Analytics
- ###### <g>DONE:</g> Firebase.Auth
- ###### <g>DONE:</g> Firebase.Crashlytics
- ###### <g>DONE:</g> Firebase.Messaging
- ###### <g>TODO:</g> Firebase.RemoteConfig
- ###### <r>TODO:</r> Firebase.Hosting
- ###### <g>DONE:</g> Google.PlayGames
- ###### <g>DONE:</g> Google.Ads
- ###### <o>TODO:</o> Unity3D IAP


- ###### <r>TODO:</r> Node.js
- ###### <o>TODO:</o> ???
- ###### <g>DONE:</g> <https://github.com/googleads/googleads-mobile-unity>

<br>

> **My Bold Text, in red color.**{: style="color: red; opacity: 0.80;" }

<br>

> ### [Google Play Console](https://play.google.com/console/developers)
>> - ###### [play-games-plugin-for-unity](https://github.com/playgameservices/play-games-plugin-for-unity/releases)
>>> ###### https://github.com/playgameservices/play-games-plugin-for-unity/tree/master/current-build
>> - ###### Unity3D 2021 'SDK not found' error.
>>> ###### Assets/GooglePlayGames/Editor/GPGSUtil.cs
```C#
        public static string GetAndroidSdkPath()
        {
            string sdkPath = EditorPrefs.GetString("AndroidSdkRoot");
448: #if UNITY_2019 || UNITY_2020 || UNITY_2021
            ...
```
>> - ##### Google Play Games -> Setup -> Android setup
![](Resources/R1280x0.png)
```xml
<?xml version="1.0" encoding="utf-8"?>
<!--Google Play game services IDs. Save this file as res/values/games-ids.xml in your project.-->
<resources>
  <!--app_id-->
  <string name="app_id" translatable="false">234033842797</string>
  <!--package_name-->
  <string name="package_name" translatable="false"></string>
  <!--leaderboard shot glass-->
  <string name="leaderboard_shot_glass" translatable="false">CgkI7ZSE7OcGEAIQAQ</string>
</resources>
```

```
Client ID: 
  234033842797-9921q0jsh68obdqa5bqhu3d7viq4vahl.apps.googleusercontent.com
```
<br>

> ### [Google AdMob](https://apps.admob.com/v2/home)
>> - ##### [Google Mobile Ads Unity Plugin v6.0.0](https://github.com/googleads/googleads-mobile-unity/releases/tag/v6.0.0)
```C#
...
using GoogleMobileAds.Api;
...
public class GoogleMobileAdsDemoScript : MonoBehaviour
{
    public void Start()
    {
        // Initialize the Google Mobile Ads SDK.
        MobileAds.Initialize(initStatus => { });
    }
}
```

>> - ##### [시작하기  |  Unity  |  Google Developers](https://developers.google.com/admob/unity/quick-start?hl=ko)
>>> ###### GoogleMobileAds -> Settings
![](Resources/unity_gma_inspector_admob.png)
```
Android: ca-app-pub-3940256099942544~3347511713
iOS    : ca-app-pub-3940256099942544~1458002511
```

>>> ###### Assets/GoogleMobileAds/Editor/GoogleMobileAdsSettings.cs
```C#
[SerializeField]
19:        private string adMobAndroidAppId = "ca-app-pub-3940256099942544~3347511713";//string.Empty;

        [SerializeField]
22:        private string adMobIOSAppId = "ca-app-pub-3940256099942544~1458002511";//string.Empty;
```

<br>

>> - ##### [배너 광고  |  Unity  |  Google Developers](https://developers.google.com/admob/unity/banner?hl=ko) - PASS
```C#
    #if UNITY_ANDROID
      string adUnitId = "ca-app-pub-3940256099942544/6300978111";
    #elif UNITY_IPHONE
      string adUnitId = "ca-app-pub-3940256099942544/2934735716";
    #else
      string adUnitId = "unexpected_platform";
    #endif

    this.bannerView = new BannerView(adUnitId, AdSize.Banner, AdPosition.Top);
```

>> - ##### [보상형 광고  |  Unity  |  Google Developers](https://developers.google.com/admob/unity/rewarded?hl=ko) - PASS
```C#
    string adUnitId;
    #if UNITY_ANDROID
        adUnitId = "ca-app-pub-3940256099942544/5224354917";
    #elif UNITY_IPHONE
        adUnitId = "ca-app-pub-3940256099942544/1712485313";
    #else
        adUnitId = "unexpected_platform";
    #endif

    this.rewardedAd = new RewardedAd(adUnitId);
```

<br>

> ### [Firebase](https://console.firebase.google.com/?hl=ko)
>> - ##### [Firebase Unity SDK](https://firebase.google.com/download/unity?authuser=0)
>> - ##### [Unity 프로젝트에 Firebase 추가](https://firebase.google.com/docs/unity/setup?hl=ko) - PASS
>> - ##### Firebase.Analytics - PASS
>>> - ###### Test device setup
>>>> To enable sending of DebugView data on a connected Android test device for a configured Firebase Analytics app, you can follow the step below:
>>>> 1. If you are simply working with single build variant, the following command is enough:
```bash
adb shell setprop debug.firebase.analytics.app [your_app_package_name]
```
>>>> 2. But if you are working with multiple build variants with different application IDs which are not the same as the app package name, be sure to execute the following command:
```bash
adb shell setprop debug.firebase.analytics.app [your_application_id]
```
>>>> Here, application ID is the app ID of your build variant found in the corresponding gradle file. For example, lets say you have x.gradle and y.gradle for two build variants x and y, and you also have the general build.gradle file. To debug the build variant x with application ID com.abc.x, the command will be:
```bash
adb shell setprop debug.firebase.analytics.app com.abc.x
```
>>>> Similarly, to debug the build variant y with application ID com.abc.y, the command will be:
```bash
adb shell setprop debug.firebase.analytics.app com.abc.y
```
>>>> This behavior persists until you explicitly disable it by executing the following command:
```bash
adb shell setprop debug.firebase.analytics.app .none.
```

<br>

```bash
adb shell setprop debug.firebase.analytics.app com.hunee.shotglass
```

>> - ##### Firebase.Auth - PASS
>>> - ###### [Unity를 사용하여 비밀번호 기반 계정으로 Firebase에 인증](https://firebase.google.com/docs/auth/unity/password-auth?authuser=0) - PASS
>>> - ###### [Unity에서 Google Play 게임 서비스를 사용하여 인증](https://firebase.google.com/docs/auth/unity/play-games?hl=ko) - PASS
>> - ##### Firebase.Messaging - PASS
```C#
    void SetFirebaseMessagingListeners() {
      Firebase.Messaging.FirebaseMessaging.TokenReceived += OnTokenReceived;
      Firebase.Messaging.FirebaseMessaging.MessageReceived += OnMessageReceived;
    }

    public void OnTokenReceived(object sender, Firebase.Messaging.TokenReceivedEventArgs token) {
      UnityEngine.Debug.Log("Received Registration Token: " + token.Token);
    }

    public void OnMessageReceived(object sender, Firebase.Messaging.MessageReceivedEventArgs e) {
      UnityEngine.Debug.Log("Received a new message from: " + e.Message.From);
```

<br>

```log
05-31 18:11:45.341  2401  2452 I Unity   : Received Registration Token: fxA77rkpTl--6NFPVD0Ky7:APA91bGSV9eo35gHnr2JwS8gOAGjfF2oRZGHlrrcjkAEZUhiPUXFN4G6eL4y0s1ZzFIC9nGrTiXr1y08HeVpwGsX0qSw6gjp7m_nZVBYd7RvMvqjSQfnsAROdcKT9GYIOPfEEilwaRRP
```
>>> - ##### [알림 작성 – Firebase Console](https://console.firebase.google.com/project/shot-glass-57056966/notification/compose?hl=ko&campaignId=3632850544257805467&dupe=true)

>> - ##### Firebase.RemoteConfig - ????

<br>

## Android

```bash
% vi ~/.bash_profile
export ANDROID_SDK_ROOT= ~/Library/Android/sdk
export NDK_ROOT=~/Library/Android/ndk

export ANDROID_HOME=$ANDROID_SDK_ROOT

export PATH=${PATH}:${ANDROID_SDK_ROOT}\tools:${ANDROID_SDK_ROOT}\platform-tools:${NDK_ROOT}
```

```bash
% vi ~/.zshrc
source ~/.bash_profile
```

> - ##### debug keystore
```bash
% keytool -keystore ~/.android/debug.keystore -list -v
Enter keystore password: android

Keystore type: jks
Keystore provider: SUN

Your keystore contains 1 entry

Alias name: androiddebugkey
Creation date: Jan 17, 2021
Entry type: PrivateKeyEntry
Certificate chain length: 1
Certificate[1]:
Owner: C=US, O=Android, CN=Android Debug
Issuer: C=US, O=Android, CN=Android Debug
Serial number: 1
Valid from: Sun Jan 17 15:01:38 KST 2021 until: Tue Jan 10 15:01:38 KST 2051
Certificate fingerprints:
	 SHA1: 9E:BC:4F:FD:EC:6A:30:E2:5D:35:8A:93:51:14:0C:5D:24:07:07:9C
	 SHA256: 1A:3C:93:57:E0:3A:81:F1:A3:46:45:24:CE:F5:EA:23:39:40:23:2F:7D:36:7E:7E:E1:01:0A:2A:A1:64:3E:A9
Signature algorithm name: SHA1withRSA (weak)
Subject Public Key Algorithm: 2048-bit RSA key
Version: 1


*******************************************
*******************************************



Warning:
<androiddebugkey> uses the SHA1withRSA signature algorithm which is considered a security risk. This algorithm will be disabled in a future update.
The JKS keystore uses a proprietary format. It is recommended to migrate to PKCS12 which is an industry standard format using "keytool -importkeystore -srckeystore /Users/jangjeonghun/.android/debug.keystore -destkeystore /Users/jangjeonghun/.android/debug.keystore -deststoretype pkcs12".
```

> - ##### sign verify
```bash
% keytool -printcert -jarfile apk_name.apk

Signer #1:

Signature:

Owner: C=US, O=Android, CN=Android Debug
Issuer: C=US, O=Android, CN=Android Debug
Serial number: 1
Valid from: Sun Jan 17 15:01:38 KST 2021 until: Tue Jan 10 15:01:38 KST 2051
Certificate fingerprints:
	 SHA1: 9E:BC:4F:FD:EC:6A:30:E2:5D:35:8A:93:51:14:0C:5D:24:07:07:9C
	 SHA256: 1A:3C:93:57:E0:3A:81:F1:A3:46:45:24:CE:F5:EA:23:39:40:23:2F:7D:36:7E:7E:E1:01:0A:2A:A1:64:3E:A9
Signature algorithm name: SHA1withRSA (weak)
Subject Public Key Algorithm: 2048-bit RSA key
Version: 1


Warning:
The certificate uses the SHA1withRSA signature algorithm which is considered a security risk. This algorithm will be disabled in a future update.
```

> - ##### [adb](https://developer.android.com/studio/command-line/adb?hl=ko)
```bash
% whereis adb 
~/Library/Android/sdk/platform-tools/adb

% adb shell ip -f inet addr show wlan0
% adb tcpip 5555

% adb connect 172.30.1.24
% adb devices
List of devices attached
172.30.1.24:5555	device

% adb shell ps | grep shotglass
u0_a177       1096  3439 2113008 264548 0                   0 S com.hunee.shotglass

% adb -s 172.30.1.24 ...

```

> - ##### [adb logcat](https://developer.android.com/studio/command-line/logcat?hl=ko)

```bash
% adb shell ps | grep shotglass
u0_a177       1096  3439 2113008 264548 0                   0 S com.hunee.shotglass

% adb logcat -c   
% adb logcat --pid 2401 -v color | grep Unity
```


