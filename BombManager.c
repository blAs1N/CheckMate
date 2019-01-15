#include "BombManager.h"

void InstallBomb(POINT bombPos) {
	bombMap[bombPos.y][bombPos.x] = '1';

	POINT* installPos = (POINT*)malloc(sizeof(POINT));
	installPos->x = bombPos.x;
	installPos->y = bombPos.y;

	HANDLE bombThread = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)BurstBomb, (LPVOID)installPos, 0, NULL);
	CloseHandle(bombThread);
}

void WINAPI BurstBomb(LPVOID installPos) {
	POINT bombPos = *((POINT*)installPos);
	char oldObject[3][3];
	memset(oldObject, '0', sizeof(oldObject));

	SAFE_FREE(installPos);
	
	Sleep(1500);

	// ��ź�� �����ϰ� ��ź�� ���� ��ġ�� �ִ� ��ü�� ����Ѵ�.
	for (int y = bombPos.y - 1; y <= bombPos.y + 1; y++) {
		for (int x = bombPos.x - 1; x <= bombPos.x + 1; x++) {
			if (x == bombPos.x && y == bombPos.y) continue;

			if (bombMap[y][x] != '2')
				oldObject[y - bombPos.y + 1][x - bombPos.x + 1] = bombMap[y][x];
		}
	}

	// 300�� ���� ������ �����ߴٰ� ������ �������.
	for (DWORD startTime = timeGetTime(); 350 > timeGetTime() - startTime; ) {
		for (int y = bombPos.y - 1; y <= bombPos.y + 1; y++) {
			for (int x = bombPos.x - 1; x <= bombPos.x + 1; x++) {
				if (cellMap[y][x] != '1')
					bombMap[y][x] = '2';
			}
		}
	}

	// ��ü�� �ǵ�����.
	for (int y = bombPos.y - 1; y <= bombPos.y + 1; y++) {
		for (int x = bombPos.x - 1; x <= bombPos.x + 1; x++)
			bombMap[y][x] = oldObject[y - bombPos.y + 1][x - bombPos.x + 1];
	}
}