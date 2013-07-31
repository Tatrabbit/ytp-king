@echo off
REM  YTP King - Easy to use sentence mixer
REM  Copyright (C) 2013  Alex "rainChu" Haddad
REM  
REM  This program is free software: you can redistribute it and/or modify
REM  it under the terms of the GNU General Public License as published by
REM  the Free Software Foundation, either version 3 of the License, or
REM  (at your option) any later version.
REM  
REM  This program is distributed in the hope that it will be useful,
REM  but WITHOUT ANY WARRANTY; without even the implied warranty of
REM  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
REM  GNU General Public License for more details.
REM  
REM  You should have received a copy of the GNU General Public License
REM  along with this program.  If not, see <http://www.gnu.org/licenses/>.


IF NOT "%2" == "Debug" (
	IF NOT "%2" == "Release" (
		GOTO USAGE
	)
) ELSE (
	IF NOT "%3" == "x86" (
		IF NOT "%3" == "x64" (
			GOTO USAGE
		)
	)
)

SET p=%CD%

CD "%1\bin\%2

REM wxWidgets
IF "%2" == "Debug" (
	REM Blindly assume the rest are here, too.
	IF NOT EXIST "wxbase295ud_vc110.dll" (
		COPY "%WX_LIB_PATH%\vc110_dll\wxbase295ud_vc110.dll" .
		COPY "%WX_LIB_PATH%\vc110_dll\wxmsw295ud_core_vc110.dll" .
	) ELSE (
		REM Don't even copy other files below these lines.
		ECHO Files already copied, ending post-build.bat now.
		GOTO END
	)
) ELSE (
	REM Blindly assume the rest are here, too.
	IF NOT EXIST "wxbase295u_vc110.dll" (
		COPY "%WX_LIB_PATH%\vc110_dll\wxbase295u_vc110.dll" .
		COPY "%WX_LIB_PATH%\vc110_dll\wxmsw295u_core_vc110.dll" .
	) ELSE (
		REM Don't even copy other files below these lines.
		ECHO Files already copied, ending post-build.bat now.
		GOTO END
	)
)

REM GStreamer

IF "%3" == "x86" (
	SET GSTREAMER_SDK_ROOT=%GSTREAMER_SDK_ROOT_X86%
) ELSE (
	SET GSTREAMER_SDK_ROOT=%GSTREAMER_SDK_ROOT_X86_64%
)

COPY "%GSTREAMER_SDK_ROOT%\bin\*.dll" .

MKDIR plugins
COPY "%GSTREAMER_SDK_ROOT%\lib\gstreamer-0.10\*.dll" .\plugins\

:END
CD "%p%"
GOTO EOF

:USAGE
ECHO %0 SolutionPath ^<Debug^|Release^> ^<x86^|x64^>
ECHO.
PAUSE

:EOF