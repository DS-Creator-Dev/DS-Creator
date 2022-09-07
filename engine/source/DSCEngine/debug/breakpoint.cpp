#include "DSCEngine/debug/log.hpp"
#include <cstdarg>

namespace DSC::Debug
{	
	// gcc translates inline asm "mov r7,r7" to "add r7, r7, #0"
	// so we have to hardcode the intended instruction
	#define MOV_R7_R7 ".BYTE 0x3f, 0x46"
	
	__attribute__((always_inline)) inline void SET_BREAKPOINT()
	{
		asm volatile (MOV_R7_R7); // mov r7, r7
	}
	
	__attribute__((target("thumb"))) void _log(const char* message)
	{
		asm volatile
		(
			"push {r6} \r\n"
			"mov r6, %0 \r\n"
			MOV_R7_R7 "\r\n"
			"pop {r6}\r\n"			
			:: "r"(message)
		);
	}
	
	__attribute__((target("thumb"))) void log(const char* message, ...)
	{
		va_list args;
		
		va_start(args, message);
		
		char* result = new char[1024];
		char* built = result;
				
		for(const char* msg=message; *msg;)
		{
			if(*msg=='%')
			{
				++msg;
				if(*msg==0) break;
				
				switch(*msg)
				{
					case 'i':
					{						
						int val = va_arg(args, int);

						if(val==0)
						{
							*(built++)='0';
							break;
						}
						
						if(val<0)						
							*(built++)='-', val = -val;						
						
						int temp = 0;
						for(;val;val/=10) temp=temp*10 + val%10;						
						for(;temp;temp/=10) *(built++)='0'+temp%10;
						
						++msg;
						break;
					}
					case 'u':
					{
						unsigned int val = va_arg(args, unsigned int);
						
						if(val==0)
						{
							*(built++)='0';
							break;
						}
						
						int temp = 0;
						for(;val;val/=10) temp=temp*10 + val%10;						
						for(;temp;temp/=10) *(built++)='0'+temp%10;
						
						break;
					}
					case 's':
					{
						char* val = va_arg(args, char*);
						
						while(*val) *(built++)=*(val++);
											
						++msg;
						break;
					}
				}					
			}
			else
			{
				*(built++)=*(msg++);
			}
		}	
		va_end(args);		
		
		*(built)='\0';		
		_log(result);
		
		delete[] result;
	}	
}