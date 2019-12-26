#include "Polynom.h"
#include <cmath>

TMonom::TMonom(double coeff, int power)
{
	if (power < 0 || power > 100)
		throw exception();

	Coeff = coeff;
	Power = power;
	pNext = 0;
}

TMonom::TMonom(double coeff, int power, TMonom* pnext) // конструктор инициализации
{
	Coeff = coeff;
	Power = power;
	pNext = pnext;
}

TMonom::TMonom(const TMonom& tm)
{
	Coeff = tm.Coeff;
	Power = tm.Power;
	pNext = tm.pNext;
} //конструктор копирования

TPolynom::TPolynom()
{
	pHead = 0;
	ListLen = 0;
}

TPolynom::TPolynom(const TPolynom& tp) : TPolynom()
{
	TMonom* tmp = tp.pHead;
	while (tmp != 0)
	{
		this->Insert(tmp->Coeff, tmp->Power);
		tmp = tmp->pNext;
	}
	ListLen = tp.ListLen;
}

TPolynom::~TPolynom()
{
	ClearList();
}

void TPolynom::ClearList(void)
{
	while (pHead != 0 && ListLen != 0)
		DelFirst();
}

int TPolynom::IsInList(int power)
{
	TMonom* currPos = pHead;
	while (currPos != 0) {
		if (currPos->Power == power) {
			return true;
		}
		currPos = currPos->pNext;
	}
	return false;
}

int TPolynom::Calculate(int val)
{
	TMonom* tmp = pHead;
	int result = 0;

	while (tmp != 0)
	{
		result += tmp->Coeff * pow(val, tmp->Power);
		tmp = tmp->pNext;
	}
	return result;
}

TPolynom TPolynom::operator+(const TPolynom& q) const
{
	TPolynom currPos;
	TMonom* currHead = this->pHead;
	while (currHead != 0) {
		currPos.Insert(currHead->Coeff, currHead->Power);
		currHead = currHead->pNext;
	}

	TMonom* qHead = q.pHead;
	while (qHead != 0) {
		currPos.Insert(qHead->Coeff, qHead->Power);
		qHead = qHead->pNext;
	}
	return currPos;
}

TPolynom TPolynom::operator-(TPolynom& q)
{
	TPolynom k = q * (-1);
	return *this + k;
}

TPolynom TPolynom::operator*(const TPolynom& q)
{
	TPolynom currPos;
	TMonom* mh = pHead;
	TMonom* mq = q.pHead;

	while (mh != 0) {
		mq = q.pHead;
		while (mq != 0)
		{
			double Coeff = mq->Coeff * mh->Coeff;
			int Power = mq->Power + mh->Power;
			currPos.Insert(Coeff, Power);
			mq = mq->pNext;
		}
		mh = mh->pNext;
	}
	return currPos;
}

TPolynom TPolynom::operator*(const double& q) const
{
	TPolynom tmp;
	TMonom* a = this->pHead;

	while (a != 0) {
		tmp.Insert(a->Coeff, a->Power);
		a = a->pNext;
	}

	TMonom* temp = tmp.pHead;

	while (temp != 0) {
		temp->Coeff = temp->Coeff * q;
		temp = temp->pNext;
	}
	return tmp;
}

const TPolynom& TPolynom::operator=(const TPolynom& q)
{
	if (this->pHead != q.pHead) {
		ClearList();

		TMonom* tmp = q.pHead;
		while (tmp != 0) {
			Insert(tmp->Coeff, tmp->Power);
			tmp = tmp->pNext;
		}
	}
	return *this;
}

void TPolynom::Insert(TMonom tm)
{
	if (pHead == 0 || pHead->Power > tm.Power) {
		InsFirst(tm);
		return;
	}

	TMonom* currPos = pHead;
	while (currPos->pNext != 0 && currPos->pNext->Power <= tm.Power && currPos->Power <= tm.Power) {
		currPos = currPos->pNext;
	}
	if (currPos->Power == tm.Power) {
		currPos->Coeff += tm.Coeff;
		if (abs(currPos->Coeff) < 0.000001) {
			DelList(*currPos);
		}
		return;
	}
	TMonom* obj = new TMonom(tm);
	obj->pNext = currPos->pNext;
	currPos->pNext = obj;
	ListLen++;

}

