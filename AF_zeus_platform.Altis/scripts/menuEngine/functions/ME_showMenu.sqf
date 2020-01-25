disableSerialization;
"menuEngineNavigate" cutRsc ["menuEngineNavigate","PLAIN",-1,false];
if ("load" call ME_profileParams) then { hint parseText localize "ME_profileParamsLoaded"; };
private _control = (uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001;
_control ctrlSetTextColor (ME_params select 0);
_control ctrlSetFont (ME_params select 1);
_control ctrlSetBackgroundColor (ME_params select 2);
_control ctrlSetPosition (ME_params select 3);
_control ctrlCommit 0;

private _handler = ME_temp param [0, -1];
if !(_handler isEqualTo -1) then { (findDisplay 46) displayRemoveEventHandler ["keyDown", _handler]; };
_handler = (findDisplay 46) displayAddEventHandler ["keyDown","private _key = _this select 1; _key = [0x4F,0x50,0x51,0x4B,0x4C,0x4D,0x47,0x48,0x49,0x52,0x53] find _key; if !(_key isEqualTo -1) then { _key spawn ME_dataUpdate; true }"];
ME_temp set [0, _handler];