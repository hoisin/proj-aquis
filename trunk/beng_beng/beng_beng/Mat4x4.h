//--------------------------------------------------------------------------
//
//	19/03/2014
//
//	4x4 template matrix class
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __MAT4X4_H__
#define __MAT4X4_H__


namespace beng
{
	template<class T>
	class Mat4x4
	{
		Mat4x4(T i00, T i10, T i20, T i30,
				  T i01, T i11, T i21, T i31,
				  T i02, T i12, T i22, T i32,
				  T i03, T i13, T i23, T i33) : m00(i00), m10(i10), m20(i20), m30(i30),
												 m01(i01), m11(i11), m21(i21), m31(i31),
												 m02(i02), m12(i12), m22(i22), m32(i32),
												 m03(i03), m13(i13), m23(i23), m33(i33)
		{
		}

		Mat4x4() : m00(0), m10(0), m20(0), m30(0),
			          m01(0), m11(0), m21(0), m31(0),
					  m02(0), m12(0), m22(0), m32(0),
					  m03(0), m13(0), m23(0), m33(0)
		{
		}

		~Mat4x4()
		{
		}


	public:
		T m00, m10, m20, m30;
		T m01, m11, m21, m31;
		T m02, m12, m22, m32;
		T m03, m13, m23, m33;
	};

	typedef Mat4x4<int> Mat4x4i;
	typedef Mat4x4<float> Mat4x4f;
};


#endif