void TPolynom::Insert(double Coeff, int Power)
{
	TMonom tm(Coeff, Power);
	if (pHead == 0 || pHead->Power > tm.Power) {
		InsFirst(tm);
		return;
	}

	TMonom* currPos = pHead;
	while (currPos->pNext != 0 && currPos->pNext->Power <= tm.Power && currPos->Power <= tm.Power) {
		currPos = currPos->pNext;
	}
	if (currPos->Power == tm.Power)
	{
		currPos->Coeff += tm.Coeff;
		if (abs(currPos->Coeff) < 0.000001)
		{
			DelList(*currPos);
		}
		return;
	}
	TMonom* obj = new TMonom(tm);
	obj->pNext = currPos->pNext;
	currPos->pNext = obj;
	ListLen++;
}

void TPolynom::Add(const TPolynom tp)
{
	TPolynom tmp;
	TMonom* currPos1 = (this)->pHead;
	TMonom* currPos2 = tp.pHead;

	while (currPos1 != 0 && currPos2 != 0)
	{
		if (currPos1->Power <= currPos2->Power)
		{
			TMonom newMonom(*currPos1);
			newMonom.pNext = 0;
			tmp.InsLast(newMonom);
			currPos1 = currPos1->pNext;
		}
		else
		{
			TMonom newMonom(*currPos2);
			newMonom.pNext = 0;
			tmp.InsLast(newMonom);
			currPos2 = currPos2->pNext;
		}
	}

	while (currPos1 != 0)
	{
		TMonom newMonom(*currPos1);
		newMonom.pNext = 0;
		tmp.InsLast(newMonom);
		currPos1 = currPos1->pNext;
	}

	while (currPos2 != 0)
	{
		TMonom newMonom(*currPos2);
		newMonom.pNext = 0;
		tmp.InsLast(newMonom);
		currPos2 = currPos2->pNext;
	}

	*this = tmp;
	tmp.pHead = 0;
	tmp.ListLen = 0;
}

void TPolynom::InsFirst(TMonom tm)
{
	pHead = new TMonom(tm.Coeff, tm.Power, pHead);
	ListLen++;
}

void TPolynom::DelFirst()
{
	TMonom* tmp = pHead;
	pHead = pHead->pNext;
	delete tmp;
	ListLen--;
}

void TPolynom::InsLast(TMonom tm)
{

	if (pHead == 0) {
		pHead = new TMonom(tm);
	}
	else {
		TMonom* currPos = pHead;
		while (currPos->pNext != 0) {
			currPos = currPos->pNext;
		}
		currPos->pNext = new TMonom(tm);
	}
	ListLen++;
}

void TPolynom::DelList(TMonom tm)
{
	TMonom* currPos = pHead;
	if (currPos->Power == tm.Power && abs(currPos->Coeff - tm.Coeff) < 0.000001) {
		DelFirst();
		return;
	}

	while (currPos->pNext != 0 && currPos->pNext->Power != tm.Power) {
		currPos = currPos->pNext;
	}

	TMonom* tmp = currPos->pNext->pNext;
	delete currPos->pNext;
	currPos->pNext = tmp;
	ListLen--;
}

ostream& operator<<(ostream& os, const TPolynom& obj)
{
	if (obj.pHead == 0) {
		os << 0;
		return os;
	}

	TMonom* tmp = obj.pHead;
	while (tmp != 0)
	{
		if (tmp->Coeff > 0) {
			os << tmp->Coeff << " ";
		}
		else {
			os << "(" << tmp->Coeff << ") ";
		}
		if (tmp->Power != 0) {
			os << "* x^" << tmp->Power << " ";
		}
		if (tmp->pNext != 0) {
			os << "+ ";
		}
		tmp = tmp->pNext;
	}
	return os;
}