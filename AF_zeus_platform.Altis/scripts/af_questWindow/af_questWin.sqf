/* 
[ nextCode, cancelCode, headline, question, buttonsText, crossSettings ] spawn AF_question;

- nextCode 									- STRING ' nextCode '. 					Исполняется при нажатии ПРАВОЙ КНОПКИ.
- cancelCode 	(optional, default - '')	- STRING ' cancelCode '. 				Исполняется при нажатии ЛЕВОЙ КНОПКИ.					(По умолчанию - закрывает диалог)
- headline		(optional, default - '')	- STRING 'headline'.					Текст, отображаемый в загаловке.						(По умолчанию - 'Подтверждение')

- question		(optional, default - '')	- STRING 'question'.					Текст, отображаемый в основном окне.					(По умолчанию - 
																																			'Уверены, что хотите сделать это?')

- buttonsText 	(optional, default - [])	- ARRAY ['nextText','cancelText'].		Отображаемый текст в кнопках :


													- nextText 		(optional, default - '') 			- STRING 'nextText'. 	То, что будет написано на ПРАВОЙ КНОПКЕ
																																			(По умолчанию - 'Да')

													- cancelText 	(optional, default - '') 			- STRING 'cancelText'. 	То, что будет написано на ЛЕВОЙ КНОПКЕ
																																			(По умолчанию - 'Нет')



- crossSettings (optional, default - [])	- ARRAY [cross,crossCancel].			Настройки функций красного креста :


													- cross			(optional, default - TRUE)			- BOOLEAN cross.		Присутствует ли красный крест в правом углу
																																			(По умолчанию - Присутствует)

													- crossCancel	(optional, default - FALSE)			- BOOLEAN crossCancel.	Будет ли крест выполнять действие,
																																	привязанное к ЛЕВОЙ КНОПКЕ, которое
																																	указывается в cancelCode.
																																			(По умолчанию - Нет, будет 
																																				лишь закрывать диалог)


Пример вызова: [ " hint 'hellow!' " ] spawn AF_question; - если нажать ПРАВУЮ КНОПКУ, то сработает hint с текстом 'hellow!'

Пример вызова со всеми параметрами "по умолчанию": 			[ "closeDialog 0;","","","",[],[]] spawn AF_question;
																				ИЛИ
															[ "closeDialog 0;","","","",["",""],[true,false]] spawn AF_question;
*/

private _countThis			= count _this;
private _nextCode			= _this select 0;

private	_cancelCode			= if (_countThis > 1) then { (_this select 1) } else { '' };
private _headline			= if (_countThis > 2) then { (_this select 2) } else { '' };
private _question			= if (_countThis > 3) then { (_this select 3) } else { '' };

private _buttonsText		= if (_countThis > 4) then { (_this select 4) } else { [] };
	private _nextText			= if ((count _buttonsText) > 0) then { (_buttonsText select 0) } else { '' };
	private _cancelText			= if ((count _buttonsText) > 1) then { (_buttonsText select 1) } else { '' };

private _crossSettings		= if (_countThis > 5) then { (_this select 5) } else { [] };
	private _cross				= if ((count _crossSettings) > 0) then { (_crossSettings select 0) } else { true };
	private _crossCancel		= if ((count _crossSettings) > 1) then { (_crossSettings select 1) } else { false };


disableSerialization;
createDialog "Question_Window";
private _display			= findDisplay 777200;
private _block 				= _display displayAddEventHandler ["KeyDown", "true"];

buttonSetAction [777220,_nextCode];

if !(_cancelCode isEqualTo '') 		then { buttonSetAction [777221,_cancelCode]; } else { buttonSetAction [777221,'closeDialog 0;']; };

if !(_headline isEqualTo '') 		then { (_display displayCtrl 777210) ctrlSetStructuredText parseText _headline; } else 
												{ (_display displayCtrl 777210) ctrlSetStructuredText parseText localize 'QuestHeadline'; };

if !(_question isEqualTo '') 		then { (_display displayCtrl 777211) ctrlSetStructuredText parseText _question; } else 
												{ (_display displayCtrl 777211) ctrlSetStructuredText parseText localize 'QuestQuestion'; };

if !(_buttonsText isEqualTo [])		then
{
	if !(_nextText isEqualTo '') 		then { ctrlSetText [777220,_nextText]; 		} else { ctrlSetText [777220,localize 'QuestNextBtn']; };
	if !(_cancelText isEqualTo '') 		then { ctrlSetText [777221,_cancelText]; 	} else { ctrlSetText [777221,localize 'QuestCancelBtn']; };
} else
{
	ctrlSetText [777220,localize 'QuestNextBtn'];
	ctrlSetText [777221,localize 'QuestCancelBtn'];
};

if !(_cross) then
{
	ctrlEnable [777223,_cross];
	ctrlSetText [777223,''];
};
if (_crossCancel) 					then { buttonSetAction [777223,buttonAction 777221]; } else { buttonSetAction [777223,'closeDialog 0;']; };

waitUntil { !dialog };

_display displayRemoveEventHandler ["KeyDown", _block];