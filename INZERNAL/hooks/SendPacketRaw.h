#pragma once
#include <core/globals.h>
#include <sdk/sdk.h>
#include <string>

class SendPacketRawHook {
   public:
    static void Execute(types::SendPacketRaw orig, int type, GameUpdatePacket* packet, int size, void* packetsender, EnetPeer* peer, int flag) {
        if (opt::cheat::block_sendpacketraw)
            return;

        printf("sending raw packet with type %d\n", packet->type);

        if (packet->type == PACKET_APP_INTEGRITY_FAIL)
            return;

        if (packet->type == 0 && packet->flags & 4) {
            auto player = sdk::GetGameLogic()->GetLocalPlayer();
            if (player)
                player->SetModStatus(opt::mod_zoom, opt::cheat::dev_zoom);
        }

        if (packet->velocity_x == 1000.f || packet->type == PACKET_PING_REPLY || packet->type == PACKET_PING_REQUEST) {
            utils::printc("95", "[ping check] sending emulated response so we dont get dc or ban");
            GameUpdatePacket pk{ 0 };
            pk.type = PACKET_PING_REPLY;
            pk.item = packet->item; // tick count (speedhack)
            pk.pos_x = 64.f;        // punch range in pixels
            pk.pos_y = 64.f;        // build range in pixels
            pk.velocity_x = 1000.f; //gravity
            pk.velocity_y = 250.f;  // movement speed

            void* PacketSender = nullptr;
            orig(NET_MESSAGE_GAME_PACKET, &pk, 56, PacketSender, sdk::GetPeer(), flag);
            return;
        }

        orig(type, packet, size, packetsender, peer, flag);
    }
};