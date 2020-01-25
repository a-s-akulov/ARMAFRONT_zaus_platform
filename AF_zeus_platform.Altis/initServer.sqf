#include "hpp\globalsServer.hpp" // Глобальные переменные Сервера
#include "hpp\serverFunctions.hpp" // Быстрые функции сервера (для частого использования)

[ "Initialize" ]  call BIS_fnc_dynamicGroups; // динамические группы

if ("AF_randomRespawn" call BIS_fnc_getParamValue isEqualto 1) then
{
	private _spawnLocations = nearestLocations [[0,0,0], ["CityCenter","NameCity","NameCityCapital","NameVillage","Strategic","Name"], 50000];

	private ["_position", "_str", "_obj"];
	{
		_position = locationPosition (_spawnLocations deleteAT floor random count _spawnLocations);
		_position = [_position, 0, 75, 7, 0, 10, 0,[], [_position,_position]] call BIS_fnc_findSafePos;

		// base objects
		if !(_forEachIndex isEqualTo 3) then
		{
			_obj = createVehicle ["CUP_BAF_VehicleBox", _position getPos [3,0], [], 0, "CAN_COLLIDE"];
			_obj allowDamage false;
			clearMagazineCargoGlobal _obj;
			[ "AmmoboxInit", [ _obj, true, {(_this distance _target) < 10} ] ] call BIS_fnc_arsenal;
		};

		// resp pos
		[_x,_position,"MAIN BASE"] call BIS_fnc_addRespawnPosition;

		_str = switch _x do { case West: { "West" }; case East: { "East" }; case Resistance: { "Resistance" }; case Civilian: { "Civilian" }; };
		missionNamespace setVariable [format["spawn%1", _str], _position];
		publicVariable format["spawn%1", _str];
	} forEach [West, East, Resistance, Civilian];
};