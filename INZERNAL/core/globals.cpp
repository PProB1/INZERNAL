#pragma once
#include "globals.h"

// clang-format off


//logging options
namespace logging {
		bool	enabled		= true; //master switch for all logging
	
		//logging in console
		int		console		=	sendpacketraw | processtank | callfunction;

		//logging in menu
		int		max_count	=	500;  //max events in menu, for performance concerns.
		int		menu		=	sendpacket | sendpacketraw | processtank | callfunction;
}

//options
namespace opt {

	//enhanchements 
	float		fps_limit	=	144.0f;		//fps limit gets forced to this
	float		gt_version	=	3.50f;		//gt version gets spoofed to this
	bool		tp_click	=	true;		//when on, holding CTRL allows you to tp to mouse location.
	bool		mod_zoom	=	true;		//unlimited zoom. Cant ban you. cant punch further, only view. NOTE: If for some reason you can punch further, re-join.
	bool		see_ghosts	=	true;		//allows you to see ghosts so you can avoid constant slime
	bool		spoof_login	=	true;		//whether or not to spoof mac, hash2, wk, rid, etc on login. GT version spoofed even when off.
	bool		spoof_name	=	true;		//Also set the requestedName field to random. Might be unwanted for non grow-id accounts.
	WinSpoof	spoof_win	=	::wsMimic;	//Mode of zf/fz spoofing mode. See the WinSpoof enum for more details.
	FlagMode	flag_mode	=	::fmRandom; //See FlagMode enum for details.
	std::string	flag		=	"us";		//set if flag_mode is set to fmCustom
	bool		alt_server	=	true;		//always use alternative server for login, because growtopia1 (main logon server) has issues with freezing.

	bool		custom_server_on	=	false;	//when on it uses 
	std::string	custom_server_val	=	"growtopia2.com"; //you can put your private server ip etc there if you want to

	//cheats
	namespace cheat {
		bool	punch_cooldown_on	=	true;		//toggle: custom punch/place cooldown
		float	punch_cooldown_val	=	0.15f;		//punch/place cooldown timer. i.e fast punch & place
		bool	dev_zoom			=	false;		//unlimited zoom + unlimited build/punch. The latter can ban, use at your own caution.
		bool	gravity_on			=	false;		//toggle: use custom gravity
		float	gravity_val			=	1000.0f;	//the gravity, 1000 is normal
		bool	block_sendpacketraw	=	false;		//blocks any and all sendpacketraw requests. Acts as full ghost. You can safely explore worlds with this on.
		bool	antighost			=	true;		//ignores ghost effects. doesnt ban, but people can see that you are not affected from ur speed.
		bool	movespeed_on		=	false;		//movement speedhack. shouldnt ban.
		bool	movespeed_start		=	true;		//instant acceleration/start of movement
		bool	movespeed_stop		=	true;		//instant deceleration/stop of movement
		float	movespeed_val		=	250.f;		//actual speed that you will have
	}
	
}

//other variables
namespace global {
	HMODULE		self	=	NULL;		//pointer to the dll module
	HWND		hwnd	=	NULL;		//pointer to hwnd of Growtopia window
	App*		app		=	nullptr;	//pointer to App instance
	bool		unload	=	false;		//proces terminates when set to true
	void*		gt		=	nullptr;	//pointer to growtopia base address
	bool		load	=	false;		//menu/imgui initialization status
	bool		draw	=	false;		//menu draw status. set to true for menu to show up when you inject
	std::string	version	=	"V0.5";		//INZERNAL version
}

// clang-format on

//unused for now, from private internal, might use later.
namespace col {
    int col::im_to_gt(im& c) {
        auto a = uint8_t(c.alpha * 255);
        auto r = uint8_t(c.red * 255);
        auto g = uint8_t(c.green * 255);
        auto b = uint8_t(c.blue * 255);
        return RGBA(r, g, b, a);
    }
    im gt_to_im(int gt) {
        return { (float)HIBYTE(LOWORD(gt)) / 255.f, (float)LOBYTE(HIWORD(gt)) / 255.f, (float)HIBYTE(HIWORD(gt)) / 255.f, (float)LOBYTE(LOWORD(gt)) / 255.f };
    }
} // namespace col