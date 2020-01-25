private _descExtPath = str missionConfigFile;
mDir = compile str (_descExtPath select [0, count _descExtPath - 15]);
mDir = call mDir; // расположение корня миссии

earplugs = false; // беруши