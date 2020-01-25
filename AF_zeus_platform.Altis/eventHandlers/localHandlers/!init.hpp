#include "arsenalOpened.sqf"
#include "displayKeyDown.sqf"
#include "playersNames.sqf"

if ("AF_playersOnMap" call BIS_fnc_getParamValue isEqualto 1) then { execVM "eventHandlers\localHandlers\playerMapMarkers.sqf"; }; // Отображение игроков на карте
if AF_playerIsZeus then { execVM "eventHandlers\localHandlers\curatorMapTeleport.sqf"; }; // Телепорт по аль-клику на карте