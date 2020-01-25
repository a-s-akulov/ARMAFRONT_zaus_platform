/*
	by KOKaKOJIbKA, addapted by Katletka
*/

if (isNull objectParent player) exitWith {true};

private _assigned = assignedVehicle player;
private _arr = [];

{
	_x params ["_crew"];
	private _pic = if (_assigned isKindOf "Air") then {
		if (
			(driver _assigned isEqualTo _crew) ||
			({_assigned turretUnit [_x] isEqualTo _crew} count [0,1,2,3,4,5,6,7,8,9] > 0)
		) then {
			if ((driver _assigned isEqualTo _crew) || (_assigned turretUnit [0] isEqualTo _crew)) then {
				"<img size='1' color='#99ffffff' image='pictures\actions\getinpilot_ca.paa'/>"
			} else {
				"<img size='1' color='#99ffffff' image='pictures\actions\getingunner_ca.paa'/>"
			}
		} else {
			"<img size='1' color='#99ffffff' image='pictures\actions\getincargo_ca.paa'/>"
		}
	} else {
		if ((driver _assigned isEqualTo _crew) || (gunner _assigned isEqualTo _crew)) then {
			if (driver _assigned isEqualTo _crew) then {
				"<img size='1' color='#99ffffff' image='pictures\actions\getindriver_ca.paa'/>"
			} else {
				"<img size='1' color='#99ffffff' image='pictures\actions\getingunner_ca.paa'/>"
			}
		} else {
			if (commander _assigned isEqualTo _crew) then {
				"<img size='1' color='#99ffffff' image='pictures\actions\getincommander_ca.paa'/>"
			} else {
				"<img size='1' color='#99ffffff' image='pictures\actions\getincargo_ca.paa'/>"
			}
		}
	};
	_arr append [format ["<t align='left'>                     %1     %2</t><br/>",_pic, name _crew]];
} count crew _assigned;

_arr = _arr joinString "";

hintSilent parseText format [
	"<br/><img size='4' color='#595923' image='pictures\hint_pic\vehiclegui_ca.paa'/><br/><br/>
	<t size='1.1' color='#99ffffff'>%1</t><br/>",
	_arr
];
