#include "defines.h"
/*
	Author: Bryan "Tonic" Boardwine
	
	Description:
	Called via addAction and opens the TAW View Distance Menu
*/
if(isNull (findDisplay MENU_IDD)) then {
	if(!createDialog "TAW_VDMenu") exitWith {hint "Something went wrong, the menu won't open?"};
};
disableSerialization;

{
	ctrlSetText[SEL(_x,0),str(SEL(_x,1))];
} foreach [[INFANTRY_EDIT,tawvd_foot],[GROUND_EDIT,tawvd_car],[AIR_EDIT,tawvd_air],[OBJECT_EDIT,tawvd_object],[DRONE_EDIT,tawvd_drone]];

//Setup the sliders
{
	if(!isNil "tawvd_maxRange") then {
		slidersetRange [_x select 0,100,tawvd_maxRange];
	} else {
		slidersetRange [_x select 0,100,20000];
	};
	private _a = (findDisplay MENU_IDD) displayCtrl (_x select 0);
	_a sliderSetSpeed [100,100,100];
	_a ctrlSetTooltip (_x select 2);
	sliderSetPosition[_x select 0, _x select 1];
} foreach [[INFANTRY_SLIDER,tawvd_foot,localize "STR_chvd_TooltipInf"],[GROUND_SLIDER,tawvd_car,localize "STR_chvd_TooltipCar"],[AIR_SLIDER,tawvd_air,localize "STR_chvd_TooltipAir"],[OBJECT_SLIDER,tawvd_object,localize "STR_chvd_TooltipObj"],[DRONE_SLIDER,tawvd_drone,localize "STR_chvd_TooltipUAV"]];

((findDisplay MENU_IDD) displayCtrl 2931) cbSetChecked tawvd_syncObject;

if(tawvd_syncObject) then {
	ctrlEnable [OBJECT_SLIDER,false];
	ctrlEnable [OBJECT_EDIT,false];
} else {
	ctrlEnable [OBJECT_SLIDER,true];
	ctrlEnable [OBJECT_EDIT,true];
};
ctrlSetText [29501,localize "STR_chvd_low"];
ctrlSetText [29502,localize "STR_chvd_standart"];
ctrlSetText [29503,localize "STR_chvd_high"];
ctrlSetText [295000,localize "STR_chvd_title"];
ctrlSetText [295001,localize "STR_chvd_foot"];
ctrlSetText [295002,localize "STR_chvd_car"];
ctrlSetText [295003,localize "STR_chvd_air"];
ctrlSetText [295004,localize "STR_chvd_object"];
ctrlSetText [295005,localize "STR_chvd_UAV"];
ctrlSetText [295006,localize "STR_chvd_grass"];
ctrlSetText [295007,localize "STR_chvd_objViewDistance"];
ctrlSetText [295010,localize "STR_chvd_sync"];
ctrlSetText [295009,localize "STR_chvd_saves"];