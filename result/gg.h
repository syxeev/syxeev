#ifndef GG_H
#define GG_H
class ss;
class gg{
private:
	int S;
public:
	gg(int);
	friend int func(gg &, ss &);
};
