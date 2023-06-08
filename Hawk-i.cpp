#include <iostream>

#include <thread>
#include "memory.h"
#include "offsets.h"

int main()
{
	const auto mem = Memory{"csgo.exe"};
	const auto client_dll = mem.GetModuleAddress("client.dll");


	while (true)
	{
		uintptr_t local_player = mem.Read<uintptr_t>(client_dll + offsets::dwLocalPlayer);
		int32_t currentTeam = mem.Read<int32_t>(local_player + offsets::m_iTeamNum);

		for (int i = 0; i < 64; i++)
		{
			uintptr_t entity = mem.Read< uintptr_t>(client_dll + offsets::dwEntityList + i * 0x10);
			int32_t enemyTeam = mem.Read<int32_t>(entity + offsets::m_iTeamNum);

			if (enemyTeam == currentTeam)
				continue;
			mem.Write<bool>(entity + offsets::m_bSpotted, true);

		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));

		std::cout << "Running \n";
	}
	return 0;
}