#include "serializator.h"
#include "filesystemexception.h"
#include "../Text/text.h"
#include "../nobjectregistry.h"
#include <string.h>
#include <typeinfo>

Serializator::Serializator(const IFile &file)
{
	this->file = (IFile *)&file;
}

Serializator::~Serializator()
{
	
}

void Serializator::Put(const NObject &o) 
{
	char strName[1000];
	strcpy(strName, typeid(o).name());
	unsigned char namelen = strlen(strName);
	unsigned char signature = 0x000000CC;

	file->Write((char *)&signature, sizeof(signature));
	file->Write((char *)&namelen, sizeof(namelen));
	file->Write(strName, namelen);
	((NObject *)&o)->Serialize(*this);
}

void Serializator::Put(char n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(short n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(int n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(long n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(long long n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned char n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned short n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned int n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned long n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned long long n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(float n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(double n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(long double n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::ensureRead(char *buffer, int lonBuffer)
{
	int leido = 0;
	while (leido < lonBuffer) {
		int res = file->Read(buffer + leido, lonBuffer - leido);
		if (res == 0) 
			throw new FileSystemException((Text)"End of file reached before reading " + lonBuffer + " requested bytes.", __FILE__, __LINE__, __func__);
		leido += res;
	}
}

NObject *Serializator::GetNObject()
{
	char strName[1000];
	unsigned char namelen = strlen(strName);
	unsigned char signature = 0;

	ensureRead((char *)&signature, sizeof(signature));
	ensureRead((char *)&namelen, sizeof(namelen));
	ensureRead(strName, namelen);
	
	NObject *o = NObjectRegistry::GetInstance(strName);
	o->Deserialize(*this);
	return o;
}

char Serializator::GetChar()
{
	char n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}

short Serializator::GetShort()
{
	short n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}

int Serializator::GetInt()
{
	int n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;	
}

long Serializator::GetLong()
{
	long n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}

long long Serializator::GetLongLong()
{
	long long n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}

unsigned char Serializator::GetUChar()
{
	unsigned char n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;	
}

unsigned short Serializator::GetUShort()
{
	unsigned short n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}

unsigned int Serializator::GetUInt()
{
	unsigned int n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}

unsigned long Serializator::GetULong()
{
	unsigned long n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}

unsigned long long Serializator::GetULongLong()
{
	unsigned long long n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}

float Serializator::GetFloat()
{
	float n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}

double Serializator::GetDouble()
{
	double n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}

long double Serializator::GetLongDouble()
{
	long double n = 0;
	ensureRead((char *)&n, sizeof(n));
	return n;
}