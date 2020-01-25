private _menuStructure =
[
	"Миссия",
	"Игроки",
	"Транспорт",
	"Объекты",
	"Zeus",
	"Настройки меню",
	[
		[
			"Завершить",
			"Стороны",
			"Очистка карты",
			[
				[
					"Победа синих",
					"Победа красных",
					"Победа зеленых",
					"Победа гражданских",
					"Все проиграли",
					[
						{ [west,{ failMission (["AF_fail_default","AF_complete_default"] select (playerSide isEqualTo _this)); }] remoteExec ["spawn",0]; },
						{ [east,{ failMission (["AF_fail_default","AF_complete_default"] select (playerSide isEqualTo _this)); }] remoteExec ["spawn",0]; },
						{ [resistance,{ failMission (["AF_fail_default","AF_complete_default"] select (playerSide isEqualTo _this)); }] remoteExec ["spawn",0]; },
						{ [civilian,{ failMission (["AF_fail_default","AF_complete_default"] select (playerSide isEqualTo _this)); }] remoteExec ["spawn",0]; },
						{ "AF_fail_default" remoteExec ["failMission",0]; }
					]
				],

				[
					"Заблокировать \ разблокировать стороны для игроков",
					[
						[
							"Заблокировать синих",
							"Заблокировать красных",
							"Заблокировать зеленых",
							"Список заблокированных сторон",
							"Разблокировать все стороны",
							[
								{ west spawn ME_blockSide; },
								{ east spawn ME_blockSide; },
								{ resistance spawn ME_blockSide; },
								{ private _str = 'Список заблокированных сторон:<br/>'; { if (_forEachIndex > 0) then { _str = _str + ', '; }; _str = _str + str _x; } forEach AF_blockedSides; hint parseText _str; },
								{ AF_blockedSides = []; publicVariable 'AF_blockedSides'; [name player,{ if AF_playerIsZeus then { hint parseText format["%1<br/>разблокировал все стороны",_this]; }; }] remoteExec ['spawn',-2]; }
							]
						],

						// onLoadActions
						[
							// "Заблокировать \ разблокировать стороны для игроков"
							{ private _str = 'Список заблокированных сторон:<br/>'; { if (_forEachIndex > 0) then { _str = _str + ', '; }; _str = _str + str _x; } forEach AF_blockedSides; hint parseText _str; }
						]

					]
				],

				[
					"Выполнить очистку карты",
					[
						{ [] remoteExec ["AF_cleanUp", 2]; }
					]
				]

			]
		],

		[
			"Роли",
			"Снаряжение",
			[
				[
					"Операции с юнитом по курсору",
					"Операции с юнитами в радиусе 10 м.",
					[
						[
							"Научить чинить",
							"Научить разминировывать",
							"Научить лечить",
							"Научить взламывать БПА",
							"Вывод списка игроков с навыками",
							"Сбросить навыки юнита",
							[
								{ [cursorObject,"engineer"] spawn ME_setUnitTrait; },
								{ [cursorObject,"explosiveSpecialist"] spawn ME_setUnitTrait; },
								{ [cursorObject,"medic"] spawn ME_setUnitTrait; },
								{ [cursorObject,"UAVHacker"] spawn ME_setUnitTrait; },
								{
									private _player = allPlayers select { _x getUnitTrait "engineer" || _x getUnitTrait "explosiveSpecialist" || _x getUnitTrait "medic" || _x getUnitTrait "UAVHacker" };
									private _str	= "Список игроков c особыми навыками:";
									{
										private _target = _x;
										private _count 	= 0;
										_str = _str + format["<br/>%1. %2 - ",_forEachIndex + 1,name _target];
										{
											if (_target getUnitTrait (_x select 0)) then { if (_count > 0) then { _str = _str + ", "; }; _str = _str + (_x select 1); _count = _count + 1; };
										} forEach [["engineer","механик"],["explosiveSpecialist","сапёр"],["medic","медик"],["UAVHacker","хакер"]];
									} forEach _player;
									hint parseText _str;
								},
								{
									private _unit = cursorObject;
									if (isNull _unit || { !(_unit in allUnits) }) exitWith { hint "Нет юнита по курсору для сброса навыков"; };
									{ [[_unit,_x],{ (_this select 0) setUnitTrait [_this select 1, 0]; }] remoteExec ["spawn"]; } forEach ["engineer","explosiveSpecialist","medic","UAVHacker"];
									hint parseText format ["Юнит '%1'<br/>больше не имеет особых навыков",name _unit];
								}

							]
						],

						[
							"Научить чинить (10 м.)",
							"Научить разминировывать (10 м.)",
							"Научить лечить (10 м.)",
							"Научить взламывать БПА (10 м.)",
							"Вывод списка игроков с навыками",
							"Сбросить навыки юнитов (10 м.)",
							[
								{ private _units = (allUnits select { (player distance _x) < 10 }) - [player]; [_units,"engineer"] spawn ME_setUnitTrait; },
								{ private _units = (allUnits select { (player distance _x) < 10 }) - [player]; [_units,"explosiveSpecialist"] spawn ME_setUnitTrait; },
								{ private _units = (allUnits select { (player distance _x) < 10 }) - [player]; [_units,"medic"] spawn ME_setUnitTrait; },
								{ private _units = (allUnits select { (player distance _x) < 10 }) - [player]; [_units,"UAVHacker"] spawn ME_setUnitTrait; },
								{
									private _player = allPlayers select { _x getUnitTrait "engineer" || _x getUnitTrait "explosiveSpecialist" || _x getUnitTrait "medic" || _x getUnitTrait "UAVHacker" };
									private _str	= "Список игроков c особыми навыками:";
									{
										private _target = _x;
										private _count 	= 0;
										_str = _str + format["<br/>%1. %2 - ",_forEachIndex + 1,name _target];
										{
											if (_target getUnitTrait (_x select 0)) then { if (_count > 0) then { _str = _str + ", "; }; _str = _str + (_x select 1); _count = _count + 1; };
										} forEach [["engineer","механик"],["explosiveSpecialist","сапёр"],["medic","медик"],["UAVHacker","хакер"]];
									} forEach _player;
									hint parseText _str;
								},
								{
									private _units = (allUnits select { (player distance _x) < 10 }) - [player]; 
									if (0 isEqualTo count _units) exitWith { hint "Нет юнитов в радиусе 10 метров"; };
									{ private _unit = _x; { [[_unit, _x], { (_this select 0) setUnitTrait [_this select 1, 0]; }] remoteExec ["spawn"]; } forEach ["engineer","explosiveSpecialist","medic","UAVHacker"]; } forEach _units;
									hint parseText format ["Особые навыки сброшены у %1 юнитов(а)",count _units];
								}

							]
						],

						// onLoadActions
						[
							// "Операции с юнитом по курсору"
							{
								private _player = allPlayers select { _x getUnitTrait "engineer" || _x getUnitTrait "explosiveSpecialist" || _x getUnitTrait "medic" || _x getUnitTrait "UAVHacker" };
								private _str	= "Список игроков c особыми навыками:";
								{
									private _target = _x;
									private _count 	= 0;
									_str = _str + format["<br/>%1. %2 - ",_forEachIndex + 1,name _target];
									{
										if (_target getUnitTrait (_x select 0)) then { if (_count > 0) then { _str = _str + ", "; }; _str = _str + (_x select 1); _count = _count + 1; };
									} forEach [["engineer","механик"],["explosiveSpecialist","сапёр"],["medic","медик"],["UAVHacker","хакер"]];
								} forEach _player;
								hint parseText _str;
							},

							// "Операции с юнитами в радиусе 10 м."
							{
								private _player = allPlayers select { _x getUnitTrait "engineer" || _x getUnitTrait "explosiveSpecialist" || _x getUnitTrait "medic" || _x getUnitTrait "UAVHacker" };
								private _str	= "Список игроков c особыми навыками:";
								{
									private _target = _x;
									private _count 	= 0;
									_str = _str + format["<br/>%1. %2 - ",_forEachIndex + 1,name _target];
									{
										if (_target getUnitTrait (_x select 0)) then { if (_count > 0) then { _str = _str + ", "; }; _str = _str + (_x select 1); _count = _count + 1; };
									} forEach [["engineer","механик"],["explosiveSpecialist","сапёр"],["medic","медик"],["UAVHacker","хакер"]];
								} forEach _player;
								hint parseText _str;
							}
						]
					]
					
				],

				[
					"Выдать\изменить свое снаряжение",
					"""Копипаст"" снаряжения",
					[
						[
							"Выдать свое снаряжение юниту по курсору",
							"Выдать свое снаряжение всем игрокам в радиусе 10 м.",
							"Выдать себе снаряжение юнита по курсору",
							[
								{
									private _unit = cursorObject;
									if (isNull _unit || { !(_unit in allUnits) }) exitWith { hint "Нет юнита по курсору для выдачи снаряжения"; };
									_unit setUnitLoadout [(getUnitLoadout player),true];
								},
								{
									private _players = allPlayers select { _x distance player < 10};
									{ _x setUnitLoadout [(getUnitLoadout player),true]; } forEach _players;
									hint parseText format["Вы выдали<br/>%1 игрокам(у)<br/>свое снаряжение",count _players];
								},
								{
									private _unit = cursorObject;
									if (isNull _unit || { !(_unit in allUnits) }) exitWith { hint "Нет юнита по курсору для копирования снаряжения"; };
									player setUnitLoadout (getUnitLoadout [_unit,true]); 
									hint "Вы выдали себе снаряжение юнита по курсору";
								}
							]
						],

						[
							"Копировать свое снаряжение в буфер",
							"Копирвоать снаряжение юнита по курсору в буфер",
							"Выдать себе снаряжение из буфера",
							"Выдать юниту по курсору снаряжение из буфера",
							"Выдать всем игрокам в радиусе 10 м. снаряжение из буфера",
							"Проверить наличие данных в буфере",
							[
								{ ME_buffer_loadout = getUnitLoadout [player,true]; hint "Вы скопировали свое снаряжение в буфер"; },
								{
									private _unit = cursorObject;
									if (isNull _unit || { !(_unit in allUnits) }) exitWith { hint "Нет юнита по курсору для копирования снаряжения"; };
									ME_buffer_loadout = getUnitLoadout [_unit,true];
									hint parseText format["Вы скопировали снаряжение<br/>%1<br/>в буфер обмена",name _unit];
								},
								{
									if (isNil "ME_buffer_loadout") exitWith { hint "В буфере нет сохраненного снаряжения"; }; 
									player setUnitLoadout ME_buffer_loadout;
									hint "Вы выдали себе снаряжение из буфера обмена";
								},
								{
									private _unit = cursorObject;
									if (isNil "ME_buffer_loadout") exitWith { hint "В буфере нет сохраненного снаряжения"; };
									if (isNull _unit || { !(_unit in allUnits) }) exitWith { hint "Нет юнита по курсору для выдачи снаряжения"; };
									_unit setUnitLoadout ME_buffer_loadout;
									hint parseText format["Вы выдали<br/>%1<br/>снаряжение из буфера обмена",name _unit];
								},
								{
									if (isNil "ME_buffer_loadout") exitWith { hint "В буфере нет сохраненного снаряжения"; };
									private _players = allPlayers select { _x distance player < 10};
									{ _x setUnitLoadout ME_buffer_loadout; } forEach _players;
									hint parseText format["Вы выдали<br/>%1 игрокам(у)<br/>снаряжение из буфера обмена",count _players];
								},
								{ if (isNil "ME_buffer_loadout") then { hint "В буфере нет сохраненного снаряжения"; } else { hint "В буффере есть сохраненное снаряжение" }; }
							]
						],

						// onLoadActions
						[
							// "Выдать\изменить свое снаряжение"
							{  },
							// "'Копипаст' снаряжения"
							{ if (isNil "ME_buffer_loadout") then { hint "В буфере нет сохраненного снаряжения"; } else { hint "В буфре есть сохраненное снаряжение" }; }
						]

					]
				],

				// onLoadActions
				[
					// "Роли"
					{
						private _player = allPlayers select { _x getUnitTrait "engineer" || _x getUnitTrait "explosiveSpecialist" || _x getUnitTrait "medic" || _x getUnitTrait "UAVHacker" };
						private _str	= "Список игроков c особыми навыками:";
						{
							private _target = _x;
							private _count 	= 0;
							_str = _str + format["<br/>%1. %2 - ",_forEachIndex + 1,name _target];
							{
								if (_target getUnitTrait (_x select 0)) then { if (_count > 0) then { _str = _str + ", "; }; _str = _str + (_x select 1); _count = _count + 1; };
							} forEach [["engineer","механик"],["explosiveSpecialist","сапёр"],["medic","медик"],["UAVHacker","хакер"]];
						} forEach _player;
						hint parseText _str;
					}
				]
			]
			
		],

		[
			"Починить транспорт по курсору",
			"Пополнить боезапас транспорта по курсору",
			"Заправить транспорт по курсору",
			"Взорвать транспорт по курсору",
			"Удалить транспорт по курсору (с экипажем)",
			"Отключить / включить симуляцию объекта по курсору",
			[
				{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; _target setDamage 0; hint "Объект по курсору отремонтирован"; },
				{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; if !(_target in vehicles) exitWith { hint "Объект по курсору - не транспорт!"; }; if !(alive _target) exitWith { hint "Трансопрт по курсору уже уничтожен, пополнение боекомплекта невозможно"; }; _target setVehicleAmmo 1; hint "Транспорту по курсору пополнен боезапас"; },
				{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; if !(_target in vehicles) exitWith { hint "Объект по курсору - не транспорт!"; }; if !(alive _target) exitWith { hint "Трансопрт по курсору уже уничтожен, дозаправка невозможна"; }; _target setFuel 1; hint "Транспорт по курсору заправлен"; },
				{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; _target setDamage 1; hint "Объект по курсору уничтожен"; },
				{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; deleteGroup group ((crew _target) select 0); { _target deleteVehicleCrew _x; } forEach (crew _target); deleteVehicle _target; hint "Объект по курсору удален"; },
				{
					private _target = cursorObject; if !(isNull _target) then 
					{
						private _enabled = simulationEnabled _target;
						_target enableSimulation !_enabled;
						hint parseText format ["Симуляция объекта<br/>%1<br/>теперь %2",typeOf _target,["включена","выключена"] select _enabled];
					} else { hint "Нет объекта по курсору"; }; 
				}
			]
		],

		[
			"Особое...",
			"Очистка инвентаря...",
			"",
			"Удалить объект по курсору",
			"Уничтожить объект по курсору",
			"Уничтожить объект по курсору (без спецэффектов)",
			"Отключить / включить неуязвимость объекта по курсору",
			"Отключить / включить симуляцию объекта по курсору",
			[
				[
					"Ящики с виртуальным арсеналом",
					"Взаимодействия с объектами",
					[
						[
							"Создать ящик с арсеналом (полный арсенал) - тип 1",
							[
								{
									private _obj = createVehicle ["CUP_BAF_VehicleBox", player getRelPos [5,0],[],0,"CAN_COLLIDE"];
									_obj setDir direction player;
									clearMagazineCargoGlobal _obj;
									[ "AmmoboxInit", [ _obj, true, {(_this distance _target) < 10} ] ] call BIS_fnc_arsenal;
									hint "Создан ящик с полным виртуальным арсеналом (тип 1)";
								}
							]
						],

						[
							"Мобильность",
							[
								[
									"Переноска объекта на руках",
									"Транспортировка объекта в технике",
									[
										[
											"Сделать объект по курсору переносимым - !! НЕ ОБРАТИМО !!",
											[
												{
													_target = cursorObject;
													if (isNull _target) exitWith { hint "Нет объекта по курсору"; };
													if !(isNil { _target getVariable "vehTransportableObject" }) exitWith { hint "Объект по курсору уже может перевозиться в технике!" };
													[_target,
													{
														_this addAction [format["<t color='#00FFFF'>%1</t>",localize 'addActTakeObj'],
														"
															[
																[_this select 0,_this select 1],
																{ 
																	[_this select 0,_this select 1] spawn AF_objTakeIt;
																}
															] remoteExec ['spawn',2];
														",[],11,false,true,"","",5]; 
													}] remoteExec ["spawn",-2,_target];
													_target setVariable ["vehTransportableObject", true];
													hint "Объект по курсору теперь можно переносить";
												}
											]
										],

										[
											"Сделать объект по курсору транспортируемым в технике - !! НЕ ОБРАТИМО !!",
											[
												{
													_target = cursorObject;
													if (isNull _target) exitWith { hint "Нет объекта по курсору"; };
													if !(isNil { _target getVariable "bringinObject" }) exitWith { hint "Объект по курсору уже переносимый!" };

													[_target,
													{
														_this addAction [format["<t color='#00FFFF'>%1</t>",localize 'addActInCarObj'],"[[(_this select 0),(_this select 1)],{ [_this select 0,_this select 1] spawn AF_objInVeh; }] remoteExec ['spawn',2];",[],10,false,true,"","",5];
													}] remoteExec ["spawn",-2,_target];
													_target setVariable ["bringinObject", true];
													hint "Объект по курсору теперь можно перевозить в транспорте";
												}
											]
										]
									]
								]
							]
						]
					]
				],

				[
					"Очистить все 'items' инвентаря объекта по курсору",
					"Очистить все рюкзаки инвентаря объекта по курсору",
					"Очистить всё вооружение инвентаря объекта по курсору",
					"Очистить все боеприпасы инвентаря объекта по курсору",
					"",
					"Очистить инвентарь полностью объекта по курсору",
					[
						{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; clearItemCargoGlobal _target; hint "Все 'items' удалены из инвентаря объекта по курсору"; },
						{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; clearBackpackCargoGlobal _target; hint "Все рюкзаки удалены из инвентаря объекта по курсору"; },
						{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; clearWeaponCargoGlobal _target; hint "Всё вооружение удалено из инвентаря объекта по курсору"; },
						{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; clearMagazineCargoGlobal _target; hint "Все боеприпасы удалены из инвентаря объекта по курсору"; },
						{},
						{
							private _target = cursorObject;
							if (isNull _target) exitWith { hint "Нет объекта по курсору"; };
							clearItemCargoGlobal _target;
							clearBackpackCargoGlobal _target;
							clearWeaponCargoGlobal _target;
							clearMagazineCargoGlobal _target;
							hint "Весь инвентарь объекта по курсору очищен";
						}
					]
				],

				{},
				{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; deleteGroup group ((crew _target) select 0); { _target deleteVehicleCrew _x; } forEach (crew _target); deleteVehicle _target; hint "Объект по курсору удален"; },
				{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; _target setDamage 1; hint "Объект по курсору уничтожен"; },
				{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; _target setDamage [1,false]; hint "Объект по курсору уничтожен"; },
				{ private _target = cursorObject; if (isNull _target) exitWith { hint "Нет объекта по курсору"; }; if (isDamageAllowed _target) then { _target allowDamage false; hint "Объект по курсору теперь НЕуязвим"; } else { _target allowDamage true; hint "Объект по курсору теперь уязвим"; }; },
				{
					private _target = cursorObject; if !(isNull _target) then 
					{
						private _enabled = simulationEnabled _target;
						_target enableSimulation !_enabled;
						hint parseText format ["Симуляция объекта<br/>%1<br/>теперь %2",typeOf _target,["включена","выключена"] select _enabled];
					} else { hint "Нет объекта по курсору"; }; 
				}
			]
		],

		[
			"Выдать себе зевса",
			"Удалить своего юнита зевса (может помочь если не выдается)",
			[
				{ player remoteExec["AF_curatorAdd",2]; pIsCurator = true; hint "Вы подключили себе ZEUS"; },
				{
					private _UID 			= getPlayerUID player;
					private _curators		= allCurators;
					private _arrID			= _curators findIf { (str _x) isEqualTo _UID };
					if (_arrID > -1) then 
					{
						[_arrID,
						{
							private _arrID 		= _this;
							private _curators	= allCurators;
							private _curator 	= _curators select _arrID;
							private _group 		= group _curator;
							unassignCurator _curator;
							deleteVehicle _curator;
							if (allCurators isEqualTo []) then { deleteGroup _group; };
						}] remoteExec ["spawn", 2];
						hint "Ваш юнит Зевса был найден и удален";
					} else { hint "Не найдено вашего юнита куратора для удаления"; };
				}
			]
		],

		[
			"Настройки текста",
			"Настройки фона",
			"Настройки размера и расположения меню",
			"Загрузить / Сохранить / Сбросить параметры",
			[
				[
					"Цвет текста",
					"Шрифт текста",
					[
						[
							"Черный (по умолчанию)",
							"Красный",
							"Оранжевый",
							"Бордовый",
							"Синий",
							"Голубой",
							"Фиолетовый",
							"Зеленый",
							"Салатовый",
							[
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetTextColor [0,0,0,1]; ME_params set [0,[0,0,0,1]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetTextColor [1,0,0,1]; ME_params set [0,[1,0,0,1]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetTextColor [1,0.5,0,1]; ME_params set [0,[1,0.5,0,1]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetTextColor [0.8,0,0.5,1]; ME_params set [0,[0.8,0,0.5,1]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetTextColor [0,0,1,1]; ME_params set [0,[0,0,1,1]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetTextColor [0,1,1,1]; ME_params set [0,[0,1,1,1]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetTextColor [0.5,0,0.8,1]; ME_params set [0,[0.5,0,0.8,1]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetTextColor [0,0.5,0,1]; ME_params set [0,[0,0.5,0,1]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetTextColor [0,0.9,0,1]; ME_params set [0,[0,0.9,0,1]]; }
							]
						],

						[
							"EtelkaMonospaceProBold (по умолчанию)",
							"EtelkaMonospacePro",
							"EtelkaNarrowMediumPro",
							"TahomaB",
							"LCD14",
							"LucidaConsoleB",
							"PuristaBold",
							"PuristaLight",
							"Еще...",
							[
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "EtelkaMonospaceProBold"; ME_params set [1,"EtelkaMonospaceProBold"]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "EtelkaMonospacePro"; ME_params set [1,"EtelkaMonospacePro"]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "EtelkaNarrowMediumPro"; ME_params set [1,"EtelkaNarrowMediumPro"]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "TahomaB"; ME_params set [1,"TahomaB"]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "LCD14"; ME_params set [1,"LCD14"]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "LucidaConsoleB"; ME_params set [1,"LucidaConsoleB"]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "PuristaBold"; ME_params set [1,"PuristaBold"]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "PuristaLight"; ME_params set [1,"PuristaLight"]; },
								[
									"PuristaMedium",
									"PuristaSemibold",
									"RobotoCondensed",
									"RobotoCondensedBold",
									"RobotoCondensedLight",
									[
										{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "PuristaMedium"; ME_params set [1,"PuristaMedium"]; },
										{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "PuristaSemibold"; ME_params set [1,"PuristaSemibold"]; },
										{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "RobotoCondensed"; ME_params set [1,"RobotoCondensed"]; },
										{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "RobotoCondensedBold"; ME_params set [1,"RobotoCondensedBold"]; },
										{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetFont "RobotoCondensedLight"; ME_params set [1,"RobotoCondensedLight"]; }
									]
								]
							]
						]

					]
				],

				[
					"Цвет фона",
					[
						[
							"Прозрачный (по умолчанию)",
							"Серый",
							"Красный",
							"Оранжевый",
							"Бордовый",
							"Синий",
							"Голубой",
							"Фиолетовый",
							"Зеленый",
							[
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetBackgroundColor [0,0,0,0]; ME_params set [2,[0,0,0,0]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetBackgroundColor [0,0,0,0.3]; ME_params set [2,[0,0,0,0.3]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetBackgroundColor [1,0,0,0.3]; ME_params set [2,[1,0,0,0.3]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetBackgroundColor [1,0.5,0,0.3]; ME_params set [2,[1,0.5,0,0.3]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetBackgroundColor [0.8,0,0.5,0.3]; ME_params set [2,[0.8,0,0.5,0.3]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetBackgroundColor [0,0,1,0.3]; ME_params set [2,[0,0,1,0.3]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetBackgroundColor [0,1,1,0.3]; ME_params set [2,[0,1,1,0.3]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetBackgroundColor [0.5,0,0.8,0.3]; ME_params set [2,[0.5,0,0.8,0.3]]; },
								{ ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001) ctrlSetBackgroundColor [0,0.5,0,0.3]; ME_params set [2,[0,0.5,0,0.3]]; }
							]
						]

					]
				],

				[
					"Размеры границ (рекомендуется включить фон)",
					"Расположение меню",
					[
						[
							"По умолчанию",
							"Нижняя граница - ниже",
							"",
							"Правая граница - левее",
							"",
							"Правая граница - правее",
							"",
							"Нижняя граница - выше",
							[
								{ private _control = ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001); (ME_params select 3) set [2,((call ME_profileParams) select 3) select 2]; (ME_params select 3) set [3,((call ME_profileParams) select 3) select 3]; _control ctrlSetPosition (ME_params select 3); _control ctrlCommit 0; },
								{ private _control = ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001); (ME_params select 3) set [3,((ME_params select 3) select 3) + 0.01]; _control ctrlSetPosition (ME_params select 3); _control ctrlCommit 0; },
								{  },
								{ private _control = ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001); (ME_params select 3) set [2,((ME_params select 3) select 2) - 0.01]; _control ctrlSetPosition (ME_params select 3); _control ctrlCommit 0; },
								{  },
								{ private _control = ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001); (ME_params select 3) set [2,((ME_params select 3) select 2) + 0.01]; _control ctrlSetPosition (ME_params select 3); _control ctrlCommit 0; },
								{  },
								{ private _control = ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001); (ME_params select 3) set [3,((ME_params select 3) select 3) - 0.01]; _control ctrlSetPosition (ME_params select 3); _control ctrlCommit 0; }
							]
						],

						[
							"По умолчанию",
							"Меню - ниже",
							"",
							"Меню - левее",
							"",
							"Меню - правее",
							"",
							"Меню - выше",
							[
								{ private _control = ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001); (ME_params select 3) set [0,((call ME_profileParams) select 3) select 0]; (ME_params select 3) set [1,((call ME_profileParams) select 3) select 1]; _control ctrlSetPosition (ME_params select 3); _control ctrlCommit 0; },
								{ private _control = ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001); (ME_params select 3) set [1,((ME_params select 3) select 1) + 0.01]; _control ctrlSetPosition (ME_params select 3); _control  ctrlCommit 0; },
								{  },
								{ private _control = ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001); (ME_params select 3) set [0,((ME_params select 3) select 0) - 0.01]; _control ctrlSetPosition (ME_params select 3); _control ctrlCommit 0; },
								{  },
								{ private _control = ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001); (ME_params select 3) set [0,((ME_params select 3) select 0) + 0.01]; _control ctrlSetPosition (ME_params select 3); _control ctrlCommit 0; },
								{  },
								{ private _control = ((uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001); (ME_params select 3) set [1,((ME_params select 3) select 1) - 0.01]; _control ctrlSetPosition (ME_params select 3); _control ctrlCommit 0; }
							]
						]

					]
				],

				[
					"Загрузить ранее сохраненные параметры",
					"Сохранить текущие настройки",
					"Сбросить текущие настройки (без сохранения)",
					"!! Удалить !! сохраненные настройки из профиля",
					[
						[
							"Подтвердить загрузку сохраненных параметров",
							[
								{
									private _oldParams = ME_params;
									if ("load" call ME_profileParams) then
									{
										private _control = (uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001;
										_control ctrlSetTextColor (ME_params select 0);
										_control ctrlSetFont (ME_params select 1);
										_control ctrlSetBackgroundColor (ME_params select 2);
										_control ctrlSetPosition (ME_params select 3);
										_control ctrlCommit 0;
										hint "Сохраненные ранее настройки успешно загружены";
									} else {
										ME_params = _oldParams;
										hint parseText "Загрузка сохраненых параметров не удалась<br/>В профиле пользователя не найдено подходящего сохранения";
									};
								}
							]
						],

						[
							"Подтвердить сохранение параметров в профиль",
							[
								{
									if ("save" call ME_profileParams) then
									{
										hint "Настройки успешно сохранены в файле пользователя";
									} else {
										hint parseText "Сохранение параметров в профиль не удалось<br/>Рекомендуется загрузить настройки по умолчанию";
									};
								}
							]
						],

						[
							"Подтвердить сброс настроек по умолчанию",
							[
								{
									ME_params = call ME_profileParams;
									private _control = (uiNameSpace getVariable "menuEngineNavigate") displayCtrl 1001;
									_control ctrlSetTextColor (ME_params select 0);
									_control ctrlSetFont (ME_params select 1);
									_control ctrlSetBackgroundColor (ME_params select 2);
									_control ctrlSetPosition (ME_params select 3);
									_control ctrlCommit 0;
									hint "Настройки меню успешно сброшены до значений по умолчанию";
								}
							]
						],

						[
							"!!! Подтвердить удаление сохранения из профиля !!!",
							[
								{
									profileNamespace setVariable ["ME_kat_params",nil];
									saveProfileNamespace;
									hint "Сохранение настроек меню успешно стёрто из профиля";
								}
							]
						]
					]

				]

			]
		]
	]
];
