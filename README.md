YTP King
========

An easy to use sentence mixer app for Windows, licensed under the GNU GPL.

Compiling
---------

This app is being built with cross-platform compatibility in mind, but currently, project files only exist for Windows. If you have any luck getting it to run on your platform, let me know!

### Requirements

* [GStreamer SDK For Windows][1] (Tested with 2013.6 Congo)
* [wxWidgets Development Release][2] (Tested with 2.9.5)
* Microsoft Visual Studio 2012

[1]: http://docs.gstreamer.com/display/GstSDK/Installing+on+Windows
[2]: http://www.wxwidgets.org/

### Setting up GStreamer

First, install the GStreamer x86 and/or x64 installers. Install the GStreamer SDK runtime, then the GStreamer SDK Development package. Once it's installed, verify that your Windows Environment variables are set correctly. Unless GStreamer SDK is in your User folder, I recommend setting System variables, not User variables. Assuming you installed the SDK to **C:\gstreamer-sdk**, then the enviroment variables you've set are as follows:

|           Name            |                    Value                        |  Arch  |
| :------------------------ | ----------------------------------------------: | :----: |
| GSTREAMER_SDK_ROOT_X86    | C:\gstreamer-sdk\0.10\x86                       | x86    |
| GSTREAMER_SDK_ROOT_X86_64 | C:\gstreamer-sdk\0.10\x86_64                    | x64    |
| GST_PLUGIN_PATH           | C:\gstreamer-sdk\0.10\x86\lib\gstreamer-0.10    | x86    |
| GST_PLUGIN_PATH           | C:\gstreamer-sdk\0.10\x86_64\lib\gstreamer-0.10 | x64    |

Once that's set, you should be good to go!

### Setting up wxWidgets

Install the [wxWidgets prebuilt 2.9.5][3] debug binaries release binaries, and header files. I keep mine in **C:\wxWidgets-2.9.5**, but you may install them anywhere. Once installed, you need to set environment variables to point to it.

|           Name            |                    Value                        |
| :------------------------ | ----------------------------------------------: |
| WX_INCLUDE_PATH           | C:\wxWidgets-2.9.5\include                      |
| WX_LIB_PATH               | C:\wxWidgets-2.9.5\lib                          |

That should be it! You're done!

[3]: http://sourceforge.net/projects/wxwindows/files/2.9.5/binaries/

### Compilation

It should hopefully be a simple matter of pressing the Build button in MSVS from here. Everything that was needed is now in place. But, Murphy's law says otherwise. Good luck!