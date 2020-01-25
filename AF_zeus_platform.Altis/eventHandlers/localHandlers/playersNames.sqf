["AF_playersNames", "onEachFrame",
{
	_conf = mDir;
    {
        if (alive _x) then {
            _dist = (player distance _x) / 15;
            _color = [([playerSide,false] call BIS_fnc_sideColor),[0.227,0.773,0,1]] select (groupId (group _x) isEqualTo groupId (group player));
            if (cursorTarget != _x) then {
                _color set [3, 1 - _dist]
            };
            drawIcon3D [
                "",
                _color,
                [
                    visiblePosition _x select 0,
                    visiblePosition _x select 1,
                    (visiblePosition _x select 2) +
                    ((_x modelToWorld (
                        _x selectionPosition 'head'
                    )) select 2) + 0.45 + _dist / 1.5
                ],
                2 - (0.1 * _dist),
                2 - (0.1 * _dist),
                0,
                [name _x,format["%1 (300)",name _x]] select ((lifeState _x) isEqualTo "INCAPACITATED"),
                2,
                0.035,
                'RobotoCondensedBold'
            ];
        };
    } count ( [ (allPlayers - [player]) select { side group _x isEqualto playerSide }, allPlayers - [player] ] select AF_playerIsZeus );
}] call BIS_fnc_addStackedEventHandler;