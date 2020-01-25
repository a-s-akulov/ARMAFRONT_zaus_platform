class Question_Window
{
	idd = 777200;
	movingEnable = false;
	onLoad = "hintSilent """"";
	class controls
	{
		class main_background: IGUIBack
		{
            idc = -1;
			x = 0.25 * safezoneW + safezoneX;
			y = 0.375 * safezoneH + safezoneY;
			w = 0.5 * safezoneW;
			h = 0.225 * safezoneH;
			colorBackground[] = {0,0,0,0.5};
		};
		class main_frame: RscFrame
		{
			idc = -1;
			x = 0.25 * safezoneW + safezoneX;
			y = 0.375 * safezoneH + safezoneY;
			w = 0.5 * safezoneW;
			h = 0.225 * safezoneH;
		};
        class questHeadline: RscStructuredText
		{
			idc = 777210;
			x = 0.25 * safezoneW + safezoneX;
			y = 0.375 * safezoneH + safezoneY;
			w = 0.475 * safezoneW;
			h = 0.025 * safezoneH;
			text = "Подтверждение";
		};
        class questMainText: RscStructuredText
		{
			idc = 777211;
			x = 0.25 * safezoneW + safezoneX;
			y = 0.4 * safezoneH + safezoneY;
			w = 0.5 * safezoneW;
			h = 0.15 * safezoneH;
			text = "Уверены, что хотите сделать это?";
		};
		class second_frame: RscFrame
		{
			idc = -1;
			x = 0.25 * safezoneW + safezoneX;
			y = 0.4 * safezoneH + safezoneY;
			w = 0.5 * safezoneW;
			h = 0.15 * safezoneH;
		};
        class questNextButton: RscButton
		{
			idc = 777220;
			x = 0.61 * safezoneW + safezoneX;
			y = 0.56 * safezoneH + safezoneY;
			w = 0.13 * safezoneW;
			h = 0.03 * safezoneH;
			text = "Да";
			colorBackground[] = {0,0,0,0.7};
			colorText[] = {0.82,0.82,0.82,1};
			onButtonClick = "";
			colorBackgroundActive[] = {0,0,0,1};
			colorFocused[] = {0,0,0,0.8};
		};
        class questCancelButton: RscButton
		{
			idc = 777221;
			x = 0.26 * safezoneW + safezoneX;
			y = 0.56 * safezoneH + safezoneY;
			w = 0.13 * safezoneW;
			h = 0.03 * safezoneH;
			text = "Нет";
			colorBackground[] = {0,0,0,0.7};
			colorText[] = {0.82,0.82,0.82,1};
			onButtonClick = "";
			colorBackgroundActive[] = {0,0,0,1};
			colorFocused[] = {0,0,0,0.8};
		};
		class questRedCancBut: RscButton
		{
			idc = 777223;
			x = 0.725 * safezoneW + safezoneX;
			y = 0.375 * safezoneH + safezoneY;
			w = 0.025 * safezoneW;
			h = 0.025 * safezoneH;
			text = "X";
			colorBackground[] = {0.6,0,0,1};
			colorBackgroundDisabled[] = {0,0,0,0.5};
			colorText[] = {0.82,0.82,0.82,1};
			onButtonClick = "";
			colorBackgroundActive[] = {0.9,0,0,1};
			colorFocused[] = {0.6,0,0,1};
		};
	};
};