private _unit = _this select 0;
private _trait = _this select 1;
switch typeName _unit do
{
	case "ARRAY":
	{
		if (0 isEqualTo count _unit) exitWith { hint "Нет юнитов в радиусе 10 м."; };
		{ [[_x, _trait],{ (_this select 0) setUnitTrait [_this select 1, true, true]; }] remoteExec ["spawn"]; } forEach _unit;
		hint parseText format["%1 юнит(ов) теперь умеет %2",count _unit,switch _trait do 
		{
			case "engineer" 			: { "чинить" };
			case "explosiveSpecialist" 	: { "разминировывать" };
			case "medic" 				: { "лечить" };
			case "UAVHacker" 			: { "взламывать БПА" };
			default		 				{ "ERROR" };
		}];
	};

	default
	{
		if (isNull _unit || { !(_unit in allUnits) }) exitWith { hint "Нет юнита по курсору для выдачи навыка"; };
		[[_unit, _trait],{ (_this select 0) setUnitTrait [_this select 1, true, true]; }] remoteExec ["spawn"];
		hint parseText format["Юнит '%1'<br/>теперь умеет %2",name _unit,switch _trait do 
		{
			case "engineer" 			: { "чинить" };
			case "explosiveSpecialist" 	: { "разминировывать" };
			case "medic" 				: { "лечить" };
			case "UAVHacker" 			: { "взламывать БПА" };
			default		 				{ "ERROR" };
		}];
	};
};