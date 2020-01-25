/*
	author : Killzone_Kid
	modified : KOKaKOJIbKA
*/
_player = player;
_player setVariable ["KOKa_allowFire",true];
_player setVariable ["KOKa_countFire",0];

_player addEventHandler ["FiredMan", {
	params ["_player","_class"];

	_num = (_player getVariable "KOKa_countFire") + 1;
	_player setVariable ["KOKa_countFire",_num];

	if (
		(random 100 > 99.5) &&
		(primaryWeapon _player isEqualTo _class) &&
		(!isNil {_player getVariable "KOKa_allowFire"}) &&
		(isNull objectParent _player) &&
		((_player getVariable "KOKa_countFire") > 100)
	) then {
		_player spawn {
			_frame = diag_frameno;
			_weapon = currentWeapon _this;
			_ammo = _this ammo _weapon;
			if (_ammo > 0) then {
				_this setVariable ["KOKa_allowFire",nil];
				_this setAmmo [_weapon, 0];
				waitUntil {_frame < diag_frameno};
				_this setAmmo [_weapon, _ammo];
			};
			true
		};
	};
}];

_player addEventHandler ["Reloaded", {
	params ["_player","_class"];
	if (
		(primaryWeapon _player isEqualTo _class) &&
		(isNil {_player getVariable "KOKa_allowFire"}) &&
		(isNull objectParent _player)
	) then {
		_player setVariable ["KOKa_allowFire",true];
		_player setVariable ["KOKa_countFire",0];
	};
}];

true