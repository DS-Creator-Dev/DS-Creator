#include <stdio.h>
#include <cassert>
#include <iostream>
#include <windows.h>


#include "allocator.hpp"

// habit :))
#define iprintf printf 

#include <set>
using namespace std;
set<int> lists;

struct Block32 { char data[32]; };

void* generate_mem()
{
	char* data = new char[32*1024];
	
	return data;
}

class PublicAllocator
{
public:
	unsigned char id;
	int base_offset;
	int base_length;		
	int free_space_head;
	static PublicAllocator* from(DSC::Allocator* alc)
	{
		return (PublicAllocator*)alc;
	}
};

struct alloc_info
{	
	int32_t length;	
	alloc_info* prev;
	alloc_info* next;	
	
	
	int offset() { return (int)(long long)this;}	
	
	static alloc_info* at(int offset)
	{
		return (alloc_info*)(long long)offset;
	}
};

const char* symbols_free = "abcdefghijklmnopqrstuvwxyz0123456789";
const char* symbols_alcd = "ABCDEFGHIJKLMNOPQRSTUVWXYZ)!@#$%^&*(";

void display_memory_map(DSC::Allocator* alc)
{
	lists.clear();
	char blocks[32][33];
	
	for(int i=0;i<32;i++) blocks[i][32]='\0';
	
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++) blocks[i][j] = '_';
	}
	
	int head = PublicAllocator::from(alc)->free_space_head;
	int base = PublicAllocator::from(alc)->base_offset;
	
	//printf("----> %i\n\n", head);
	
	int sf_id = 0;
	for(auto* alc = alloc_info::at(head); alc; alc=alc->next)
	{
		lists.insert((int)alc);
		lists.insert((int)alc+4);
		lists.insert((int)alc+8);
		//printf("!---> %08X\n\n", (int)(long long)alc);
		//printf("!---> %08X\n\n", head);
		int rel_offset = ((int)alc) - base;
		if(rel_offset%32>0) 
		{
			printf("Offset not aligned with block.");
			exit(1);
		}		
		rel_offset/=32;
		
		int len = alc->length/32;
		for(int j=0;j<len;j++)
		{			
			blocks[rel_offset/32][rel_offset%32] = symbols_free[sf_id];
			rel_offset++;
		}
				
		sf_id++;
	}
	
	
	
	for(int i=0;i<32;i++) printf("%02i |%s\n",i+1, blocks[i]);
}

int main()
{
	HANDLE  hConsole;    
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  
	printf("Initing test...\n");
	
	// simulate a VRAM bank
	Block32* space = (Block32*)generate_mem();	
	
	printf("Test memory address : %p \n\n", space);
				
	printf("Creating allocator..\n");
	int offset32 = (int)(long long)space; 	
	DSC::Allocator alc(offset32, 32*1024);
	printf("Allocator id   : %i\n", PublicAllocator::from(&alc)->id);
	printf("Allocator base : offset = 0x%08X, length = %i\n", 
		PublicAllocator::from(&alc)->base_offset, 
		PublicAllocator::from(&alc)->base_length);
		
	printf("Allocator head : 0x%08X\n\n", PublicAllocator::from(&alc)->free_space_head);
	
	int op = 0;
	while(1)
	{
		printf("Allocator head : 0x%08X (rel. 0x%08X)\n\n", PublicAllocator::from(&alc)->free_space_head,
				PublicAllocator::from(&alc)->free_space_head - PublicAllocator::from(&alc)->base_offset);
		display_memory_map(&alc);
		
		printf("Operation (1=reserse, 2=release, 3=dump memory, 0=exit)\n >>> ");
		scanf("%i",&op);
		if(op==1)
		{
			int length;
			printf("Length = ");
			scanf("%i", &length);
			void* offset = alc.reserve(length);
			for(int i=0;i<length;i++)
			{
				*((char*)offset+i) = -1;
			}
			
			printf("Reserved address at %08p (relative offset: 0x%08X)\n", offset, (int)(long long)offset - PublicAllocator::from(&alc)->base_offset);
			printf("Allocator head : 0x%08X (rel. 0x%08X)\n\n", PublicAllocator::from(&alc)->free_space_head,
				PublicAllocator::from(&alc)->free_space_head - PublicAllocator::from(&alc)->base_offset);
		}
		else if(op==2)
		{
			int offset;
			printf("Offset (rel.) = ");
			scanf("%i", &offset);
			printf("Freeing %08X\n",(int)space+offset);
			alc.release((void*)((int)space+offset));
			
		}
		else if(op==3)
		{
			SetConsoleTextAttribute(hConsole, 0x0F);
			int* data = (int*)space;
			for(int i=0;i<8*10;) 
			{
				printf("%08X |  ", (int)data + i*4);
				for(int j=8;j--;i++)
				{
					if(lists.find((int)data+4*i)!=lists.end())
					{
						SetConsoleTextAttribute(hConsole, 0x01);
						printf("%08X ", data[i]);
						SetConsoleTextAttribute(hConsole, 0x0F);
					}
					else
					{
						SetConsoleTextAttribute(hConsole, 0x0F);
						printf("%08X ", data[i]);
						SetConsoleTextAttribute(hConsole, 0x0F);
					}					
				}
				printf("\n");
			}
		}
		else if(op==0)
		{
			exit(0);
		}
		printf("\n\n");
		getchar();
		getchar();
	}
	return 0;
}