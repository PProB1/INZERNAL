#pragma once
#include <core/globals.h>
#include <core/minhook/hook.h>
#include <proton/Variant.h>
#include <string.h>
#include <windows.h>

typedef void(__cdecl* ENetPacketFreeCallback)(struct _ENetPacket*);

typedef struct _ENetPacket {
    size_t reference_count;
    int flags;
    uint8_t* data;
    size_t dataLength;
    ENetPacketFreeCallback freeCallback;
    void* userData;
} ENetPacket;

#define TYPE(x) extern types::x x

namespace hooks {

    namespace orig {
        TYPE(App_GetVersion);
        TYPE(BaseApp_SetFPSLimit);
        TYPE(LogMsg);
        TYPE(NetAvatar_CanMessageT4);
        TYPE(CanPunchOrBuildNow);
        TYPE(ObjectMap_HandlePacket);
        TYPE(SendPacketRaw);
        TYPE(HandleTouch);
        TYPE(WorldCamera_OnUpdate);
        TYPE(UpdateFromNetAvatar);
        TYPE(SendPacket);
        TYPE(EndScene);
        TYPE(ProcessTankUpdatePacket);
        TYPE(CanSeeGhosts);
        TYPE(NetAvatar_Gravity);

        extern WNDPROC wndproc;
    } // namespace orig

    void init();
    void destroy();

    // clang-format off

	float	__cdecl		App_GetVersion(App* app);
	void	__cdecl		BaseApp_SetFPSLimit(BaseApp* ba, float fps);
	int		__cdecl		LogMsg(const char* msg, ...);
	bool	__cdecl		NetAvatar_CanMessageT4(NetAvatar* player);
	bool	__cdecl		CanPunchOrBuildNow(AvatarRenderData* render_data);
	bool	__cdecl		ObjectMap_HandlePacket(WorldObjectMap* map, GameUpdatePacket* packet);
	void	__cdecl		SendPacketRaw(int type, GameUpdatePacket* packet, int size, void* packetsender, EnetPeer* peer, int flag);
	void	__cdecl		HandleTouch(LevelTouchComponent* touch, CL_Vec2f pos, bool started);
    void    __cdecl     WorldCamera_OnUpdate(WorldCamera* camera, CL_Vec2f unk, CL_Vec2f unk2);
    void    __cdecl     UpdateFromNetAvatar(AvatarRenderData* render_data, NetAvatar* player);
    void    __cdecl     SendPacket(int type, const std::string& packet, EnetPeer* peer);
    void    __cdecl     ProcessTankUpdatePacket(GameLogic* logic, GameUpdatePacket* packet);
    bool    __cdecl     CanSeeGhosts(int id);
    void    __cdecl     NetAvatar_Gravity(NetAvatar* player);
    long    __stdcall   EndScene(IDirect3DDevice9* device);


    LRESULT __stdcall   WndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);


    // clang-format on

} // namespace hooks