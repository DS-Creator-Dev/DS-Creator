
//{{BLOCK(Store)

//======================================================================
//
//	Store, 256x192@8, 
//	+ palette 256 entries, not compressed
//	+ bitmap not compressed
//	Total size: 512 + 49152 = 49664
//
//	Time-stamp: 2022-03-22, 15:15:14
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.17
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STORE_H
#define GRIT_STORE_H

#define StoreBitmapLen 49152
extern const unsigned int StoreBitmap[12288];

#define StorePalLen 512
extern const unsigned short StorePal[256];

#endif // GRIT_STORE_H

//}}BLOCK(Store)
