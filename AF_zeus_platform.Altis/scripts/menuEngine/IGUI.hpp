class menuEngineNavigate {
    idd = 0905201901;
    movingEnable =  0;
    enableSimulation = 1;
    enableDisplay = 1;
    duration     =  10e10;
    fadein       =  0;
    fadeout      =  0;
    name = "menuEngineNavigate";
    onLoad = "with uiNameSpace do { menuEngineNavigate = _this select 0 }";
	class controls {
	    class structuredText {
            access = 0;
            type = 13;
            idc = 1001;
            onLoad = "[] spawn ME_dataUpdate;";
            style = 0x00;
            lineSpacing = 1;
			x = 0.01 * safezoneW + safezoneX;
			y = 0.23 * safezoneH + safezoneY;//0.757996
			w = 0.3 * safezoneW;
			h = 0.4 * safezoneH;
            size = 0.05;//0.020
            colorBackground[] = {0,0,0,0};
            colorText[] = {0,0,0,1};//{1,1,1,1}
            text = "Глав. меню >> ";
            font = "EtelkaMonospaceProBold";
			class Attributes {
				font = "EtelkaMonospaceProBold";
				color = "#000000";//"#FFFFFF";
				align = "LEFT";
				valign = "top";
				shadow = true;
				shadowColor = "#000000";
				underline = false;
				size = "0.75";//4
			};
        };
	};
};