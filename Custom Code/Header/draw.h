#pragma once
/*For the next frame, calculate the 
* possible trajectory of each billiard
*/
void nextTimeInit(struct billiard* head);

/*Refresh screen after all billiards are  
 * in right position
 */
void screenRefresh(struct billiard* head);

void displayAbout(void);