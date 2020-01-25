private _side = _this;
if (_side in AF_blockedSides) exitWith { hint "Эта сторона уже заблокирована"; };
AF_blockedSides pushBack _side;
publicVariable 'AF_blockedSides';
[[_side,name player],
{
	if (playerSide isEqualTo (_this select 0)) then { failMission "AF_side_blocked"; };
	if (playerSide isEqualTo civilian) then { hint parseText format["%1<br/>заблокировал сторону<br/>%2",_this select 1,_this select 0]; };
}] remoteExec ["spawn",0];