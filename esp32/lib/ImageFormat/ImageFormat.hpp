#ifndef __IMAGEFORMAT_H__
#define __IMAGEFORMAT_H__

struct ImageFormat
{
    unsigned short int width, height, length;
    const unsigned char* data;
};


#endif // __IMAGEFORMAT_H__