#ifndef __HMENDIANCONV_H__
#define __HMENDIANCONV_H__

void BE2LE( __int16& i16Val );
void LE2BE( __int16& i16Val );
void BE2LE( __int32& i32Val );
void LE2BE( __int32& i32Val );
bool isBigEndian();
bool isLittleEndian();
void EndianTransfer( __int16& i16Val );
void EndianTransfer( __int32& i32Val );


#endif //__HMENDIANCONV_H__