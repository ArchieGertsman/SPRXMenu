#pragma once

#define TOC 0x0072DCE8 

struct opd_s
{
	uint32_t sub;
	uint32_t toc;
};

namespace PS3
{

int sys_ppu_thread_exit() {
	system_call_1(41, 0);
	return_to_user_prog(int);
}
int cstrcmp(const char* s1, const char* s2) { //Please note if its equal to zero the strings are equal 
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}
int console_write(const char * s) {
	uint32_t len;
	system_call_4(403, 0, (uint64_t)s, std::strlen(s), (uint64_t)&len);
	return_to_user_prog(int);
}
int32_t write_process(uint64_t ea, const void * data, uint32_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
sys_ppu_thread_t create_thread(void(*entry)(uint64_t), int priority, size_t stacksize, const char* threadname, sys_ppu_thread_t tid) {

	console_write((sys_ppu_thread_create(&tid, entry, 0, priority, stacksize, 0, threadname) != CELL_OK) ?
		"Thread creation failed\n" : "Thread created\n");
	return tid;
}
}
namespace 
{
	void sleep(usecond_t time) { //1 second = 1000
		sys_timer_usleep(time * 1000);
	}
	float* readFloat(int address, int length) {
		float floatArray[100];
		for (int i = 0; i < length; i++) {
			floatArray[i] = *(float*)(address + (i * 0x04));
		}
		return floatArray;
	}

	char* readBytes(int address, int length) {
		char byteArray[100];
		for (int i = 0; i < length; i++) {
			byteArray[i] = *(char*)(address + (i));
		}
		return byteArray;
	}

	void writeFloat(int address, float* input, int length) {
		for (int i = 0; i < length; i++) {
			*(float*)(address + (i * 4)) = input[i];
		}
	}

	float* readInt(int address, int length)
	{
		float intArray[100];
		for (int i = 0; i < length; i++) {
			intArray[i] = *(int*)(address + (i * 0x04));
		}
		return intArray;
	}

	void writeInt(int address, int* input, int length)
	{
		float intArray[100];
		for (int i = 0; i < length; i++) {
			*(int*)(intArray + (i * 0x04)) = input[i];
		}
	}

	void writeString(int address, char* string)
	{
		int FreeMem = 0x1D00000;
		int strlength = std::strlen(string);
		*(char**)FreeMem = string;
		char* StrBytes = readBytes(*(int*)FreeMem, strlength);
		PS3::write_process(address, &StrBytes, strlength);
	}

	struct readstr
	{
		char returnRead[100];
	}return_read[1000];

	char* readString(int address) {
		int strcount;
		strcount++;
		memset(&return_read[strcount].returnRead[0], 0, sizeof(return_read[strcount].returnRead));
		int strlength = 100;
		char* StrBytes = readBytes(address, strlength);
		for (int i = 0; i < strlength; i++) {
			if (StrBytes[i] != 0x00)
				return_read[strcount].returnRead[i] = StrBytes[i];
			else
				break;
		}
		return return_read[strcount].returnRead;
	}
}

