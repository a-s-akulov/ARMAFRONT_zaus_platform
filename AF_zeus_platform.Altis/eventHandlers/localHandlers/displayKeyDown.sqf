waitUntil {!isNull(findDisplay 46)};
findDisplay 46 displayAddEventHandler ["KeyDown",
{	
	private _key = _this select 1;
	if (_key isEqualTo 0xB8) exitWith { [] spawn AF_Crew_Hud; }; // Список народа в авто по ALT
	if (_key isEqualTo 0xCF) exitWith { [] spawn Bee_earplugs; }; // Беруши пчелы
	if (_key isEqualTo 0x0B) exitWith { [] spawn AF_weapsBack; }; // Оружие за спину при нажатии на 0
}];