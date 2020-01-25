private _par = -1;
if (!isNil "_this" && { !(_this isEqualTo []) }) then { _par = _this; };

player action ["SWITCHWEAPON",player,player,_par];