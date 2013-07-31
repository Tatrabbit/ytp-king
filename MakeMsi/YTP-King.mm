#define VER_FILENAME.VER  YTP-King.ver

; After you've installed MakeMSI, you should edit this file in your
; Program Files/Make MSI installation. Include your own personal
; details.
#include "DEPT.MMH"


; Default department
#define? DEPT_ARP_URL_PUBLISHER           http://www.rainChu.com
#define? DEPT_ARP_URL_TECHNICAL_SUPPORT   http://www.rainChu.com
#define? COMPANY_SUMMARY_SCHEMA           110      ;;Minimum v1.1 Installer



;----------------------------------------------------------------------------
;--- Override/set some standard defaults ------------------------------------
;----------------------------------------------------------------------------
#define? DBG_ALL                                   Y         ;;Add MAKEMSI debugging to "console file"
#define? DBG_SAY_LOCATION                          call Say2Logs <$DBG_INDENT> || '  ' || time() || ' '  ;;Adding time makes it a bit slower but useful for debugging slow builds...
#define? COMMONFRAMEWORK_ZIP_SOURCE_FOR_BACKUP     N         ;;No "insurance" until I bother to install "info zip"...
#define? DEFAULT_SERVICE_CONTROL_UNINSTALL_EVENTS            ;;I think this option is safer than the MAKEMSI default
#define? DEFAULT_SERVICE_CONTROL_INSTALL_EVENTS              ;;I think this option is better
#define? DEFAULT_FILE_WANT_FILEHASH                Y         ;;My box can generate MD5 hashes!
#define? COMPANY_PREPROCESS_LICENCE_FILE           Y         ;;Default is to preprocess licence files
#define? MAKEMSI_HTML_EXTENSION                    hta       ;;Default extension (HTML Application - gets around WINXP SP2 issue)
#define? UISAMPLE_LEFTSIDE_TEXT_FONT_COLOR         &H7F0000  ;;Medium Blue in BGR (believe it or not...)

#(
    #define? UISAMPLE_LEFTSIDE_TEXT
    Ugly side banner will soon be replaced
#)
#(
    #define? @VALIDATE_TEXT_FOR_MISSINGDATA                   ;;Example only as now duplicates exact text as new default value
    This column is not mentioned in the _Validation table.
    Either add the validation data or use the "@validate" parameter
    on the "row" command (or alter its default).
#)

#(
	<$Feature "App"
		Title="YTP King"
		Description="The application itself"
		Level="1"
	>
		<$DirectoryTree
			Key="INSTALLDIR"
				Dir="c:\Program Files\rainChu\YTP King"
				CHANGE="\"
				PrimaryFolder="Y"
		>
		
		<$Files "..\bin\Release\*.dll" DestDir="INSTALLDIR">
		<$Files "..\bin\Release\*.exe" DestDir="INSTALLDIR">
	<$/Feature>

	;; GStreamer
	;; Installed by default
	<$Feature "GStreamer_Plugins"
		Title="Necessary GStreamer Files"
		Description=^Necessary plugin files for GStreamer.
			Unless you know what you're doing, you need this.^
		Level="3"
	>
		<$DirectoryTree
			Key="GSTREAMER_INSTALL_DIR"
			Dir="[INSTALLDIR]\gstreamer\0.10\lib"
		>

		<$Component "Environment" Directory_="<$AnyDir>" LM="Y">
			<$Environment
				Name="GST_PLUGIN_PATH"
				VALUE="[GSTREAMER_INSTALL_DIR]"
				HOW="SET_DURING_INSTALLATION,DELETE_ON_UNINSTALL,CREATE_IF_NONEXISTANT"
				>
		<$/Component>
		
		<$Files "..\bin\Release\plugins\*.dll"
			DestDir="GSTREAMER_INSTALL_DIR">
	<$/Feature>
#)


;---------------------------------------------------------------------
;--- Better Welcome Dialog message -----------------------------------
;---------------------------------------------------------------------
#(
	;--- Better welcome information, #1 ------------------------------
	#define UISAMPLE_WELCOME_VB_EXPRESSION_FIRST_PARA
		"This will install [ProductName] for you."
#)

#(
	;--- Better welcome information, #2 ------------------------------
	#define UISAMPLE_WELCOME_VB_EXPRESSION_BEFORE_CLICK_NEXT_PARA
		& vbCRLF & vbCRLF
		& "YTP King uses GStreamer, which will be installed as well by "
		& "default. If you don't have GStreamer already, then choosing "
		& "not to install it will cause things to break!"
#)

#(
   ;--- "Click Next to Continue" -------------------------------------
   #define UISAMPLE_WELCOME_VB_EXPRESSION_CLICK_NEXT_PARA
   & vbCRLF & vbCRLF
   & "Are you a true warrior? Mah boi, click ""Next"" to strive for "
   & "peace and continue."
#)
