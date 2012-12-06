#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

class Text;

class TextBuffer {

public:
	TextBuffer();
	TextBuffer(int size);
	TextBuffer(Text &t);
	TextBuffer(const char *c);
	TextBuffer(const wchar_t *c);
	virtual ~TextBuffer();
	
	void Append(Text &t);
	void Append(const char *t);
	void Append(const wchar_t *t);
	void AppendLine(Text &t);
	void AppendLine(const char *t);
	void AppendLine(const wchar_t *t);
	
	Text ToText();
	
private:
	void increaseBuffer(int newLen);

	wchar_t *p;
	int length;
	int psize;

};

#endif // TEXTBUFFER_H