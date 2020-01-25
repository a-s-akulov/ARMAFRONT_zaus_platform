player setUnitLoadout (player getVariable["Saved_Loadout",[]]); // выдать сохраненное снаряжение

// ниже - клин оружия
player addAction ["", {
	playSound3D ['a3\sounds_f\weapons\Other\dry9.wss', (_this select 0)];
}, "", 0, false, true, "DefaultAction", "isNil {player getVariable ""KOKa_allowFire""} && (primaryWeapon player isEqualTo currentWeapon player) && (isNull objectParent player)"];


// Инициализация зевса после смерти
[] spawn { sleep 4; if (!isNil "pIsCurator") then { player remoteExec["AF_curatorRespawn",2]; }; };

// Удаление трупа
if !( isNil "AF_killedUnit" ) then { deleteVehicle AF_killedUnit; AF_killedUnit = nil; };