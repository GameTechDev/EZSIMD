
#include "stdafx.h"

// ******************************************************************
class VFloat
{
public:
    __m256 mAsVector;

public:
    VFloat(){};
    ~VFloat(){};

    explicit VFloat( const float val )
    {
        mAsVector = _mm256_set1_ps( val );
    }

    explicit VFloat( const __m256 &v0 )
    {
        mAsVector = v0;
    }

    explicit VFloat(
        const float v0, const float v1, const float v2, const float v3,
        const float v4, const float v5, const float v6, const float v7
    )
    {
        mAsVector = _mm256_set_ps( v0, v1, v2, v3, v4, v5, v6, v7 );
    }

    __forceinline VFloat operator+( const VFloat &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_add_ps( mAsVector, val.mAsVector );
        return tmp;
    }
    __forceinline VFloat operator+( const float val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_add_ps( mAsVector, _mm256_set1_ps(val) );
        return tmp;
    }
/*
    VInt asVInt()
    {
        VInt tmp;
        tmp.mAsVector = _mm256_castps_si256( mAsVector );
        return tmp;
    }
*/

    __forceinline VFloat operator-( const VFloat &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_sub_ps( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat operator*( const VFloat &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_mul_ps( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat operator*( const float val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_mul_ps( mAsVector, _mm256_set1_ps( val ) );
        return tmp;
    }

    __forceinline VFloat operator/( const VFloat &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_div_ps( mAsVector, val.mAsVector );
        return tmp;
    }
    __forceinline VFloat operator/( const float val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_div_ps( mAsVector, _mm256_set1_ps( val ) );
        return tmp;
    }
    __forceinline VFloat Reciprocal()
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_rcp_ps( mAsVector );
        return tmp;
    }

    __forceinline float HorizontalSum() const
    {
        return mAsVector.m256_f32[0] + mAsVector.m256_f32[1] + mAsVector.m256_f32[2] + mAsVector.m256_f32[3];
    }

    __forceinline float Red() const
    {
        return mAsVector.m256_f32[0];
    }

    __forceinline float Green() const
    {
        return mAsVector.m256_f32[1];
    }

    __forceinline float Blue() const
    {
        return mAsVector.m256_f32[2];
    }
/*
    __forceinline VFloat ShiftVectorLeftOne()
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mAsVector), 4 ) );
        return tmp;
    }

    __forceinline VFloat ShiftVectorLeftTwo()
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mAsVector), 8 ) );
        return tmp;
    }

    __forceinline VFloat ShiftVectorLeftThree()
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mAsVector), 12 ) );
        return tmp;
    }

    __forceinline VFloat ShiftVectorRightByOne()
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mAsVector), 4 ) );
        return tmp;
    }

    __forceinline VFloat ShiftVectorRightByTwo()
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mAsVector), 8 ) );
        return tmp;
    }

    __forceinline VFloat ShiftVectorRightByThree()
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mAsVector), 12 ) );
        return tmp;
    }
*/
/*
    __forceinline VFloat Shuffle( VFloat v0, int val )
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_shuffle_ps( mAsVector, v0.mAsVector, val );
        return tmp;
    }
*/
};

#pragma warning( disable:4201 )
#if 0
// ******************************************************************
class VFloat4
{
public:
    union {
        struct {
            __m256 mRed;
            __m256 mGreen;
            __m256 mBlue;
            __m256 mAlpha;
        };
        struct {
            __m256 mX;
            __m256 mY;
            __m256 mZ;
            __m256 mW;
        };
    };

public:
    VFloat4(){};
    ~VFloat4(){};

    explicit VFloat4( const float val )
    {
        mX = mY = mZ = mW = _mm256_set1_ps( val );
    }

    explicit VFloat4( const float xx, const float yy, const float zz, const float ww )
    {
        mX = mY = mZ = mW = _mm256_set_ps( xx, yy, zz, ww );
    }

    explicit VFloat4( const VFloat &v0, const VFloat &v1, const VFloat &v2, const VFloat &v3 )
    {
        mX = v0.mAsVector;
        mY = v1.mAsVector;
        mZ = v2.mAsVector;
        mW = v3.mAsVector;
    }

    __forceinline const VFloat4 operator+( const VFloat4 &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm256_add_ps( mX, val.mX );
        tmp.mY = _mm256_add_ps( mY, val.mY );
        tmp.mZ = _mm256_add_ps( mZ, val.mZ );
        tmp.mW = _mm256_add_ps( mW, val.mW );
        return tmp;
    }

    __forceinline const VFloat4 operator-( const VFloat4 &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm256_sub_ps( mX, val.mX );
        tmp.mY = _mm256_sub_ps( mY, val.mY );
        tmp.mZ = _mm256_sub_ps( mZ, val.mZ );
        tmp.mW = _mm256_sub_ps( mW, val.mW );
        return tmp;
    }

    __forceinline const VFloat4 operator*( const VFloat4 &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm256_mul_ps( mX, val.mX );
        tmp.mY = _mm256_mul_ps( mY, val.mY );
        tmp.mZ = _mm256_mul_ps( mZ, val.mZ );
        tmp.mW = _mm256_mul_ps( mW, val.mW );
        return tmp;
    }

    __forceinline const VFloat4 operator*( float val ) const
    {
        __m256 vv = _mm256_set1_ps( val );
        VFloat4 tmp;
        tmp.mX = _mm256_mul_ps( mX, vv );
        tmp.mY = _mm256_mul_ps( mY, vv );
        tmp.mZ = _mm256_mul_ps( mZ, vv );
        tmp.mW = _mm256_mul_ps( mW, vv );
        return tmp;
    }

    __forceinline const VFloat4 operator+( const VFloat &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm256_add_ps( mX, val.mAsVector );
        tmp.mY = _mm256_add_ps( mY, val.mAsVector );
        tmp.mZ = _mm256_add_ps( mZ, val.mAsVector );
        tmp.mW = _mm256_add_ps( mW, val.mAsVector );
        return tmp;
    }

    __forceinline const VFloat4 operator-( const VFloat &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm256_sub_ps( mX, val.mAsVector );
        tmp.mY = _mm256_sub_ps( mY, val.mAsVector );
        tmp.mZ = _mm256_sub_ps( mZ, val.mAsVector );
        tmp.mW = _mm256_sub_ps( mW, val.mAsVector );
        return tmp;
    }

    __forceinline const VFloat4 operator*( const VFloat &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm256_mul_ps( mX, val.mAsVector );
        tmp.mY = _mm256_mul_ps( mY, val.mAsVector );
        tmp.mZ = _mm256_mul_ps( mZ, val.mAsVector );
        tmp.mW = _mm256_mul_ps( mW, val.mAsVector );
        return tmp;
    }

    __forceinline const VFloat4 operator/( const VFloat4 &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm256_div_ps( mX, val.mX );
        tmp.mY = _mm256_div_ps( mY, val.mY );
        tmp.mZ = _mm256_div_ps( mZ, val.mZ );
        tmp.mW = _mm256_div_ps( mW, val.mW );
        return tmp;
    }

    // TODO: Which way do we want to do this?  SOA or AOS?
    // For now, keep with the "SOA is behind the scenes" theme, and add the vectors together
    // instead of adding each of them horizontally.
    __forceinline VFloat HorizontalSum() const
    {
/*
        VFloat tmp;
        tmp.mAsVector.m256_f32[0] = mX.m256_f32[0] + mX.m256_f32[1] + mX.m256_f32[2] + mX.m256_f32[3];
        tmp.mAsVector.m256_f32[1] = mY.m256_f32[0] + mY.m256_f32[1] + mY.m256_f32[2] + mY.m256_f32[3];
        tmp.mAsVector.m256_f32[2] = mZ.m256_f32[0] + mZ.m256_f32[1] + mZ.m256_f32[2] + mZ.m256_f32[3];
        tmp.mAsVector.m256_f32[3] = mW.m256_f32[0] + mW.m256_f32[1] + mW.m256_f32[2] + mW.m256_f32[3];
        return tmp;
*/
        VFloat tmp;
        tmp.mAsVector = _mm256_add_ps( _mm256_add_ps( mRed, mGreen ), _mm256_add_ps( mBlue, mAlpha ) );
        return tmp;
    }
    __forceinline VFloat4 operator[](int lane)
    {
        // "extraxt" one lane, "promote" to VFloat4.
        return VFloat4(
            VFloat(mX.m256_f32[lane]),
            VFloat(mY.m256_f32[lane]),
            VFloat(mZ.m256_f32[lane]),
            VFloat(mW.m256_f32[lane])
        );
    }
};
#endif

// ******************************************************************
class VInt
{
public:
    __m256i mAsVector;

public:
    VInt(){};
    ~VInt(){};

    explicit VInt( const __m256i val )
    {
        mAsVector = val;
    }

    explicit VInt( const int val )
    {
        mAsVector = _mm256_set1_epi32( val );
    }

    explicit VInt(
        const int v0, const int v1, const int v2, const int v3,
        const int v4, const int v5, const int v6, const int v7 
        )
    {
        mAsVector = _mm256_set_epi32( v0, v1, v2, v3, v4, v5, v6, v7 );
    }

    explicit VInt( const VFloat &v0 )
    {
        // mAsVector = _mm256_castps_si256( v0.mAsVector );
        mAsVector = _mm256_cvtps_epi32( v0.mAsVector );
    }
/*
    __forceinline VInt operator+( const VInt &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm256_add_epi32( mAsVector, val.mAsVector );
        return tmp;
    }
*/
    __forceinline VInt operator+( const int &val ) const
    {
        VInt tmp;

		__m128i upper128 = _mm_castps_si128(_mm256_extractf128_ps( _mm256_castsi256_ps(mAsVector), 1 ));
		__m128i lower128 = _mm_castps_si128(_mm256_extractf128_ps( _mm256_castsi256_ps(mAsVector), 0 ));

		upper128 = _mm_add_epi32( upper128, _mm_set1_epi32(val) );
		lower128 = _mm_add_epi32( lower128, _mm_set1_epi32(val) );

		tmp.mAsVector = _mm256_insertf128_si256( _mm256_setzero_si256(), upper128, 1 ); 
		tmp.mAsVector = _mm256_insertf128_si256( tmp.mAsVector, lower128, 0 ); 
        return tmp;
    }
/*
    __forceinline VInt operator-( const VInt &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm256_sub_epi32( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VInt operator*( const VInt &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm256_mul_epi32( mAsVector, val.mAsVector );
        return tmp;
    }
*/
//    VInt operator/( VInt val )
//    {
//        VInt tmp;
//        tmp.mAsVector = _mm256_div_epi32( mAsVector, val.mAsVector );
//    }
/*
*/
    __forceinline VInt UnpackHi16( const VInt &src ) const
    {
        VInt tmp;
		__m128i upper128 = _mm_castps_si128(_mm256_extractf128_ps( _mm256_castsi256_ps(src.mAsVector), 1 ));
		__m128i upperF16 = _mm_unpackhi_epi16( upper128, _mm_setzero_si128() );
		__m128i lowerF16 = _mm_unpacklo_epi16( upper128, _mm_setzero_si128() );
		tmp.mAsVector = _mm256_insertf128_si256( _mm256_setzero_si256(), upperF16, 1 ); 
		tmp.mAsVector = _mm256_insertf128_si256( tmp.mAsVector, lowerF16, 0 ); 
        return tmp;
    }
    __forceinline VInt UnpackLow16( const VInt &src ) const
    {
        VInt tmp;
		__m128i lower128 = _mm_castps_si128(_mm256_extractf128_ps( _mm256_castsi256_ps(src.mAsVector), 0 ));
		__m128i upperF16 = _mm_unpackhi_epi16( lower128, _mm_setzero_si128() );
		__m128i lowerF16 = _mm_unpacklo_epi16( lower128, _mm_setzero_si128() );
		tmp.mAsVector = _mm256_insertf128_si256( _mm256_setzero_si256(), upperF16, 1 ); 
		tmp.mAsVector = _mm256_insertf128_si256( tmp.mAsVector, lowerF16, 0 ); 
        return tmp;
    }

	__forceinline VInt operator&( const VInt &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm256_castps_si256(_mm256_and_ps( _mm256_castsi256_ps(mAsVector), _mm256_castsi256_ps(val.mAsVector) ));
        return tmp;
    }
    __forceinline VInt operator&( const int &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm256_castps_si256(_mm256_and_ps( _mm256_castsi256_ps(mAsVector), _mm256_castsi256_ps(_mm256_set1_epi32(val)) ));
        return tmp;
    }
    __forceinline VInt operator|( const VInt &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm256_castps_si256(_mm256_or_ps( _mm256_castsi256_ps(mAsVector), _mm256_castsi256_ps(val.mAsVector) ));
        return tmp;
    }

    __forceinline VInt operator<<( const int count ) const
    {
        VInt tmp;

		__m128i upper128 = _mm_castps_si128(_mm256_extractf128_ps( _mm256_castsi256_ps(mAsVector), 1 ));
		__m128i lower128 = _mm_castps_si128(_mm256_extractf128_ps( _mm256_castsi256_ps(mAsVector), 0 ));

		upper128 = _mm_slli_epi32( upper128, count );
		lower128 = _mm_slli_epi32( lower128, count );


		tmp.mAsVector = _mm256_insertf128_si256( _mm256_setzero_si256(), upper128, 1 ); 
		tmp.mAsVector = _mm256_insertf128_si256( tmp.mAsVector, lower128, 0 ); 
        return tmp;
    }

    __forceinline VFloat InterpretAsVFloat() const
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_castsi256_ps( mAsVector );
        return tmp;
    }
};


// ******************************************************************
class VFloat3
{
public:
    union {
        struct {
            __m256 mRed;
            __m256 mGreen;
            __m256 mBlue;
        };
        struct {
            __m256 mX;
            __m256 mY;
            __m256 mZ;
        };
    };

public:
    VFloat3(){};
    ~VFloat3(){};

    explicit VFloat3( const float val )
    {
        mX = mY = mZ = _mm256_set1_ps( val );
    }

    explicit VFloat3( const float xx, const float yy, const float zz )
    {
        mX = _mm256_set1_ps( xx );
        mY = _mm256_set1_ps( yy );
        mZ = _mm256_set1_ps( zz );
    }

    explicit VFloat3( const VFloat &v0, const VFloat &v1, const VFloat &v2 )
    {
        mX = v0.mAsVector;
        mY = v1.mAsVector;
        mZ = v2.mAsVector;
    }

    __forceinline VFloat3 operator+( const VFloat3 &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm256_add_ps( mX, val.mX );
        tmp.mY = _mm256_add_ps( mY, val.mY );
        tmp.mZ = _mm256_add_ps( mZ, val.mZ );
        return tmp;
    }

    __forceinline VFloat3 operator-( const VFloat3 &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm256_sub_ps( mX, val.mX );
        tmp.mY = _mm256_sub_ps( mY, val.mY );
        tmp.mZ = _mm256_sub_ps( mZ, val.mZ );
        return tmp;
    }

    __forceinline VFloat3 operator*( const VFloat3 &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm256_mul_ps( mX, val.mX );
        tmp.mY = _mm256_mul_ps( mY, val.mY );
        tmp.mZ = _mm256_mul_ps( mZ, val.mZ );
        return tmp;
    }

    __forceinline VFloat3 operator+( const VFloat &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm256_add_ps( mX, val.mAsVector );
        tmp.mY = _mm256_add_ps( mY, val.mAsVector );
        tmp.mZ = _mm256_add_ps( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat3 operator-( const VFloat &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm256_sub_ps( mX, val.mAsVector );
        tmp.mY = _mm256_sub_ps( mY, val.mAsVector );
        tmp.mZ = _mm256_sub_ps( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat3 operator*( const VFloat &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm256_mul_ps( mX, val.mAsVector );
        tmp.mY = _mm256_mul_ps( mY, val.mAsVector );
        tmp.mZ = _mm256_mul_ps( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat3 operator/( const VFloat3 &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm256_div_ps( mX, val.mX );
        tmp.mY = _mm256_div_ps( mY, val.mY );
        tmp.mZ = _mm256_div_ps( mZ, val.mZ );
        return tmp;
    }

    __forceinline VFloat3 operator+( const float val ) const
    {
        VFloat3 tmp;
        __m256 valVec = _mm256_set1_ps(val);
        tmp.mX = _mm256_add_ps( mX, valVec );
        tmp.mY = _mm256_add_ps( mY, valVec );
        tmp.mZ = _mm256_add_ps( mZ, valVec );
        return tmp;
    }

    __forceinline VFloat3 operator-( const float val ) const
    {
        VFloat3 tmp;
        __m256 valVec = _mm256_set1_ps(val);
        tmp.mX = _mm256_sub_ps( mX, valVec );
        tmp.mY = _mm256_sub_ps( mY, valVec );
        tmp.mZ = _mm256_sub_ps( mZ, valVec );
        return tmp;
    }

    __forceinline VFloat3 operator*( const float val ) const
    {
        VFloat3 tmp;
        __m256 valVec = _mm256_set1_ps(val);
        tmp.mX = _mm256_mul_ps( mX, valVec );
        tmp.mY = _mm256_mul_ps( mY, valVec );
        tmp.mZ = _mm256_mul_ps( mZ, valVec );
        return tmp;
    }

    __forceinline VFloat3 operator/( const float val ) const
    {
        VFloat3 tmp;
        __m256 valVec = _mm256_set1_ps(val);
        tmp.mX = _mm256_div_ps( mX, valVec );
        tmp.mY = _mm256_div_ps( mY, valVec );
        tmp.mZ = _mm256_div_ps( mZ, valVec );
        return tmp;
    }

    // TODO: Which way do we want to do this?  SOA or AOS?
    // For now, keep with the "SOA is behind the scenes" theme, and add the vectors together
    // instead of adding each of them horizontally.
    __forceinline VFloat HorizontalSum() const
    {
        VFloat tmp;
        tmp.mAsVector = _mm256_add_ps( _mm256_add_ps( mRed, mGreen ),  mBlue );
        return tmp;
    }

    __forceinline VInt AsRgbaVInt() const
    {
        VInt tmp;

        __m128i redUpper128   = _mm_cvtps_epi32(_mm256_extractf128_ps( mRed,   1 ));
		__m128i redLower128   = _mm_cvtps_epi32(_mm256_extractf128_ps( mRed,   0 ));
		__m128i greenUpper128 = _mm_cvtps_epi32(_mm256_extractf128_ps( mGreen, 1 ));
		__m128i greenLower128 = _mm_cvtps_epi32(_mm256_extractf128_ps( mGreen, 0 ));
		__m128i blueUpper128  = _mm_cvtps_epi32(_mm256_extractf128_ps( mBlue,  1 ));
		__m128i blueLower128  = _mm_cvtps_epi32(_mm256_extractf128_ps( mBlue,  0 ));

		greenUpper128 = _mm_slli_epi32( greenUpper128, 8 );
		greenLower128 = _mm_slli_epi32( greenLower128, 8 );

		blueUpper128  = _mm_slli_epi32( blueUpper128, 16 );
		blueLower128  = _mm_slli_epi32( blueLower128, 16 );

        __m128i rgbUpper128 = _mm_or_si128( redUpper128, _mm_or_si128(greenUpper128, blueUpper128) );
        __m128i rgbLower128 = _mm_or_si128( redLower128, _mm_or_si128(greenLower128, blueLower128) );

		tmp.mAsVector = _mm256_insertf128_si256( _mm256_setzero_si256(), rgbUpper128, 1 ); 
		tmp.mAsVector = _mm256_insertf128_si256( tmp.mAsVector, rgbLower128, 0 ); 

        return tmp;
    }

    __forceinline VFloat Red() const
    {
        VFloat tmp;
        tmp.mAsVector = mRed;
        return tmp;
    }

    __forceinline VFloat Green() const
    {
        VFloat tmp;
        tmp.mAsVector = mGreen;
        return tmp;
    }

    __forceinline VFloat Blue() const
    {
        VFloat tmp;
        tmp.mAsVector = mBlue;
        return tmp;
    }
    __forceinline VFloat3 operator[](int lane)
    {
        // "extraxt" one lane, "promote" to VFloat4.
        return VFloat3(
            VFloat(mX.m256_f32[lane]),
            VFloat(mY.m256_f32[lane]),
            VFloat(mZ.m256_f32[lane])
        );
    }

    __forceinline void Set( int lane, float red, float green, float blue )
    {
        mRed.m256_f32[lane]   = red;
        mGreen.m256_f32[lane] = green;
        mBlue.m256_f32[lane]  = blue;
    }

    __forceinline VFloat3 ShiftVectorLeftByOne()   { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorLeftByTwo()   { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorLeftByThree() { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorLeftByFour()  { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorLeftByFive()  { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorLeftBySix()   { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorLeftBySeven() { return VFloat3(0.0f); }

    __forceinline VFloat3 ShiftVectorRightByOne()   { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorRightByTwo()   { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorRightByThree() { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorRightByFour()  { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorRightByFive()  { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorRightBySix()   { return VFloat3(0.0f); }
    __forceinline VFloat3 ShiftVectorRightBySeven() { return VFloat3(0.0f); }

/* TODO: Double pump?  But, what about crossing 128-bit halves?
    __forceinline VFloat3 ShiftVectorLeftByOne()
    {
        VFloat3 tmp;
        tmp.mX = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mX), 4 ) );
        tmp.mY = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mY), 4 ) );
        tmp.mZ = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mZ), 4 ) );
        return tmp;
    }

    __forceinline VFloat3 ShiftVectorLeftByTwo()
    {
        VFloat3 tmp;
        tmp.mX = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mX), 8 ) );
        tmp.mY = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mY), 8 ) );
        tmp.mZ = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mZ), 8 ) );
        return tmp;
    }

    __forceinline VFloat3 ShiftVectorLeftByThree()
    {
        VFloat3 tmp;
        tmp.mX = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mX), 12 ) );
        tmp.mY = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mY), 12 ) );
        tmp.mZ = _mm256_castsi256_ps( _mm256_slli_si256( _mm256_castps_si256(mZ), 12 ) );
        return tmp;
    }

    __forceinline VFloat3 ShiftVectorRightByOne()
    {
        VFloat3 tmp;
        tmp.mX = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mX), 4 ) );
        tmp.mY = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mY), 4 ) );
        tmp.mZ = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mZ), 4 ) );
        return tmp;
    }

    __forceinline VFloat3 ShiftVectorRightByTwo()
    {
        VFloat3 tmp;
        tmp.mX = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mX), 8 ) );
        tmp.mY = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mY), 8 ) );
        tmp.mZ = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mZ), 8 ) );
        return tmp;
    }

    __forceinline VFloat3 ShiftVectorRightByThree()
    {
        VFloat3 tmp;
        tmp.mX = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mX), 12 ) );
        tmp.mY = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mY), 12 ) );
        tmp.mZ = _mm256_castsi256_ps( _mm256_srli_si256( _mm256_castps_si256(mZ), 12 ) );
        return tmp;
    }
*/
    __forceinline VFloat3 AndVector( VFloat v0 )
    {
        VFloat3 tmp;
        tmp.mX = _mm256_and_ps( mX, v0.mAsVector);
        tmp.mY = _mm256_and_ps( mY, v0.mAsVector);
        tmp.mZ = _mm256_and_ps( mZ, v0.mAsVector);
        return tmp;
    }

    __forceinline VFloat3 AndVector( VFloat3 v0 )
    {
        VFloat3 tmp;
        tmp.mX = _mm256_and_ps( mX, v0.mX );
        tmp.mY = _mm256_and_ps( mY, v0.mY );
        tmp.mZ = _mm256_and_ps( mZ, v0.mZ );
        return tmp;
    }

    __forceinline VFloat3 OrVector( VFloat v0 )
    {
        VFloat3 tmp;
        tmp.mX = _mm256_or_ps( mX, v0.mAsVector );
        tmp.mY = _mm256_or_ps( mY, v0.mAsVector );
        tmp.mZ = _mm256_or_ps( mZ, v0.mAsVector );
        return tmp;
    }

    __forceinline VFloat3 OrVector( VFloat3 v0 )
    {
        VFloat3 tmp;
        tmp.mX = _mm256_or_ps( mX, v0.mX );
        tmp.mY = _mm256_or_ps( mY, v0.mY );
        tmp.mZ = _mm256_or_ps( mZ, v0.mZ );
        return tmp;
    }
/*
    __forceinline VFloat3 Shuffle( VFloat3 v0, int val )
    {
        VFloat3 tmp;
        tmp.mX = _mm256_shuffle_ps( mX, v0.mX, val );
        tmp.mY = _mm256_shuffle_ps( mY, v0.mY, val );
        tmp.mZ = _mm256_shuffle_ps( mZ, v0.mZ, val );
        return tmp;
    }
*/
    VFloat3 Step( float threshold )
    {
        __m256 vThresh = _mm256_set1_ps( threshold );
        VFloat3 tmp;
        tmp.mX = _mm256_and_ps( _mm256_cmp_ps( mX, vThresh, _CMP_GT_OQ ), mX );
        tmp.mY = _mm256_and_ps( _mm256_cmp_ps( mY, vThresh, _CMP_GT_OQ ), mY );
        tmp.mZ = _mm256_and_ps( _mm256_cmp_ps( mZ, vThresh, _CMP_GT_OQ ), mZ );
        return tmp;
    }

    __forceinline void SetHorizontalSumByFours( int lane, VFloat3 source )
    {
        // TODO: Use shuffles instead of these awkward accesses.
        mX.m256_f32[lane]   = source.mX.m256_f32[0] + source.mX.m256_f32[1] + source.mX.m256_f32[2] + source.mX.m256_f32[3];
        mX.m256_f32[lane+1] = source.mX.m256_f32[4] + source.mX.m256_f32[5] + source.mX.m256_f32[6] + source.mX.m256_f32[7];

        mY.m256_f32[lane]   = source.mY.m256_f32[0] + source.mY.m256_f32[1] + source.mY.m256_f32[2] + source.mY.m256_f32[3];
        mY.m256_f32[lane+1] = source.mY.m256_f32[4] + source.mY.m256_f32[5] + source.mY.m256_f32[6] + source.mY.m256_f32[7];

        mZ.m256_f32[lane]   = source.mZ.m256_f32[0] + source.mZ.m256_f32[1] + source.mZ.m256_f32[2] + source.mZ.m256_f32[3];
        mZ.m256_f32[lane+1] = source.mZ.m256_f32[4] + source.mZ.m256_f32[5] + source.mZ.m256_f32[6] + source.mZ.m256_f32[7];
    }
};


#define VECTOR_LENGTH 8

__forceinline VFloat Min( const VFloat &v0, const VFloat &v1 ) 
{
    VFloat tmp;
    tmp.mAsVector = _mm256_min_ps( v0.mAsVector, v1.mAsVector );
    return tmp;
}

__forceinline VFloat Max( const VFloat &v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm256_max_ps( v0.mAsVector, v1.mAsVector );
    return tmp;
}
/*
__forceinline VInt Min( const VInt &v0, const VInt &v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm256_min_epi32( v0.mAsVector, v1.mAsVector );
    return tmp;
}

__forceinline VInt Max( const VInt &v0, const VInt &v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm256_max_epi32( v0.mAsVector, v1.mAsVector );
    return tmp;
}
*/
__forceinline void Transpose( VFloat &v0, VFloat &v1, VFloat &v2, VFloat &v3 )
{
/*
    Start with:
    R0 G0 B0 A0 R1 G1 B1 A1
    R2 G2 B2 A2 R3 G3 B3 A3
    R4 G4 B4 A4 R5 G5 B5 A5
    R6 G6 B6 A6 R7 G7 B7 A7

    End with
    R0 R1 R2 R3 R4 R5 R6 R7
    G0 G1 G2 G3 G4 G5 G6 G7
    B0 B1 B2 B3 B4 B5 B6 B7
    A0 A1 A2 A3 A4 A5 A6 A7

*/
    __m256 tmp0, tmp1, tmp2, tmp3;

    float *pv[4]   = { v0.mAsVector.m256_f32, v1.mAsVector.m256_f32, v2.mAsVector.m256_f32, v3.mAsVector.m256_f32 };
    float *ptmp[4] = {         tmp0.m256_f32,         tmp1.m256_f32,         tmp2.m256_f32,         tmp3.m256_f32 };

    for( int ii=0; ii<4; ii++ )
    {
        ptmp[ii][0] = pv[0][ii];
        ptmp[ii][1] = pv[0][ii+4];
        ptmp[ii][2] = pv[1][ii];
        ptmp[ii][3] = pv[1][ii+4];
        ptmp[ii][4] = pv[2][ii];
        ptmp[ii][5] = pv[2][ii+4];
        ptmp[ii][6] = pv[3][ii];
        ptmp[ii][7] = pv[3][ii+4];
    }

    v0.mAsVector = tmp0;
    v1.mAsVector = tmp1;
    v2.mAsVector = tmp2;
    v3.mAsVector = tmp3;
}
/*
__forceinline void Transpose( VFloat4 &v0 )
{
    // Four RGBARGBA in.  RRRRRRRR, GGGGGGGG, BBBBBBBB, AAAAAAAA out.
    __m256 tmp0   = _mm256_shuffle_ps(v0.mX, v0.mY, 0x44);
    __m256 tmp2   = _mm256_shuffle_ps(v0.mX, v0.mY, 0xEE);
    __m256 tmp1   = _mm256_shuffle_ps(v0.mZ, v0.mW, 0x44);
    __m256 tmp3   = _mm256_shuffle_ps(v0.mZ, v0.mW, 0xEE);

    v0.mX = _mm256_shuffle_ps(tmp0, tmp1, 0x88);
    v0.mY = _mm256_shuffle_ps(tmp0, tmp1, 0xDD);
    v0.mZ = _mm256_shuffle_ps(tmp2, tmp3, 0x88);
    v0.mW = _mm256_shuffle_ps(tmp2, tmp3, 0xDD);
}
*/
/*
__forceinline float Dot3( VFloat v0, VFloat v1 )
{
    __m256 tmp1 = _mm256_mul_ps( v0.mAsVector, v1.mAsVector );
    return tmp1.m256_f32[0] + tmp1.m256_f32[1] + tmp1.m256_f32[2];
}
*/
__forceinline VFloat Dot3( const VFloat3 &v0, const VFloat &v1 )
{
    VFloat tmp;
    __m256 tmpX = _mm256_mul_ps( v0.mX, v1.mAsVector );
    __m256 tmpY = _mm256_mul_ps( v0.mY, v1.mAsVector );
    __m256 tmpZ = _mm256_mul_ps( v0.mZ, v1.mAsVector );

    __m256 sum0 = _mm256_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm256_add_ps( sum0, tmpZ );
    return tmp;
}

__forceinline VFloat Dot3( const VFloat3 &v0, const VFloat3 &v1 )
{
    VFloat tmp;
    __m256 tmpX = _mm256_mul_ps( v0.mX, v1.mX );
    __m256 tmpY = _mm256_mul_ps( v0.mY, v1.mY );
    __m256 tmpZ = _mm256_mul_ps( v0.mZ, v1.mZ );

    __m256 sum0 = _mm256_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm256_add_ps( sum0, tmpZ );
    return tmp;
}
/*
__forceinline VFloat Dot3( const VFloat4 &v0, const VFloat &v1 )
{
    VFloat tmp;
    __m256 tmpX = _mm256_mul_ps( v0.mX, v1.mAsVector );
    __m256 tmpY = _mm256_mul_ps( v0.mY, v1.mAsVector );
    __m256 tmpZ = _mm256_mul_ps( v0.mZ, v1.mAsVector );

    __m256 sum0 = _mm256_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm256_add_ps( sum0, tmpZ );
    return tmp;
}

__forceinline VFloat Dot3( const VFloat4 &v0, const VFloat3 &v1 )
{
    VFloat tmp;
    __m256 tmpX = _mm256_mul_ps( v0.mX, v1.mX );
    __m256 tmpY = _mm256_mul_ps( v0.mY, v1.mY );
    __m256 tmpZ = _mm256_mul_ps( v0.mZ, v1.mZ );

    __m256 sum0 = _mm256_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm256_add_ps( sum0, tmpZ );
    return tmp;
}
__forceinline VFloat Dot3( const VFloat4 &v0, const VFloat4 &v1 )
{
    VFloat tmp;
    __m256 tmpX = _mm256_mul_ps( v0.mX, v1.mX );
    __m256 tmpY = _mm256_mul_ps( v0.mY, v1.mY );
    __m256 tmpZ = _mm256_mul_ps( v0.mZ, v1.mZ );

    __m256 sum0 = _mm256_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm256_add_ps( sum0, tmpZ );
    return tmp;
}
*/

__forceinline VFloat Dot( const VFloat3 &v0, const VFloat3 &v1 )
{
    VFloat tmp;
    __m256 tmpX = _mm256_mul_ps( v0.mX, v1.mX );
    __m256 tmpY = _mm256_mul_ps( v0.mY, v1.mY );
    __m256 tmpZ = _mm256_mul_ps( v0.mZ, v1.mZ );

    __m256 sum = _mm256_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm256_add_ps( sum, tmpZ );
    return tmp;
}

__forceinline VFloat3 Min( float val, const VFloat3 &v0 )
{
    __m256 xx = _mm256_set1_ps( val );
    VFloat3 tmp;
    tmp.mX = _mm256_min_ps( xx, v0.mX );
    tmp.mY = _mm256_min_ps( xx, v0.mY );
    tmp.mZ = _mm256_min_ps( xx, v0.mZ );
    return tmp;
}

__forceinline VFloat3 rsqrt( const VFloat3 &src )
{
    VFloat3 tmp;
    tmp.mX = _mm256_rsqrt_ps( src.mX );
    tmp.mY = _mm256_rsqrt_ps( src.mY );
    tmp.mZ = _mm256_rsqrt_ps( src.mZ );
    return tmp;
}

__forceinline VFloat3 sqrt( const VFloat3 &src )
{
    VFloat3 tmp = rsqrt(src);
    return src * tmp;
}

//    X0.lower4=X0.lower4+X0.upper4 and X0.upper4 = x2.lower4+x2.upper4 and
//    X1.lower4=X1.lower4+X0.upper4 and X1.upper4 = x3.lower4+x3.upper4

__forceinline VFloat3 MergeLowerAndUpperFour( const VFloat3 &v0, const VFloat3 &v1 )
{
    VFloat3 tmp;

    // Copy.  Swap upper and lower halves. Add to original.  Extract lower half.  Repeat for second vector.  Insert into upper and lower half of tmp.
    tmp.mX = _mm256_insertf128_ps( _mm256_setzero_ps(), _mm_add_ps( _mm256_extractf128_ps( v0.mX, 0 ), _mm256_extractf128_ps( v0.mX, 1 ) ), 0 );
    tmp.mX = _mm256_insertf128_ps(              tmp.mX, _mm_add_ps( _mm256_extractf128_ps( v1.mX, 0 ), _mm256_extractf128_ps( v1.mX, 1 ) ), 1 );

    tmp.mY = _mm256_insertf128_ps( _mm256_setzero_ps(), _mm_add_ps( _mm256_extractf128_ps( v0.mY, 0 ), _mm256_extractf128_ps( v0.mY, 1 ) ), 0 );
    tmp.mY = _mm256_insertf128_ps(              tmp.mY, _mm_add_ps( _mm256_extractf128_ps( v1.mY, 0 ), _mm256_extractf128_ps( v1.mY, 1 ) ), 1 );

    tmp.mZ = _mm256_insertf128_ps( _mm256_setzero_ps(), _mm_add_ps( _mm256_extractf128_ps( v0.mZ, 0 ), _mm256_extractf128_ps( v0.mZ, 1 ) ), 0 );
    tmp.mZ = _mm256_insertf128_ps(              tmp.mZ, _mm_add_ps( _mm256_extractf128_ps( v1.mZ, 0 ), _mm256_extractf128_ps( v1.mZ, 1 ) ), 1 );

    return tmp;
}


__forceinline VFloat3 ExpandPixelByFour( const VFloat3 &src, int lane )
{
    // Expand src[lane] and src[lane+1] to four lanes each, and put them in the lower and upper halves of dest, respectively
    VFloat3 tmp;

    tmp.mX = _mm256_insertf128_ps( _mm256_setzero_ps(), _mm_set1_ps( src.mX.m256_f32[lane] ),   0 );
    tmp.mX = _mm256_insertf128_ps(              tmp.mX, _mm_set1_ps( src.mX.m256_f32[lane+1] ), 1 );

    tmp.mY = _mm256_insertf128_ps( _mm256_setzero_ps(), _mm_set1_ps( src.mY.m256_f32[lane] ),   0 );
    tmp.mY = _mm256_insertf128_ps(              tmp.mY, _mm_set1_ps( src.mY.m256_f32[lane+1] ), 1 );

    tmp.mZ = _mm256_insertf128_ps( _mm256_setzero_ps(), _mm_set1_ps( src.mZ.m256_f32[lane] ),   0 );
    tmp.mZ = _mm256_insertf128_ps(              tmp.mZ, _mm_set1_ps( src.mZ.m256_f32[lane+1] ), 1 );

    return tmp;
}

void ExpandByFour( VFloat3 *pOut, VFloat3 *pIn, int count )
{
    float f0, f1;
    int ii, jj;
    for( ii=0; ii<count; ii+=VECTOR_LENGTH )
    {
        for( jj=0; jj<VECTOR_LENGTH; jj+=2 )
        {
            f0 = pIn->mX.m256_f32[jj];
            f1 = pIn->mX.m256_f32[jj+1];
            pOut->mX = _mm256_set_ps( f1, f1, f1, f1, f0, f0, f0, f0 );
            f0 = pIn->mY.m256_f32[jj];
            f1 = pIn->mY.m256_f32[jj+1];
            pOut->mY = _mm256_set_ps( f1, f1, f1, f1, f0, f0, f0, f0 );
            f0 = pIn->mZ.m256_f32[jj];
            f1 = pIn->mZ.m256_f32[jj+1];
            pOut->mZ = _mm256_set_ps( f1, f1, f1, f1, f0, f0, f0, f0 );

            pOut++;
        }
        pIn++;
    }
}

void ShiftAndExpandByFour( VFloat3 *pOut, VFloat3 *pIn, int count )
{
    float f0, f1;
    int ii, jj;
    for( ii=0; ii<count; ii+=VECTOR_LENGTH )
    {
        for( jj=1; jj<(VECTOR_LENGTH-1); jj+=2 )
        {
            f0 = pIn->mX.m256_f32[jj];
            f1 = pIn->mX.m256_f32[jj+1];
            pOut->mX = _mm256_set_ps( f1, f1, f1, f1, f0, f0, f0, f0 );
            f0 = pIn->mY.m256_f32[jj];
            f1 = pIn->mY.m256_f32[jj+1];
            pOut->mY = _mm256_set_ps( f1, f1, f1, f1, f0, f0, f0, f0 );
            f0 = pIn->mZ.m256_f32[jj];
            f1 = pIn->mZ.m256_f32[jj+1];
            pOut->mZ = _mm256_set_ps( f1, f1, f1, f1, f0, f0, f0, f0 );

            pOut++;
        }

        // The last lane of this vector = first lane of next vector.
        f0 = pIn->mX.m256_f32[7];
        f1 = pIn[1].mX.m256_f32[0];
        pOut->mX = _mm256_set_ps( f1, f1, f1, f1, f0, f0, f0, f0 );
        f0 = pIn->mY.m256_f32[7];
        f1 = pIn[1].mY.m256_f32[0];
        pOut->mY = _mm256_set_ps( f1, f1, f1, f1, f0, f0, f0, f0 );
        f0 = pIn->mZ.m256_f32[7];
        f1 = pIn[1].mZ.m256_f32[0];
        pOut->mZ = _mm256_set_ps( f1, f1, f1, f1, f0, f0, f0, f0 );

        // This completes this output vector
        pOut++;

        pIn++;
    }
}

__forceinline VFloat3 UnpackRGBA( const VInt &packedRGBA )
{
	const __m256 redMask   = _mm256_castsi256_ps( _mm256_set1_epi32( 0x000000FF ) ); // Cast to float because AVX doesn't have int bitwise ops
	const __m256 greenMask = _mm256_castsi256_ps( _mm256_set1_epi32( 0x0000FF00 ) );
	const __m256 blueMask  = _mm256_castsi256_ps( _mm256_set1_epi32( 0x00FF0000 ) );
	const __m256 oneOver0x100   = _mm256_set1_ps( 1.0f/0x100 );
	const __m256 oneOver0x10000 = _mm256_set1_ps( 1.0f/0x10000 );

	__m256 rgba = _mm256_castsi256_ps( packedRGBA.mAsVector); // Cast to float so we can do bitwise ops

    VFloat3 unpackedRGBA;

	// Mask off red bits, then cast from float to int, then convert from int to float (yuck.  I know)
	unpackedRGBA.mRed   = _mm256_and_ps( rgba, redMask );
    unpackedRGBA.mRed   = _mm256_cvtepi32_ps( _mm256_castps_si256( unpackedRGBA.mRed ) );

	unpackedRGBA.mGreen = _mm256_and_ps( rgba, greenMask ); // Mask out green bits.  mGreen is now int as float
	unpackedRGBA.mGreen = _mm256_cvtepi32_ps( _mm256_castps_si256( unpackedRGBA.mGreen ) ); // convert to actual float
	unpackedRGBA.mGreen = _mm256_mul_ps( unpackedRGBA.mGreen, oneOver0x100 ); // "divide" to convert from 0xFF00 space to 0xFF space.

	unpackedRGBA.mBlue  = _mm256_and_ps( rgba, blueMask );
	unpackedRGBA.mBlue  = _mm256_cvtepi32_ps( _mm256_castps_si256( unpackedRGBA.mBlue ) );
	unpackedRGBA.mBlue  = _mm256_mul_ps( unpackedRGBA.mBlue, oneOver0x10000 );

	return unpackedRGBA;
}

__forceinline VInt PackRGBA( const VFloat3 &unpackedRGBA )
{
	const __m256 greenScale = _mm256_set1_ps( 0x100 );
	const __m256 blueScale  = _mm256_set1_ps( 0x10000 );
	const __m256 greenMask  = _mm256_castsi256_ps( _mm256_cvtps_epi32(_mm256_set1_ps( 0xFF00 ) ) );
	const __m256 blueMask   = _mm256_castsi256_ps( _mm256_cvtps_epi32(_mm256_set1_ps( 0xFF0000 ) ) );

	__m256 red   = _mm256_castsi256_ps( _mm256_cvtps_epi32( unpackedRGBA.mRed ) );
    __m256 green = _mm256_castsi256_ps( _mm256_cvtps_epi32( _mm256_mul_ps( unpackedRGBA.mGreen, greenScale ) ) );
    __m256 blue  = _mm256_castsi256_ps( _mm256_cvtps_epi32( _mm256_mul_ps( unpackedRGBA.mBlue,  blueScale ) ) );

    VInt tmp;
    tmp.mAsVector = _mm256_castps_si256( _mm256_or_ps( red, _mm256_or_ps( _mm256_and_ps( green, greenMask ), _mm256_and_ps( blue, blueMask ) ) ) );
    return tmp;
}

VFloat operator-( float v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm256_sub_ps( _mm256_set1_ps(v0), v1.mAsVector );
    return tmp;
}

VFloat Max( float v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm256_max_ps( _mm256_set1_ps(v0), v1.mAsVector );
    return tmp;
}
