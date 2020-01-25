AF_curatorInit = // инициализация куратора при подключении игркоа к серверу
{
	private _unit			= _this;
	private _UID 			= getPlayerUID _unit;
	if (_UID in AF_Curators || side group _unit isEqualTo civilian || !isNil { _unit getVariable "playerIsZeus" }) then { _unit spawn AF_curatorAdd; };
};

AF_curatorAdd = // выдача куратора игроку
{
	private _unit 			= _this;
	private _UID 			= getPlayerUID _unit;
	private _curators		= allCurators;
	private _arrID			= _curators findIf { (str _x) isEqualTo _UID };

	if (_arrID > -1 ) exitWith { _unit assignCurator (_curators select _arrID); [[],{ pIsCurator = true; }] remoteExec ["spawn",_unit]; };

	private _groupLogic		= [group (_curators select 0),createGroup sideLogic] select (_curators isEqualTo []);

	private _curator		= _groupLogic createUnit ["moduleCurator_f",[0,0,0],[],0,"CAN_COLLIDE"];
	_unit assignCurator _curator;
	_curator setVehicleVarName _UID;
	[[],{ pIsCurator = true; }] remoteExec ["spawn",_unit];
};

AF_curatorRespawn = // переподключение игрока к его куратору после смерти
{
	private _unit 			= _this;
	private _UID 			= getPlayerUID _unit;
	private _curators		= allCurators;
	private _arrID			= _curators findIf { (str _x) isEqualTo _UID };
	if (_arrID > -1) then { _unit spawn AF_curatorAdd; } else { [[],{ pIsCurator = nil; }] remoteExec ["spawn",_unit]; };
};

AF_curatorRemove = // удаление куратора
{
	private _unit			= _this;
	private _UID 			= getPlayerUID _unit;
	private _curators		= allCurators;
	private _arrID			= _curators findIf { (str _x) isEqualTo _UID };

	if (_arrID > -1) then 
	{
		private _curator = _curators select _arrID;
		private _group = group _curator;
		unassignCurator _curator;
		deleteVehicle _curator;
		if (allCurators isEqualTo []) then { deleteGroup _group; };
	};
	[[],{ pIsCurator = nil; }] remoteExec ["spawn",_unit];
};

