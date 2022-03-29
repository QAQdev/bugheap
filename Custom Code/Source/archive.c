#include "univLib.h"
#include "archive.h"

extern const char* COLOR[16];
extern const char* SnooCOLOR[8];

extern char* intro[20];
extern int lines;
extern int helpChoice;

void saveBilliardInfo(struct billiard* head) {
	FILE* fp;
	struct billiard* p;
	struct copy* op;

	fp = fopen("..\\Data\\billiard.txt", "wb");

	if (fp == NULL) return -1;

	for (p = head; p != NULL; p = p->next) {
		op = (struct copy*)malloc(sizeof(struct copy));
		op->id = p->id;
		op->x = p->x;
		op->y = p->y;
		op->pre_x = p->pre_x; 
		op->pre_y = p->pre_y;
		op->pre_vx = p->pre_vx; 
		op->pre_vy = p->pre_vy;
		op->vx = p->vx; 
		op->vy = p->vy;
		op->col_t = p->col_t;
		op->rem_t = p->rem_t;
		op->shadow[0] = p->shadow[0];
		op->shadow[1] = p->shadow[1];
		op->ifInPoc = p->ifInPoc;
		op->knPosVer = p->knPosVer;
		op->knPosHor = p->knPosHor;

		fwrite(op, sizeof(struct copy), 1, fp);
	}

	fclose(fp);
}

void savePlayerInfo(struct player* P1, struct player* P2) {
	FILE* fp1, * fp2;

	fp1 = fopen("..\\Data\\player1.txt", "wb");
	fp2 = fopen("..\\Data\\player2.txt", "wb");

	if (fp1 == NULL || fp2 == NULL) return -1;

	fwrite(P1, sizeof(struct player), 1, fp1);
	fwrite(P2, sizeof(struct player), 1, fp2);

	fclose(fp1);
	fclose(fp2);
}

struct billiard* readBilliardInfo(int GameMode) {
	FILE* fp;
	struct billiard* p;
	struct billiard* head = NULL, * tail = NULL;
	struct copy* op;
	fp = fopen("..\\Data\\billiard.txt", "rb");
	if (fp == NULL) return -1;

	int n;
	switch (GameMode) {
	case 0:
		n = 16;
		break;
	case 1:
		n = 10;
		break;
	case 2:
		n = 22;
		break;
	}

	for (int i = 0; i < n; i++) {
		p = (struct billiard*)malloc(sizeof(struct billiard));
		op = (struct copy*)malloc(sizeof(struct copy));
		fread(op, sizeof(struct copy), 1, fp);

		p->id = op->id;
		p->x = op->x; 
		p->y = op->y;
		p->pre_x = op->pre_x; 
		p->pre_y = op->pre_y;
		p->pre_vx = op->pre_vx; 
		p->pre_vy = op->pre_vy;
		p->vx = op->vx; 
		p->vy = op->vy;
		p->col_t = op->col_t;
		p->rem_t = op->rem_t;
		p->shadow[0] = op->shadow[0];
		p->shadow[1] = op->shadow[1];
		p->ifInPoc = op->ifInPoc;
		p->knPosVer = op->knPosVer;
		p->knPosHor = op->knPosHor;
		if (GameMode == 0 || GameMode == 1) p->color = COLOR[i];
		else {
			if (i <= 6) p->color = SnooCOLOR[i];
			else p->color = SnooCOLOR[7];
		}

		if (head == NULL) head = p;
		else tail->next = p;
		tail = p;
		p->next = NULL;
	}

	fclose(fp);

	return head;
}

void readPlayerInfo(struct player* P1, struct player* P2) {
	FILE* fp1, * fp2;

	fp1 = fopen("..\\Data\\player1.txt", "rb");
	fp2 = fopen("..\\Data\\player2.txt", "rb");

	if (fp1 == NULL || fp2 == NULL) return -1;

	fread(P1, sizeof(struct player), 1, fp1);
	fread(P2, sizeof(struct player), 1, fp2);

	fclose(fp1);
	fclose(fp2);
}

void saveMode() {
	FILE* fp;

	fp = fopen("..\\Data\\gamemode.txt", "w");

	if (fp == NULL) return -1;

	fprintf(fp, "%d", GameMode);

	fclose(fp);

}

void readMode() {
	FILE* fp;
	int bufnum;

	fp = fopen("..\\Data\\gamemode.txt", "r");
	if (fp == NULL) {
		return -1;
	}
	fscanf(fp, "%d", &bufnum);

	if (bufnum == 0 || bufnum == 1 || bufnum == 2) {
		GameMode = bufnum;
		//fscanf(fp, "%d", &GameMode);
	}
	else GameMode = -1;

	fclose(fp);
}

void readIntro() {
	FILE* fp;
	static int mallocOnce = 0;
	int i = 0;

	if (mallocOnce == 0) {
		for (int i = 0; i < 20; i++) {
			intro[i] = (char*)malloc(200 * sizeof(char));
		}
		mallocOnce++;
	}

	switch (helpChoice) {
	case 0:
		fp = fopen("..\\Data\\POOL_intro.txt", "r");
		break;
	case 1:
		fp = fopen("..\\Data\\SidePocket_intro.txt", "r");
		break;
	case 2:
		fp = fopen("..\\Data\\Snooker_intro.txt", "r");
		break;
	}

	if (fp == NULL) {
		return -1;
	}

	while (!feof(fp)) {
		fgets(intro[i], 200, fp);
		i++;
	}

	lines = i;

	fclose(fp);
}
