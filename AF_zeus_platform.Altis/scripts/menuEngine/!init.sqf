#define FOLDER "scripts\"

ME_dataUpdate		= compile preprocessFileLineNumbers (FOLDER + "menuEngine\ME_dataUpdate.sqf");
ME_setUnitTrait		= compile preprocessFileLineNumbers (FOLDER + "menuEngine\functions\ME_setUnitTrait.sqf");
ME_blockSide		= compile preprocessFileLineNumbers (FOLDER + "menuEngine\functions\ME_blockSide.sqf");
ME_showMenu			= compile preprocessFileLineNumbers (FOLDER + "menuEngine\functions\ME_showMenu.sqf");
ME_profileParams	= compile preprocessFileLineNumbers (FOLDER + "menuEngine\functions\ME_profileParams.sqf");
ME_currentDir = [];
ME_temp = [];

waitUntil {!isNull(findDisplay 46)};
call ME_showMenu;