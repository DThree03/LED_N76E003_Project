#ifndef _TM1629A_MRLG_H_
#define _TM1629A_MRLG_H_


#define nop _nop_();

void TM1629_Begin(void);
void TM1629_CLEAR_ALL(void);
void setNshowAllSeg(unsigned char buffernum[]);
void blinkSegwithLine(unsigned char line);

#endif
	