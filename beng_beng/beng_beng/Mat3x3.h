//--------------------------------------------------------------------------
//
//	19/03/2014
//
//	3x3 template matrix class
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __MAT3X3_H__
#define __MAT3X3_H__


namespace beng
{
	template<class T>
	class Mat3x3
	{
		Mat3x3(T i00, T i10, T i20,
				  T i01, T i11, T i21,
				  T i02, T i12, T i22) : m00(i00), m10(i10), m20(i20),
										 m01(i01), m11(i11), m21(i21),
										 m02(i02), m12(i12), m22(i22)
		{
		}

		Mat3x3() : m00(0), m10(0), m20(0),
					  m01(0), m11(0), m21(0),
					  m02(0), m12(0), m22(0)
		{
		}

		~Mat3x3()
		{
		}


	public:
		T m00, m10, m20;
		T m01, m11, m21;
		T m02, m12, m22;
	};

	typedef Mat3x3<int> Mat3x3i;
	typedef Mat3x3<float> Mat3x3f;
};


#endif