#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include <iostream>
using namespace std;

struct TMonom
{
	double Coeff;
	int Power;
	TMonom* pNext;

	TMonom() :Coeff(0), Power(0), pNext(nullptr) {}
	TMonom(double coeff, int power);
	TMonom(double coeff, int power, TMonom* pnext);
	TMonom(const TMonom& tm);

	TMonom& operator=(const TMonom& tm)
	{
		Coeff = tm.Coeff;
		Power = tm.Power;
		return *this;
	}

	int operator==(const TMonom& tm)
	{
		if (Power == tm.Power && abs(Coeff - tm.Coeff) < 0.000001)
			return true;
		else return false;
	}

	int operator<(const TMonom& tm)
	{
		return Power < tm.Power;
	}
};

class TPolynom
{
protected:
	TMonom* pHead;
	int ListLen;
public:
	TPolynom();
	TPolynom(const TPolynom& tp);
	~TPolynom();

	int GetListLength() const { return ListLen; }
	void ClearList(void);
	void Insert(TMonom tm);
	void Insert(double coeff, int power);
	void Add(const TPolynom tp);
	void InsFirst(TMonom tm); 
	void DelFirst();
	void InsLast(TMonom tm);
	void DelList(TMonom tm);
	int IsInList(int power); 
	int Calculate(int val);

	TPolynom operator+(const TPolynom& q) const;
	TPolynom operator-(TPolynom& q);
	TPolynom operator*(const TPolynom& q); 
	TPolynom operator*(const double& q) const;
	const TPolynom& operator = (const TPolynom& q);

	friend ostream& operator << (ostream& os, const TPolynom& object);
};

#endif // !__POLYNOM_H__