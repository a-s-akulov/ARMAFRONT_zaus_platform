#define DEFAULT_PARAMS [ [0,0,0,1], "EtelkaMonospaceProBold", [0,0,0,0], [-0.687879,0.0090909,0.727273,0.727273] ]  // параметры по умолчанию: [ textColor, textFont, backgroundColor, [x,y,w,h] ]

private _mode = _this;
switch _mode do
{
	case "load":
	{
		ME_params = profileNamespace getVariable "ME_kat_params";
		if (isNil "ME_params") exitWith { ME_params = DEFAULT_PARAMS; false };
		if !("ARRAY" isEqualTo typeName ME_params) exitWith { ME_params = DEFAULT_PARAMS; false };
		if !((count ME_params) isEqualTo (count DEFAULT_PARAMS)) exitWith { ME_params = DEFAULT_PARAMS; false };
		private _nice = true;
		{
			if !((typeName _x) isEqualTo (typeName (DEFAULT_PARAMS select _forEachIndex))) exitWith { _nice = false; };
		} forEach ME_params;
		if !_nice exitWith { ME_params = DEFAULT_PARAMS; false };
		true
	};

	case "save":
	{
		if (isNil "ME_params") exitWith { false };
		if !("ARRAY" isEqualTo typeName ME_params) exitWith { false };
		if !((count ME_params) isEqualTo (count DEFAULT_PARAMS)) exitWith { false };
		private _nice = true;
		{
			if !((typeName _x) isEqualTo (typeName (DEFAULT_PARAMS select _forEachIndex))) exitWith { _nice = false; };
		} forEach ME_params;
		profileNamespace setVariable ["ME_kat_params",ME_params];
		saveProfileNamespace;
		true
	};

	default { DEFAULT_PARAMS };
};