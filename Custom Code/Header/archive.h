#pragma once

void saveBilliardInfo(struct billiard* head);

void savePlayerInfo(struct player* P1, struct player* P2);

struct billiard* readBilliardInfo(int GameMode);

void readPlayerInfo(struct player* P1, struct player* P2);

void saveMode();

void readMode();

void readIntro();