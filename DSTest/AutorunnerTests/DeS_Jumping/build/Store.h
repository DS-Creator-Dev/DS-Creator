
//{{BLOCK(Store)

//======================================================================
//
//	Store, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ bitmap not compressed
//	Total size: 512 + 65536 = 66048
//
//	Time-stamp: 2022-03-05, 14:11:19
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.17
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STORE_H
#define GRIT_STORE_H

#define StoreBitmapLen 65536
extern const unsigned int StoreBitmap[16384];

#define StorePalLen 512
extern const unsigned short StorePal[256];

#endif // GRIT_STORE_H

//}}BLOCK(Store)
