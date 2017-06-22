//----------------------------------------------------------------
#ifndef _SoMathInt3_h_
#define _SoMathInt3_h_
//----------------------------------------------------------------
class SoMathInt3
{
public:
	int x;
	int y;
	int z;

public:
	static SoMathInt3 ZERO;

public:
	SoMathInt3();
	SoMathInt3(int _x, int _y, int _z);
	SoMathInt3(const SoMathInt3& kOther);
	~SoMathInt3();

	void operator = (const SoMathInt3& kOther);
};
//----------------------------------------------------------------
inline SoMathInt3::SoMathInt3() : x(0), y(0), z(0)
{

}
//----------------------------------------------------------------
inline SoMathInt3::SoMathInt3(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
{

}
//----------------------------------------------------------------
inline SoMathInt3::SoMathInt3(const SoMathInt3& kOther) : x(kOther.x), y(kOther.y), z(kOther.z)
{

}
//----------------------------------------------------------------
inline SoMathInt3::~SoMathInt3()
{

}
//----------------------------------------------------------------
inline void SoMathInt3::operator = (const SoMathInt3& kOther)
{
	x = kOther.x;
	y = kOther.y;
	z = kOther.z;
}
//----------------------------------------------------------------
#endif //_SoMathInt3_h_
//----------------------------------------------------------------
