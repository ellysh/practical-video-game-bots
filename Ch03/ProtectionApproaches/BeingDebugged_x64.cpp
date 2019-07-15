#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <winternl.h>

static const uint16_t MAX_LIFE = 20;
static uint16_t gLife = MAX_LIFE;

#define CheckDebug() \
{ \
PTEB pTeb = reinterpret_cast<PTEB>(__readgsqword(0x30)); \
PPEB pPeb = pTeb->ProcessEnvironmentBlock; \
if (pPeb->BeingDebugged) \
{ \
printf("debugger detected!\n"); \
exit(EXIT_FAILURE); \
} \
}

int main()
{
	SHORT result = 0;

	while (gLife > 0)
	{
		CheckDebug();

		result = GetAsyncKeyState(0x31);
		if (result != 0xFFFF8001)
			--gLife;
		else
			++gLife;

		printf("life = %u\n", gLife);
		Sleep(1000);
	}

	printf("stop\n");

	return 0;
}
