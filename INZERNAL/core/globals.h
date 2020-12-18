#pragma once
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shlwapi.lib")
#include <enet/include/enet.h>

#include <d3d9.h>
#include <proton/Variant.h>
#include <proton/clanlib/vec2.h>
#include <proton/NetHTTP.h>
#include <stdio.h>
#include <atomic>
#include <core/json.hpp>
#include <map>
#include <string>

// clang-format off


//from private internal, dont remember what I needed these for so I just brought them over for now
template<typename t> inline constexpr t operator&(t x, t y) { return static_cast<t> (static_cast<int>(x) & static_cast<int>(y)); }
template<typename t> inline constexpr t operator|(t x, t y) { return static_cast<t> (static_cast<int>(x) | static_cast<int>(y)); }
template<typename t> inline constexpr t operator^(t x, t y) { return static_cast<t> (static_cast<int>(x) ^ static_cast<int>(y)); }
template<typename t> inline constexpr t operator~(t x) { return static_cast<t>(~static_cast<int>(x)); }
template<typename t> inline t& operator&=(t& x, t y) { x = x & y;	return x; }
template<typename t> inline t& operator|=(t& x, t y) { x = x | y;	return x; }
template<typename t> inline t& operator^=(t& x, t y) { x = x ^ y;	return x; }

class BaseApp {public:};
class GameUpdatePacket;
class App : BaseApp {public:};
class AvatarRenderData;
class WorldObjectMap;
class NetAvatar;
class LevelTouchComponent;
class WorldCamera;
class variantlist_t;
class GameLogic;

namespace types {
	//hooks
	using	App_GetVersion				= float(__cdecl*)(App*);
	using	BaseApp_SetFPSLimit			= void(__cdecl*)(BaseApp*, float);
	using	LogMsg						= int(__cdecl*)(const char*, ...);
	using	NetAvatar_CanMessageT4		= bool(__cdecl*)(NetAvatar*);
	using	CanPunchOrBuildNow			= bool(__cdecl*)(AvatarRenderData*);
	using	ObjectMap_HandlePacket		= bool(__cdecl*)(WorldObjectMap*, GameUpdatePacket*);
	using	SendPacketRaw				= void(__cdecl*)(int, GameUpdatePacket*, int, void*, ENetPeer*, int);
	using	SendPacket					= void(__cdecl*)(int, const std::string&, ENetPeer*);
	using	HandleTouch					= void(__cdecl*)(LevelTouchComponent*, CL_Vec2f, bool);
	using	WorldCamera_OnUpdate		= void(__cdecl*)(WorldCamera*, CL_Vec2f, CL_Vec2f);
	using	UpdateFromNetAvatar			= void(__cdecl*)(AvatarRenderData*, NetAvatar*);
	using	EndScene					= long(__stdcall*)(IDirect3DDevice9*);
	using	ProcessTankUpdatePacket		= void(__cdecl*)(GameLogic*, GameUpdatePacket*);
	using	CanSeeGhosts				= bool(__cdecl*)(int);
	using	NetAvatar_Gravity			= void(__cdecl*)(NetAvatar*);
	using	NetHTTP_Update				= void(__cdecl*)(NetHTTP*);
	using	ProcessAcceleration			= void(__cdecl*)(NetAvatar*, float);

	//other functions, not hooked
	using	WorldToScreen				= void(__cdecl*)(WorldCamera*, CL_Vec2f&, CL_Vec2f&);
	using	OnDataConfig				= void(__cdecl*)(NetAvatar*, variantlist_t*);
	using	GetLocalPlayer				= NetAvatar*(__cdecl*)(GameLogic*);
}

enum WinSpoof {
	wsOff = 0,		//will not try to spoof anything
	wsRandom = 1,	//will set random values to zf and fz as usual
	wsMimic = 2		//will set unmodified newest growtopia.exe values to avoid fake win-ver tracking. needs manual updating
};
enum FlagMode {
	fmKeep = 0,		//keep your flag
	fmRandom = 1,	//pick random flag from gt folder
	fmCustom = 2,	//use custom flag
};
//from private internal, might be used later on, so bringing it for now
namespace col {
	struct im {
		float red;
		float green;
		float blue;
		float alpha;
	};

	//GT argb
#define RGBA(r,g,b,a)(((unsigned char)(a)) +  ((unsigned char)(r) << 8) + ((unsigned char)(g) << 16) + ((unsigned char)(b) << 24))

	int im_to_gt(im& c);
	im gt_to_im(int gt);
}

namespace logging {

		enum { 
			 sendpacket = (1 << 0), //the text of the packet
			 sendpacketraw = (1 << 1), //just the type, not the full info
			 processtank = (1 << 2), //just the type, not the full info
			 callfunction = (1 << 3), //processtankupdatepacket CALL_FUNCTION serializes as variantlist
			 logmsg	= (1 << 4), //LogMsg function
		 };

		extern bool	enabled;
		extern int console;
		extern int max_count;
		extern int menu;	
}

namespace opt {
	
	extern bool			bypass_dat;

	extern float		gt_version;
	extern float		fps_limit;
	extern bool			tp_click;
	extern bool			mod_zoom;
	extern bool			see_ghosts;
	extern bool			spoof_login;
	extern bool			spoof_name;
	extern WinSpoof		spoof_win;
	extern FlagMode		flag_mode;
	extern std::string	flag;
	extern bool			alt_server;

	extern bool			custom_server_on;
	extern std::string	custom_server_val;

	namespace cheat {
		extern bool		punch_cooldown_on;
		extern float	punch_cooldown_val;
		extern bool		dev_zoom;
		extern bool		gravity_on;
		extern float	gravity_val;
		extern bool		block_sendpacketraw;
		extern bool		antighost;
		extern bool		movespeed_on;
		extern bool		movespeed_start;
		extern bool		movespeed_stop;
		extern float	movespeed_val;
	}
	
}

namespace global {
	extern HMODULE		self;
	extern App*			app;
	extern bool			unload;
	extern HWND			hwnd;
	extern void*		gt;
	extern bool			load;
	extern bool			draw;
	extern std::string	version;
	//	extern nlohmann::json m_cfg;
}

// clang-format on