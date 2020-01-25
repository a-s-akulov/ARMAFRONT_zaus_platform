waitUntil {!(isNull (findDisplay 12) || isNull (findDisplay 46))};

findDisplay 12 displayCtrl 51 ctrlAddEventHandler ["Draw",
	"_this call {
		{
			private _pl = _x;
			if (_pl in allPlayers && { alive _pl && ((side group _pl) isEqualTo side group player || AF_playerIsZeus) }) then {
				private _i = _pl call {
					private _i = format [""%1"",
						switch true do {
							case ((vehicle _this) isKindOf ""Car"") : {""\A3\ui_f\data\map\markers\nato\n_motor_inf.paa""};
							case ((vehicle _this) isKindOf ""Tank"") : {""\A3\ui_f\data\map\markers\nato\n_armor.paa""};
							case ((vehicle _this) isKindOf ""Apc"") : {""\A3\ui_f\data\map\markers\nato\n_armor.paa""};
							case ((vehicle _this) isKindOf ""Plane"") : {""\A3\ui_f\data\map\markers\nato\n_plane.paa""};
							case ((vehicle _this) isKindOf ""Helicopter"") : {""\A3\ui_f\data\map\markers\nato\n_air.paa""};
							case ((vehicle _this) isKindOf ""Ship"") : {""\A3\ui_f\data\map\markers\nato\n_naval.paa""};
							case ((vehicle _this) isKindOf ""Man"") : {""\A3\ui_f\data\map\markers\nato\n_inf.paa""};
							default {""\A3\ui_f\data\map\markers\nato\n_inf.paa""};
						}
					];
					_i
				};
				private _p = _pl call {
					private _p = getPosASL vehicle _this;
					_p
				};
				private _c = [([side group _pl,false] call BIS_fnc_sideColor),[0.227,0.773,0,1]] select (groupId (group _pl) isEqualTo groupId (group player));
				private _s = 14;
				private _txt = ""["";
				if(vehicle _x != _x)then
				{
					_vCrew = crew (vehicle _x);
					for ""_k"" from 0 to ((count _vCrew)-1) do {
						_txt = _txt + (name(_vCrew select _k));
						if(_k < ((count _vCrew)-1))then{
							_txt = _txt + "","";
						};
					};
					_txt = _txt  + ""]"";
				}else{
					_txt = [name _x,format['%1 (300)',name _x]] select ((lifeState _x) isEqualTo 'INCAPACITATED');
				};
				_this select 0 drawIcon [
					_i,
					_c,
					_p,
					_s,
					_s,
					0,
					_txt,
					1,
					0.03,
					""TahomaB"",
					""right""
				];
			};
		} count allPlayers;
	};"
];

if AF_playerIsZeus then
{
	findDisplay 46 displayAddEventHandler ["KeyDown", { 
		if (inputAction "CuratorInterface" > 0) then
		{
			[] spawn 
			{
				waitUntil {!isNull (findDisplay 312)};
				findDisplay 312 displayCtrl 50 ctrlAddEventHandler ["Draw",
				"_this call {
					{
						private _pl = _x;
						if (_pl in allPlayers && { alive _pl && ((side group _pl) isEqualTo side group player || AF_playerIsZeus) }) then {
							private _i = _pl call {
								private _i = format [""%1"",
									switch true do {
										case ((vehicle _this) isKindOf ""Car"") : {""\A3\ui_f\data\map\markers\nato\n_motor_inf.paa""};
										case ((vehicle _this) isKindOf ""Tank"") : {""\A3\ui_f\data\map\markers\nato\n_armor.paa""};
										case ((vehicle _this) isKindOf ""Apc"") : {""\A3\ui_f\data\map\markers\nato\n_armor.paa""};
										case ((vehicle _this) isKindOf ""Plane"") : {""\A3\ui_f\data\map\markers\nato\n_plane.paa""};
										case ((vehicle _this) isKindOf ""Helicopter"") : {""\A3\ui_f\data\map\markers\nato\n_air.paa""};
										case ((vehicle _this) isKindOf ""Ship"") : {""\A3\ui_f\data\map\markers\nato\n_naval.paa""};
										case ((vehicle _this) isKindOf ""Man"") : {""\A3\ui_f\data\map\markers\nato\n_inf.paa""};
										default {""\A3\ui_f\data\map\markers\nato\n_inf.paa""};
									}
								];
								_i
							};
							private _p = _pl call {
								private _p = getPosASL vehicle _this;
								_p
							};
							private _c = [([side group _pl,false] call BIS_fnc_sideColor),[0.227,0.773,0,1]] select (groupId (group _pl) isEqualTo groupId (group player));
							private _s = 14;
							private _txt = ""["";
							if(vehicle _x != _x)then
							{
								_vCrew = crew (vehicle _x);
								for ""_k"" from 0 to ((count _vCrew)-1) do {
									_txt = _txt + (name(_vCrew select _k));
									if(_k < ((count _vCrew)-1))then{
										_txt = _txt + "","";
									};
								};
								_txt = _txt  + ""]"";
							}else{
								_txt = [name _x,format['%1 (300)',name _x]] select ((lifeState _x) isEqualTo 'INCAPACITATED');
							};
							_this select 0 drawIcon [
								_i,
								_c,
								_p,
								_s,
								_s,
								0,
								_txt,
								1,
								0.03,
								""TahomaB"",
								""right""
							];
						};
					} count allPlayers;
				};"];
			};
		}; 
		false 
	}];
};