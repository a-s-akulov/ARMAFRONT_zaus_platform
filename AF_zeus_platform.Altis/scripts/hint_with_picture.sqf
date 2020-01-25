private _str = localize (_this select 1);
if (_str isEqualTo "") then { _str = _this select 1; };

hint parseText format["<br/><img size='3' color='#595923' align='center' image='%1' /><br/><br/>
			<t size='1.2' color='#99ffffff' >%2</t><br/><br/>",_this select 0,_str];