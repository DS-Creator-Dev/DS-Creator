#pragma once

namespace DSC
{
	/// ReadOnlyData denotes a type of static resource 
	/// that lies either in RAM, FAT or NITRO.
	/// 
	/// This class represents an abstract interface for resource management 
	/// and should be able to retrieve any bytes buffer regardless of its 
	/// localization.
	///
	/// This class can also be derived to describe more specialized resource
	/// formats.
	///
	/// This class is NOT the binary data itself, but only an expression of it.
	/// It is more like a header that resides only in WRAM, whilst the data it
	/// points to can be anywhere.
	///
	/// Instances of this class should be constants, not allow moving/making copies of them.
	/// In fact, only DSC specialized tools have to create reliable ReadOnlyData instances.
	///
	/// Referencing instances of this class should only be done through pointers
	/// (attention to down/upcasts, no polymorphism is being used)
	///
	///
	/// [ !!! POSSIBLE BUG SOURCE !!! ] There is no "Read-Only Memory" thing on DS homebrew. 
	/// All the constants are being placed in EWRAM (4MB). The compiler tries its best to
	/// prevent programmers from altering constant values, but one can simply break the rule
	/// by overwriting a constant only using its dereferenced pointer. Assuming the programmer doesn't
	/// try anything strange, there is still a chance that an undefined behavior/RAM corruption/
	/// some accidental buffer overflow (eg. for i=0;i<10;i--) may overwrite in-memory "read-only" data.
	/// We should keep a careful eye on that and consider it as a potential explanation for any visual glitches
	/// or misterious data corruption. Therefore, when constant data changes its bytes, then something's really messed up.
	
	class ReadOnlyData
	{		
	public:                      /// Some technical observations to account for during implementation:
	
		int header_size;         /// equilavent of sizeof(*this), but foresees class inheritance
		int data_length;         /// size in bytes of the actual data
		bool is_file;            /// tell if the data is in RAM or on a filesystem
		char* data_source;       /// if is_file==true, data_source is the file path (fat://..., nitro://...)
		                         /// if is_file==false, data_source is a pointer to WRAM
						         /// if data_source==NULL, then the actual data resides right after *this
		bool compression_type;   /// 0 = no compression, 1=LZ7 or sth, ...
		
		ReadOnlyData(int header_size = sizeof(ReadOnlyData));		
		
		// writes binary data to the given address (most popular expected use: VRAM)		
		void extract(void* destination); 
		
		// prevent altering this object
		ReadOnlyData(const ReadOnlyData&) = delete;
		ReadOnlyData(ReadOnlyData&&) = delete;
		ReadOnlyData operator = (const ReadOnlyData&) = delete;
		ReadOnlyData operator = (ReadOnlyData&&) = delete;		
	};
	
	class AssetData : public ReadOnlyData // only as an example
	{
	public:
		int width;        // new properties
		int height;       // packed in a single place 
		bool is_bitmap;
		int color_depth;
		//...
		
		AssetData() : ReadOnlyData(sizeof(AssetData)) {} // this line is important
		~AssetData() = delete;
	};
}