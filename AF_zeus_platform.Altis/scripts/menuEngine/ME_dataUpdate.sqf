#include "menuStructure.hpp"

#define POSTFIX localize "ME_postfix_default"
#define POSTFIX_HIDE localize "ME_postfix_hideMenu"

disableSerialization;

private _dir		= ME_currentDir;
private _keyInput	= _this param [0,10,[0]];

private _display 	= uiNameSpace getVariable "menuEngineNavigate";
private _control 	= _display displayCtrl 1001;

private _displayText = format["%1 >> ",localize "ME_mainMenu_default"];

_checkLocalize =
{
	private _strLocalize = _this;
	_strLocalize = localize _strLocalize;
	if (_strLocalize isEqualTo "") then { _strLocalize = _this; };

	_strLocalize
};

if (_keyInput isEqualTo 9) then
{
	if !(_dir isEqualTo []) then
	{
		_dir deleteAt (count _dir - 1);
	};
};

if (_keyInput isEqualTo 10) then
{
	if ( (0 isEqualTo count _dir) && (10 isEqualTo _this) ) then { _dir = -1; } else {	_dir = []; };
};

// Закрыть меню 
if (_dir isEqualTo -1) exitWith
{
	(findDisplay 46) displayRemoveEventHandler ["keyDown", ME_temp select 0];
	"menuEngineNavigate" CutFadeOut 1;
	private _handler = (findDisplay 46) displayAddEventHandler ["keyDown", "private _key = _this select 1; if (_key isEqualTo 0x53) then { call ME_showMenu; };"];
	ME_temp set [0, _handler];
};

private "_onLoadAction";

{
	_displayText = _displayText + format["%1 >> ",(_menuStructure select _x) call _checkLocalize];
	if (_forEachIndex isEqualTo (count _dir -1)) then { _onLoadAction = count _menuStructure - 1; _onLoadAction = (_menuStructure select (count _menuStructure - 1)) select _onLoadAction; };
	_menuStructure = (_menuStructure select (count _menuStructure - 1)) select _x;
} forEach _dir;

if (_keyInput < 9) exitWith
{
	private _selectedOption = -1;
	if (_keyInput < (count _menuStructure - 1)) then { _selectedOption = _menuStructure param [_keyInput,-1,[""],count _menuStructure - 1]; };
	if !(_selectedOption isEqualTo -1) then
	{
		_displayText = _displayText + format["%1 >> <br/><br/>",_selectedOption call _checkLocalize];

		_onLoadAction = count _menuStructure - 1;
		_onLoadAction = (_menuStructure select (count _menuStructure - 1)) select _onLoadAction;

		_menuStructure = (_menuStructure select (count _menuStructure - 1)) select _keyInput;
		if (typeName _menuStructure isEqualTo "CODE") exitWith { [] spawn _menuStructure; };
		if !(typeName _menuStructure isEqualTo "ARRAY") exitWith { hint parseText format["ME_dataUpdate.sqf<br/>ERROR<br/>Attempt to call not-expected data type<br/>dir %1<br/>key %2",_dir,_keyInput]; };
		_dir pushBack _keyInput;

		ME_currentDir = _dir;
		for "_i" from 0 to (count _menuStructure - 2) do
		{
			_displayText = _displayText + format["%1 | %2<br/>",_i + 1, (_menuStructure select _i) call _checkLocalize];
		};
		if !(_dir isEqualTo []) then { _displayText = _displayText + POSTFIX; };
		_control ctrlSetStructuredText parseText _displayText;

		if !(isNil "_onLoadAction") then
		{
			if !(typeName _onLoadAction isEqualTo "ARRAY") exitWith { hint parseText format["ME_dataUpdate.sqf<br/>ERROR<br/>onLoadAction exists, but has not-expected data type<br/>dir %1<br/>key %2 - %3",_dir,_keyInput,typeName _onLoadAction]; };
			if (_keyInput > count _onLoadAction) exitWith {}; 
			_onLoadAction = _onLoadAction select _keyInput;
			if !(isNil "_onLoadAction") then
			{
				if (typeName _onLoadAction isEqualTo "CODE") exitWith { [] spawn _onLoadAction; };
				hint parseText format["ME_dataUpdate.sqf<br/>ERROR<br/>onLoadAction exists, but has not-expected data type<br/>dir %1<br/>key %2 - %3",_dir,_keyInput,typeName _onLoadAction];
			};
		};
	};
};
_displayText = _displayText + "<br/><br/>";

ME_currentDir = _dir;
for "_i" from 0 to (count _menuStructure - 2) do
{
	_displayText = _displayText + format["%1 | %2<br/>",_i + 1, (_menuStructure select _i) call _checkLocalize];
};
_displayText = _displayText + ([POSTFIX, POSTFIX_HIDE] select (_dir isEqualTo []));
_control ctrlSetStructuredText parseText _displayText;
if !(isNil "_onLoadAction") then
{
	if !(typeName _onLoadAction isEqualTo "ARRAY") exitWith { hint parseText format["ME_dataUpdate.sqf<br/>ERROR<br/>onLoadAction exists, but has not-expected data type<br/>dir %1<br/>key %2 - %3",_dir,_keyInput,typeName _onLoadAction]; };
	private _dirAction = _dir select (count _dir - 1);
	if (_dirAction > count _onLoadAction) exitWith {};
	_onLoadAction = _onLoadAction select _dirAction;
	if !(isNil "_onLoadAction") then
	{
		if (typeName _onLoadAction isEqualTo "CODE") exitWith { [] spawn _onLoadAction; };
		hint parseText format["ME_dataUpdate.sqf<br/>ERROR<br/>onLoadAction exists, but has not-expected data type<br/>dir %1 - %2",_dir,typeName _onLoadAction];
	};
};