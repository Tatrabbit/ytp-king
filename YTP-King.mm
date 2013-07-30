#define VER_FILENAME.VER  YTP-King.ver

#include "rainChu.mmh"

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
		
		<$Files "bin\Release\*.dll" DestDir="INSTALLDIR">
		<$Files "bin\Release\*.exe" DestDir="INSTALLDIR">
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
		
		<$Files "bin\Release\plugins\*.dll"
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
