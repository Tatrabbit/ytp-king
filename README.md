YTP King
========

Notice
------
*This program is currently on hiatus. It's been years since I started it, and I'm likely to one day get back to it, but currently, I have other projects distracting me.*

The original readme is below:

-------------------------------

It's a sentence mixer app for Windows Desktop, licensed under the GNU GPL. Designed to be easy to learn and simple to use for anybody to make YTP (YouTube Poops), to make it possible for beginners and, for experts, to get the audio done quicker and with less fuss.

**THIS PROGRAM IS A WORK IN PROGRESS, YOU'RE WELCOME TO HELP MAKE IT,
BUT IT IS NOT USABLE YET!**

Basic video editing and video file export is planned, but it's not the focus. The main feature is the quick and efficient mixing of spoken word, and audio export. Video export will be possible, but as a convenience only. The video exists more to give visual feedback to audio composition.

Compiling
---------

**You are welcome to fork this, of course, ~~but please wait until I'm able to stabalize the code base.~~ (It's been too long and I won't die on this hill. I encourage you to play around with it.)** It's a mess right now, only one week old at the time of this writing.

This app is being built with cross-platform compatibility in mind, but currently, project files only exist for Windows. In addition, there are some platform specific things which are Windows only. However, I'm taking great pains to make sure that it will compile on other platforms without too much effort.

Especially helpful would be someone with Mac OSX, as I don't have access to one. I will soon port the code to Ubuntu Linux once the app becomes useable, and possibly make binary debian packages for it.

If you have any luck getting it to run on your platform, let me know!

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
