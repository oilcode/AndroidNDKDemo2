//----------------------------------------------------------------
#ifndef _SoMathInt2_h_
#define _SoMathInt2_h_
//----------------------------------------------------------------
class SoMathInt2
{
public:
	int x;
	int y;

public:
	SoMathInt2();
	SoMathInt2(int _x, int _y);
	SoMathInt2(const SoMathInt2& kOther);
	~SoMathInt2();

	void operator = (const SoMathInt2& kOther);
};
//----------------------------------------------------------------
inline SoMathInt2::SoMathInt2() : x(0), y(0)
{

}
//----------------------------------------------------------------
inline SoMathInt2::SoMathInt2(int _x, int _y) : x(_x), y(_y)
{

}
//----------------------------------------------------------------
inline SoMathInt2::SoMathInt2(const SoMathInt2& kOther) : x(kOther.x), y(kOther.y)
{

}
//----------------------------------------------------------------
inline SoMathInt2::~SoMathInt2()
{

}
//----------------------------------------------------------------
inline void SoMathInt2::operator = (const SoMathInt2& kOther)
{
	x = kOther.x;
	y = kOther.y;
}
//----------------------------------------------------------------
#endif //_SoMathInt2_h_
//----------------------------------------------------------------