// переноска предмета
AF_objInVeh =
{
	private _obj 			= _this select 0;
	private _caller			= _this select 1;
	private _veh			= (_obj nearEntities[["Car","Tank","Air","Ship"],8]) select 0;
	private _pic			= "pictures\hint_pic\vehiclegui_ca.paa";

	if (!alive _obj || !alive _caller) exitWith {};
	if (isNil "_veh") exitWith 								{ [_pic,"noCarObj"] remoteExec ["AF_hintPicture",_caller]; };

	if !(isNil {_veh getVariable "objLoad"}) exitWith 	{ [_pic,"tooManyObj"] remoteExec ["AF_hintPicture",_caller]; };
			
	if (!alive _veh) exitWith 								{ [_pic,"deadVehObj"] remoteExec ["AF_hintPicture",_caller]; };

	if (!isNull attachedTo _obj) exitWith 				{ [_pic,"isTakenObj"] remoteExec ["AF_hintPicture",_caller]; };
	
	_obj allowDamage false;
	_obj setPos [0,0,0];
	private _handler 		= _veh addMPEventHandler ["MPKilled", 
								{
									private _veh = _this select 0;
									private _obj 	= (_veh getVariable "objLoad") select 0;
									_veh removeAction _action;
									private _cPos = _veh getRelPos [6,180];

									_obj setPos _cPos;
									_obj allowDamage true;
									_obj setDamage 1;
									
									remoteExec ["",_veh];
									[_veh,{ _this removeAction (_this getVariable "cAction"); }] remoteExec ["spawn",0];
									_veh removeMPEventHandler ["MPKilled",_thisEventHandler];
								}];
	_veh setVariable ["objLoad",[_obj,_handler]];
	[_veh,{ private _act = _this addAction [format["<t color='#00FFFF'>%1</t>",localize "addActFromCarObj"],"[[(_this select 0),(_this select 1)],{ [_this select 0,_this select 1] spawn AF_objOutVeh; }] remoteExec ['spawn',2];",[],10,false,true,"","isNull objectParent _this",5]; _this setVariable ["cAction",_act]; }] remoteExec ["spawn",-2,_veh];
	[[configFile >> "CfgVehicles" >> typeOf _veh] call BIS_fnc_displayName,{ hint parseText format["<br/><img size='3' color='#595923' align='center' image='pictures\hint_pic\vehiclegui_ca.paa' /><br/><br/>
			<t size='1.2' color='#99ffffff' >%1</t><br/><br/><t size='1.3' color='#ff0000' >%2</t>",localize "actInCarObj",_this]; }]remoteExec ["spawn",_caller];
};

AF_objOutVeh =
{
	private _veh 			= _this select 0;
	private _caller			= _this select 1;
	private _obj			= (_veh getVariable "objLoad") select 0;
	private _handler		= (_veh getVariable "objLoad") select 1;
	if (isNil "_handler" || !alive _obj || !alive _caller) exitWith {};
	private _cPos = _veh getRelPos [6,180];
	
	_obj setPos _cPos;

	_veh removeMPEventHandler ["MPKilled",_handler];
	remoteExec ["",_veh];
	[_veh,{ _this removeAction (_this getVariable "cAction"); _this setVariable ["cAction",nil]; }] remoteExec ["spawn",-2];
	_veh setVariable ["objLoad",nil];

	["pictures\hint_pic\vehiclegui_ca.paa","actFromCarObj"] remoteExec ["AF_hintPicture",_caller];
	sleep 2;
	_obj allowDamage true;
};

AF_objTakeIt =
{
	// DraggingAmmoBox	Тащит ящик, ящика нет

	private _obj 			= _this select 0;
	private _caller			= _this select 1;
	private _pic			= "pictures\hint_pic\carry_box.paa";

	if (!alive _obj || !alive _caller) exitWith {};

	if (!isNull attachedTo _obj) exitWith 			{ [_pic,"isTakenObj"] remoteExec ["AF_hintPicture",_caller]; };

	if (count ((attachedObjects _caller) select { !isNull _x }) > 0) exitWith 	{ [_pic,"tooManyInfObj"] remoteExec ["AF_hintPicture",_caller]; };

	private _handler 		= _caller addMPEventHandler ["MPKilled", 
								{
									private _caller = _this select 0;
									{ _x setDamage 1; } forEach attachedObjects _caller;
									_caller removeMPEventHandler ["MPKilled",_thisEventHandler];
								}];

	remoteExec ["AF_weapsBack",_caller];

	_caller setVariable ["hanObj",_handler];
	_obj attachTo [_caller,[0,0.5,0],"pelvis"];
	_obj setDir 90;
	[_pic,"doTookObj"] remoteExec ["AF_hintPicture",_caller];
	[[],{ player addAction [format["<t color='#00FFFF'>%1</t>",localize 'addActPutDownObj'],"[[(_this select 0),(_this select 2)],{ [_this select 0,_this select 1] spawn AF_objPutIt; }] remoteExec ['spawn',2];",[],12,true,true,"","",0]; }] remoteExec ["spawn",_caller];
};

AF_objPutIt =
{
	private _caller			= _this select 0;
	private _action			= _this select 1;
	private _obj			= attachedObjects _caller;
	private _handler		= _caller getVariable "hanObj";
	if (!alive _caller || (count ((attachedObjects _caller) select { !isNull _x }) == 0) || isNil "_handler") exitWith {};
	_obj					= _obj select ((count _obj) -1);
	if (!alive _obj) exitWith {};

	_caller removeMPEventHandler ["MPkilled",_handler];

	[[_obj,_action],
	{ 
		detach (_this select 0); 
		player removeAction (_this select 1);
		["pictures\hint_pic\carry_box.paa","doPutObj"] spawn AF_hintPicture;
		0 spawn AF_weapsBack;
	}] remoteExec ["spawn",_caller];
};

AF_cleanUp =
{
	//author: SOLDAT1C
	//Modified: KOKaKOJIbKA, Katletka
	private ["_all_groups","_m","_removeGrp","_members"];
	_all_groups = allGroups;
	for "_m" from 0 to ((count _all_groups) - 1) do {
		_removeGrp = true;
		_groupoup = (_all_groups select _m);
		if (!isNull _groupoup) then {
			_members = (units _groupoup);
			{
				if (alive _x) then {
					_removeGrp = false;
				};
			} forEach _members;
		};
		if (_removeGrp && !isNull _groupoup) then {
			deleteGroup _groupoup;
		};
	};
	{
		deleteVehicle _x;
	} forEach allMissionObjects "WeaponHolder","GroundWeaponHolder","WeaponHolderSimulated", "rhs_k36d5_seat";
	{
		if (_x in vehicles) then 
		{
			private _veh = _x;
			{ _veh deleteVehicleCrew _x; } forEach (crew _veh);
		};
		deleteVehicle _x;
	} forEach allDead;
};