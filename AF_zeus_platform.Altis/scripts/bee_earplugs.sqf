/*
Скрипт берушей
Данный скрипт создан для сервера ArmaFront

Автор: Пчёлка=Ъ
Версия: 1.0.0

Модифицировал: 
Если вы будете вносить глобальные изменения, по желанию сможете указать своё участие тут,
хотя где тут можно сделать что то глобальное? =)

Установка:
------------------------------
в initPlayerLocal.sqf

execVM "scripts\bee_earplugs.sqf";

------------------------------
в stringtable.xml
<Package name="Bee_EarplugsScript">
	<Key ID="Ear_On">
		<Original>Ear On</Original>
		<English>Ear On</English>
		<Russian>Беруши одеты</Russian>
	</Key>
	<Key ID="Ear_Off">
		<Original>Ear Off</Original>
		<English>Ear Off</English>
		<Russian>Беруши сняты</Russian>
	</Key>
</package>

------------------------------
в description.ext

	class BeeBlip
	{
		name = "BeeBlip";
		sound[] = {"@a3\sounds_f\sfx\blip1", 1.0, 1.0};
		titles[] = {0,""};
	};
ВНИМАНИЕ!!!!! Если у вас уже есть мой скрипт по ремонту техники то данный звук добавлять ненужно, т.к. он универсален для этих скриптов	
*/ 
/////////////////// НАЧАЛО ///////////////////
 // переменная отвечающая за одевание/снятие берушей

if(earplugs) then // если беруши одеты, данная функция их снимет
{
	0.1 fadeSound 1;// стандартная громкость
	earplugs = False; // переключение флага переменной на "сняты"
	hint parseText format ["<br/><img size='4' color='#595923' image='a3\ui_f\data\gui\cfg\Hints\callsupport_ca.paa' align='center'/><br/>
	<br/><t size='1.2' color='#99ffffff' align='center'>%1</t><br/><br/>",localize "Ear_Off"]; // хинт с картинкой и текстом из стрингтейбл
	//playSound "BeeBlip";	// воспроизводит звук
} else // если беруши сняты, данная функция их оденет
{
	0.1 fadeSound 0.2; // приглушение звуков на %
	earplugs = True; // переключение флага переменной на "одеты"
	hint parseText format ["<br/><img size='4' color='#595923' image='a3\ui_f\data\gui\cfg\Hints\callsupport_ca.paa' align='center'/><br/>
	<br/><t size='1.2' color='#99ffffff' align='center'>%1</t><br/><br/>",localize "Ear_On"]; // хинт с картинкой и текстом из стрингтейбл
	//playSound "BeeBlip";	// воспроизводит звук
};