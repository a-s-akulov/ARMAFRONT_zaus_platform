private _descExtPath = str missionConfigFile;
mDir = compile str (_descExtPath select [0, count _descExtPath - 15]);
mDir = call mDir; // расположение корня миссии

AF_Curators		= ["76561198120620722","76561197996339648"];

AF_blockedSides	= [];
publicVariable 'AF_blockedSides';