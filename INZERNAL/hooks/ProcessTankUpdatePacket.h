#pragma once
#include <core/globals.h>
#include <core/gt.h>
#include <sdk/sdk.h>
#include <string>

class ProcessTankUpdatePacketHook {
   public:
    static void Execute(types::ProcessTankUpdatePacket orig, GameLogic* logic, GameUpdatePacket* packet) {
        if (logging::enabled) {
            if (logging::console & logging::processtank)
                printf("got raw packet: %d [%s]\n", packet->type, gt::get_type_string(packet->type).c_str());
        }

        auto local = sdk::GetGameLogic()->GetLocalPlayer();
        switch (packet->type) {
            case PACKET_CALL_FUNCTION: {
                if (logging::enabled && logging::console & logging::callfunction) {
                    variantlist_t varlist{};
                    if (varlist.serialize_from_mem(utils::get_extended(packet))) {
                        auto content = varlist.print();
                        printf("%s\n", content.c_str());
                    }
                }
            } break;

            case PACKET_SET_CHARACTER_STATE: {
                if (!local)
                    break;
                if (opt::cheat::antighost && packet->netid == local->netid) {
                    if (packet->gravity_out > 1150.0f && packet->speed_out < 150.0f)
                        return;
                }
            } break;
        }

        orig(logic, packet);
    }
};