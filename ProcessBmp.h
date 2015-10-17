#pragma once
class ProcessBmp
{
public:
	void LoadBmp(unsigned char * filepath, BYTE *bmp, long &width, long &height);
	void ShowBmp(CDC *dc,int x, int y, unsigned char * bmp, long width, long height);
protected:
private:
};