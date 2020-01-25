[missionNamespace, "arsenalOpened", { 
    disableSerialization;
    private "_control";
    private _display = _this select 0;
    {
        _control = _display displayCtrl _x;
        _control ctrlRemoveAllEventHandlers "buttonclick";
        _control ctrlRemoveAllEventHandlers "onKeyDown";
        _control ctrlRemoveAllEventHandlers "onKeyUp";
        _control ctrlEnable false; 
        ctrlDelete _control;
    } forEach [44150];
    _display displayAddEventHandler ["keydown", "_this select 3"]; 
}] call BIS_fnc_addScriptedEventHandler;