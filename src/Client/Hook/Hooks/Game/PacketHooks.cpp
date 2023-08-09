#include <iostream>
#include "PacketHooks.hpp"
#include "../../../../SDK/SDK.hpp"
#include "../../../../SDK/Client/Network/Packet/TextPacket.hpp"

void SendPacketHook::callback(LoopbackPacketSender* pSender, Packet* pPacket) {

	/*if (SDK::clientInstance != nullptr) {
		if (SDK::clientInstance->getLocalPlayer() != nullptr) {

			auto player = SDK::clientInstance->getLocalPlayer();
			std::string xuid = *player->getXuid(&xuid);

			if (!player->isAlive()) {
				
				

				std::shared_ptr<Packet> packet = SDK::createPacket(9);

				TextPacket* tpacket = reinterpret_cast<TextPacket*>(packet.get());

				tpacket->type = TextPacketType::CHAT;
				tpacket->author = player->playerName;
				tpacket->message = "GG";
				tpacket->platformId = "";
				tpacket->translationNeeded = false;
				tpacket->xuid = xuid;

				sendPacketkOriginal(pSender, tpacket);

			}
		}
	}
	*/


	sendPacketkOriginal(pSender, pPacket);
}

void SendPacketHook::receiveCallback(const float* a1, const float* networkIdentifier, const float* netEventCallback, std::shared_ptr<Packet> packet) {

    std::string amongus;
    std::cout <<  *packet->getName(&amongus) << std::endl;

    return receivePacketkOriginal(a1, networkIdentifier, netEventCallback, packet);
}

void SendPacketHook::enableHook() {

    std::shared_ptr<Packet> packet = SDK::createPacket((int)MinecraftPacketIds::Text);
    Memory::hookFunc((void*) packet->packetHandler->vTable[1], receiveCallback, (void**)&receivePacketkOriginal, "ReceivePacketHook");
	this->autoHook(callback, (void**)&sendPacketkOriginal);
}