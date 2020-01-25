waitUntil {!isNull(findDisplay 12)};
_display		= findDisplay 12;
_control		= _display displayCtrl 51;


if AF_playerIsZeus then
{
	_control ctrlAddEventHandler ["MouseButtonClick",
	{
		if (!alive player || isObjectHidden player) exitWith {};
		if (_this select 6) then
		{
			private _position = findDisplay 12 displayCtrl 51 ctrlMapScreenToWorld getMousePosition;
			player setPos _position;
		};
	}];
};