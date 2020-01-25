// Игрок - зевс
if (playerSide isEqualTo civilian || !isNil { player getVariable "playerIsZeus" }) then { AF_playerIsZeus = true; } else { AF_playerIsZeus = false; };

#include "hpp\globalsClient.hpp" // Глобальные переменные Клиента
#include "scripts\!localCompile.hpp" // Компиляция локальных функций
#include "eventHandlers\localHandlers\!init.hpp" // Локальные эвентХандлеры

if (playerSide in AF_blockedSides) exitWith { failMission "AF_side_blocked"; };

execVM "scripts\fn_jammedWeapons.sqf"; // клин оружия
[ "InitializePlayer" ,  [ player ]]  call  BIS_fnc_dynamicGroups; // динамические группы

// Отключение урона игроку (на всякий случай)
player allowDamage false;

// Откл. Команд в чате
showSubtitles false;

if ("AF_randomRespawn" call BIS_fnc_getParamValue isEqualto 1) then
{
	// Спавн на карте при первом заходе (далее - на spawn-points)
	if ( (count (player call BIS_fnc_getRespawnPositions)) < 2 ) then
	{
		private _spawnPos = switch playerSide do
		{
			case east: { spawnEast };
			case west: { spawnWest };
			case resistance: { spawnResistance };
			case civilian: { spawnCivilian };
		};
		_spawnPos = [_spawnPos, 0, 25, 2, 0, 0, 0,[], [_spawnPos,_spawnPos]] call BIS_fnc_findSafePos;
		player setPos _spawnPos;
	} else { private _oldPl = player; forceRespawn player; _oldPl spawn { sleep 5; deleteVehicle _this; }; };

	// Маркер и флаг базы
	if AF_playerIsZeus then
	{
		{
			_marker = createMarkerLocal [format["baseMark%1", _forEachIndex], _x];
			_marker setMarkerShapeLocal "ICON";
			_marker setMarkerTypeLocal (["Faction_CUP_NATO", "flag_CSAT", "flag_FIA"] select _forEachIndex);

			// flag
			private _obj = "FlagPole_F" createVehicleLocal _x;
			_obj allowDamage false;
			_obj setFlagTexture (["\A3\Data_F\Flags\Flag_nato_CO.paa", "\A3\Data_F\Flags\Flag_CSAT_CO.paa", "\A3\Data_F\Flags\Flag_FIA_CO.paa"] select _forEachIndex);
		} forEach [spawnWest, spawnEast, spawnResistance]
	} else {
		switch playerSide do
		{
			case west:
			{
				_marker = createMarkerLocal ["baseMark0", spawnWest];
				_marker setMarkerShapeLocal "ICON";
				_marker setMarkerTypeLocal "Faction_CUP_NATO";
				
				// flag
				private _obj = "FlagPole_F" createVehicleLocal spawnWest;
				_obj allowDamage false;
				_obj setFlagTexture "\A3\Data_F\Flags\Flag_nato_CO.paa";
			};

			case east:
			{
				_marker = createMarkerLocal ["baseMark0", spawnEast];
				_marker setMarkerShapeLocal "ICON";
				_marker setMarkerTypeLocal "flag_CSAT";

				// flag
				private _obj = "FlagPole_F" createVehicleLocal spawnEast;
				_obj allowDamage false;
				_obj setFlagTexture "\A3\Data_F\Flags\Flag_CSAT_CO.paa";
			};

			case resistance:
			{
				_marker = createMarkerLocal ["baseMark0", spawnResistance];
				_marker setMarkerShapeLocal "ICON";
				_marker setMarkerTypeLocal "flag_FIA";

				// flag
				private _obj = "FlagPole_F" createVehicleLocal spawnResistance;
				_obj allowDamage false;
				_obj setFlagTexture "\A3\Data_F\Flags\Flag_FIA_CO.paa";
			};
		};
	};
};

// Включение урона игроку
if !AF_playerIsZeus then { [] spawn { sleep 10; player allowDamage true; }; };

// Проверка на зевса
[] spawn { waitUntil {!isNull(findDisplay 46)}; sleep 2; player remoteExec ["AF_curatorInit",2]; };

// Инициализация скрипта перепаковки магазинов
[] execVM "scripts\magRepack\MagRepack_init_sv.sqf";

// Меню Зевс-игроков
if AF_playerIsZeus then { execVM "scripts\menuEngine\!init.sqf"; };