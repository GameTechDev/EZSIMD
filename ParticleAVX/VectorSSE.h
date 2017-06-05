/////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or imlied.
// See the License for the specific language governing permissions and
// limitations under the License.
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

// ******************************************************************
class VFloat
{
public:
    __m128 mAsVector;

public:
    VFloat(){};
    ~VFloat(){};

    explicit VFloat( const float val )
    {
        mAsVector = _mm_set1_ps( val );
    }

    explicit VFloat( const __m128 &v0 )
    {
        mAsVector = v0;
    }

    explicit VFloat( const float v0, const float v1, const float v2, const float v3 )
    {
        mAsVector = _mm_set_ps( v0, v1, v2, v3 );
    }

    __forceinline VFloat operator+( const VFloat &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_add_ps( mAsVector, val.mAsVector );
        return tmp;
    }
    __forceinline VFloat operator+( const float val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_add_ps( mAsVector, _mm_set1_ps(val) );
        return tmp;
    }
/*
    VInt asVInt()
    {
        VInt tmp;
        tmp.mAsVector = _mm_castps_si128( mAsVector );
        return tmp;
    }
*/

    __forceinline VFloat operator-( const VFloat &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_sub_ps( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat operator*( const VFloat &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_mul_ps( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat operator*( const float val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_mul_ps( mAsVector, _mm_set1_ps( val ) );
        return tmp;
    }

    __forceinline VFloat operator*=( const float val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_mul_ps( mAsVector, _mm_set1_ps( val ) );
        return tmp;
    }

    __forceinline VFloat operator/( const VFloat &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_div_ps( mAsVector, val.mAsVector );
        return tmp;
    }
    __forceinline VFloat operator/( const float val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_div_ps( mAsVector, _mm_set1_ps( val ) );
        return tmp;
    }
    __forceinline VFloat operator[](int lane)
    {
        // "extraxt" one lane, "promote" to VFloat3.
        return VFloat( VFloat(mAsVector.m128_f32[lane]) );
    }
    __forceinline VFloat operator&( const VFloat &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_and_ps( mAsVector, val.mAsVector );
        return tmp;
    }
    __forceinline VFloat operator&( const float &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_and_ps( mAsVector, _mm_set1_ps(val) );
        return tmp;
    }

    __forceinline VFloat operator&=( const VFloat &val ) const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_and_ps( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat Reciprocal()
    {
        VFloat tmp;
        tmp.mAsVector = _mm_rcp_ps( mAsVector );
        return tmp;
    }

    __forceinline float HorizontalSum() const
    {
        return mAsVector.m128_f32[0] + mAsVector.m128_f32[1] + mAsVector.m128_f32[2] + mAsVector.m128_f32[3];
    }

    __forceinline VFloat ShiftVectorLeftOne()
    {
        VFloat tmp;
        tmp.mAsVector = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mAsVector), 4 ) );
        return tmp;
    }

    __forceinline VFloat ShiftVectorLeftTwo()
    {
        VFloat tmp;
        tmp.mAsVector = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mAsVector), 8 ) );
        return tmp;
    }

    __forceinline VFloat ShiftVectorLeftThree()
    {
        VFloat tmp;
        tmp.mAsVector = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mAsVector), 12 ) );
        return tmp;
    }

    __forceinline VFloat ShiftVectorRightByOne()
    {
        VFloat tmp;
        tmp.mAsVector = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mAsVector), 4 ) );
        return tmp;
    }

    __forceinline VFloat ShiftVectorRightByTwo()
    {
        VFloat tmp;
        tmp.mAsVector = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mAsVector), 8 ) );
        return tmp;
    }

    __forceinline VFloat ShiftVectorRightByThree()
    {
        VFloat tmp;
        tmp.mAsVector = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mAsVector), 12 ) );
        return tmp;
    }
/*
    __forceinline VFloat Shuffle( VFloat v0, int val )
    {
        VFloat tmp;
        tmp.mAsVector = _mm_shuffle_ps( mAsVector, v0.mAsVector, val );
        return tmp;
    }
*/
};

#pragma warning( disable:4201 )
// ******************************************************************
class VFloat4
{
public:
    union {
        struct {
            __m128 mRed;
            __m128 mGreen;
            __m128 mBlue;
            __m128 mAlpha;
        };
        struct {
            __m128 mX;
            __m128 mY;
            __m128 mZ;
            __m128 mW;
        };
        struct {
            VFloat x;
            VFloat y;
            VFloat z;
            VFloat w;
        };
    };

public:
    VFloat4(){};
    ~VFloat4(){};

    explicit VFloat4( const float val )
    {
        mX = mY = mZ = mW = _mm_set1_ps( val );
    }

    explicit VFloat4( const float xx, const float yy, const float zz, const float ww )
    {
        mX = _mm_set1_ps( xx );
        mY = _mm_set1_ps( yy );
        mZ = _mm_set1_ps( zz );
        mW = _mm_set1_ps( ww );
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
        tmp.mX = _mm_add_ps( mX, val.mX );
        tmp.mY = _mm_add_ps( mY, val.mY );
        tmp.mZ = _mm_add_ps( mZ, val.mZ );
        tmp.mW = _mm_add_ps( mW, val.mW );
        return tmp;
    }

    __forceinline const VFloat4 operator-( const VFloat4 &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm_sub_ps( mX, val.mX );
        tmp.mY = _mm_sub_ps( mY, val.mY );
        tmp.mZ = _mm_sub_ps( mZ, val.mZ );
        tmp.mW = _mm_sub_ps( mW, val.mW );
        return tmp;
    }

    __forceinline const VFloat4 operator*( const VFloat4 &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm_mul_ps( mX, val.mX );
        tmp.mY = _mm_mul_ps( mY, val.mY );
        tmp.mZ = _mm_mul_ps( mZ, val.mZ );
        tmp.mW = _mm_mul_ps( mW, val.mW );
        return tmp;
    }

    __forceinline const VFloat4 operator*( float val ) const
    {
        __m128 vv = _mm_set1_ps( val );
        VFloat4 tmp;
        tmp.mX = _mm_mul_ps( mX, vv );
        tmp.mY = _mm_mul_ps( mY, vv );
        tmp.mZ = _mm_mul_ps( mZ, vv );
        tmp.mW = _mm_mul_ps( mW, vv );
        return tmp;
    }

    __forceinline const VFloat4 operator+( const VFloat &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm_add_ps( mX, val.mAsVector );
        tmp.mY = _mm_add_ps( mY, val.mAsVector );
        tmp.mZ = _mm_add_ps( mZ, val.mAsVector );
        tmp.mW = _mm_add_ps( mW, val.mAsVector );
        return tmp;
    }

    __forceinline const VFloat4 operator-( const VFloat &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm_sub_ps( mX, val.mAsVector );
        tmp.mY = _mm_sub_ps( mY, val.mAsVector );
        tmp.mZ = _mm_sub_ps( mZ, val.mAsVector );
        tmp.mW = _mm_sub_ps( mW, val.mAsVector );
        return tmp;
    }

    __forceinline const VFloat4 operator*( const VFloat &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm_mul_ps( mX, val.mAsVector );
        tmp.mY = _mm_mul_ps( mY, val.mAsVector );
        tmp.mZ = _mm_mul_ps( mZ, val.mAsVector );
        tmp.mW = _mm_mul_ps( mW, val.mAsVector );
        return tmp;
    }

    __forceinline const VFloat4 operator/( const VFloat4 &val ) const
    {
        VFloat4 tmp;
        tmp.mX = _mm_div_ps( mX, val.mX );
        tmp.mY = _mm_div_ps( mY, val.mY );
        tmp.mZ = _mm_div_ps( mZ, val.mZ );
        tmp.mW = _mm_div_ps( mW, val.mW );
        return tmp;
    }

    __forceinline const VFloat4 operator/( const VFloat &val ) const
    {
        VFloat4 tmp;
        __m128 inverse = _mm_rcp_ps( val.mAsVector );

        tmp.mX = _mm_mul_ps( mX, inverse );
        tmp.mY = _mm_mul_ps( mY, inverse );
        tmp.mZ = _mm_mul_ps( mZ, inverse );
        tmp.mW = _mm_mul_ps( mW, inverse );
        return tmp;
    }

    // TODO: Which way do we want to do this?  SOA or AOS?
    // For now, keep with the "SOA is behind the scenes" theme, and add the vectors together
    // instead of adding each of them horizontally.
    __forceinline VFloat HorizontalSum() const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_add_ps( _mm_add_ps( mRed, mGreen ), _mm_add_ps( mBlue, mAlpha ) );
        return tmp;
    }
/*
    // Yuck.  What should this do?
    __forceinline VFloat4 operator[](int lane)
    {
        // "extraxt" one lane, "promote" to VFloat4.
        return VFloat4(
            VFloat(mX.m128_f32[lane]),
            VFloat(mY.m128_f32[lane]),
            VFloat(mZ.m128_f32[lane]),
            VFloat(mW.m128_f32[lane])
        );
    }
*/
};

// ******************************************************************
class VInt
{
public:
    __m128i mAsVector;

public:
    VInt(){};
    ~VInt(){};

    explicit VInt( const __m128i val )
    {
        mAsVector = val;
    }

    explicit VInt( const int val )
    {
        mAsVector = _mm_set1_epi32( val );
    }

    explicit VInt( const int v0, const int v1, const int v2, const int v3 )
    {
        mAsVector = _mm_set_epi32( v0, v1, v2, v3 );
    }

    explicit VInt( const VFloat &v0 )
    {
        // mAsVector = _mm_castps_si128( v0.mAsVector );
        mAsVector = _mm_cvtps_epi32( v0.mAsVector );
    }

    __forceinline VInt operator+( const VInt &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_add_epi32( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VInt operator+( const int &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_add_epi32( mAsVector, _mm_set1_epi32(val) );
        return tmp;
    }

    __forceinline VInt operator-( const VInt &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_sub_epi32( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VInt operator*( const VInt &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_mullo_epi32( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VInt operator*( int val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_mullo_epi32( mAsVector, _mm_set1_epi32(val) );
        return tmp;
    }

//    VInt operator/( VInt val )
//    {
//        VInt tmp;
//        tmp.mAsVector = _mm_div_epi32( mAsVector, val.mAsVector );
//    }

    __forceinline int operator[](int lane)
    {
        // "extraxt" one lane, "promote" to VFloat3.
        return mAsVector.m128i_i32[lane];
    }

    __forceinline VInt UnpackHi16( const VInt &src ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_unpackhi_epi16( src.mAsVector, _mm_setzero_si128() );
        return tmp;
    }
    __forceinline VInt UnpackLow16( const VInt &src ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_unpacklo_epi16( src.mAsVector, _mm_setzero_si128() );
        return tmp;
    }
    __forceinline VInt operator&( const VInt &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_and_si128( mAsVector, val.mAsVector );
        return tmp;
    }
    __forceinline VInt operator&( const int &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_and_si128( mAsVector, _mm_set1_epi32(val) );
        return tmp;
    }
    __forceinline VInt operator|( const VInt &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_or_si128( mAsVector, val.mAsVector );
        return tmp;
    }
    __forceinline VInt operator<<( const int count ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_slli_epi32( mAsVector, count );
        return tmp;
    }
    __forceinline VFloat InterpretAsVFloat() const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_castsi128_ps( mAsVector );
        return tmp;
    }
};


// ******************************************************************
class VFloat3
{
public:
    union {
        struct {
            __m128 mRed;
            __m128 mGreen;
            __m128 mBlue;
        };
        struct {
            __m128 mX;
            __m128 mY;
            __m128 mZ;
        };
        struct {
            VFloat x;
            VFloat y;
            VFloat z;
        };
    };

public:
    VFloat3(){};
    ~VFloat3(){};

    explicit VFloat3( const float val )
    {
        mX = mY = mZ = _mm_set1_ps( val );
    }

    explicit VFloat3( const VFloat &val )
    {
        mX = mY = mZ = val.mAsVector;
    }

    explicit VFloat3( const float xx, const float yy, const float zz )
    {
        mX = _mm_set1_ps( xx );
        mY = _mm_set1_ps( yy );
        mZ = _mm_set1_ps( zz );
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
        tmp.mX = _mm_add_ps( mX, val.mX );
        tmp.mY = _mm_add_ps( mY, val.mY );
        tmp.mZ = _mm_add_ps( mZ, val.mZ );
        return tmp;
    }

    __forceinline VFloat3 operator-( const VFloat3 &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm_sub_ps( mX, val.mX );
        tmp.mY = _mm_sub_ps( mY, val.mY );
        tmp.mZ = _mm_sub_ps( mZ, val.mZ );
        return tmp;
    }

    __forceinline VFloat3 operator*( const VFloat3 &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm_mul_ps( mX, val.mX );
        tmp.mY = _mm_mul_ps( mY, val.mY );
        tmp.mZ = _mm_mul_ps( mZ, val.mZ );
        return tmp;
    }

    __forceinline VFloat3 operator+( const VFloat &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm_add_ps( mX, val.mAsVector );
        tmp.mY = _mm_add_ps( mY, val.mAsVector );
        tmp.mZ = _mm_add_ps( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat3 operator-( const VFloat &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm_sub_ps( mX, val.mAsVector );
        tmp.mY = _mm_sub_ps( mY, val.mAsVector );
        tmp.mZ = _mm_sub_ps( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat3 operator*( const VFloat &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm_mul_ps( mX, val.mAsVector );
        tmp.mY = _mm_mul_ps( mY, val.mAsVector );
        tmp.mZ = _mm_mul_ps( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline VFloat3 operator/( const VFloat3 &val ) const
    {
        VFloat3 tmp;
        tmp.mX = _mm_div_ps( mX, val.mX );
        tmp.mY = _mm_div_ps( mY, val.mY );
        tmp.mZ = _mm_div_ps( mZ, val.mZ );
        return tmp;
    }

    __forceinline VFloat3 operator+( const float val ) const
    {
        VFloat3 tmp;
        __m128 valVec = _mm_set1_ps(val);
        tmp.mX = _mm_add_ps( mX, valVec );
        tmp.mY = _mm_add_ps( mY, valVec );
        tmp.mZ = _mm_add_ps( mZ, valVec );
        return tmp;
    }

    __forceinline VFloat3 operator-( const float val ) const
    {
        VFloat3 tmp;
        __m128 valVec = _mm_set1_ps(val);
        tmp.mX = _mm_sub_ps( mX, valVec );
        tmp.mY = _mm_sub_ps( mY, valVec );
        tmp.mZ = _mm_sub_ps( mZ, valVec );
        return tmp;
    }

    __forceinline VFloat3 operator*( const float val ) const
    {
        VFloat3 tmp;
        __m128 valVec = _mm_set1_ps(val);
        tmp.mX = _mm_mul_ps( mX, valVec );
        tmp.mY = _mm_mul_ps( mY, valVec );
        tmp.mZ = _mm_mul_ps( mZ, valVec );
        return tmp;
    }

    __forceinline VFloat3 operator/( const float val ) const
    {
        VFloat3 tmp;
        __m128 valVec = _mm_set1_ps(val);
        tmp.mX = _mm_div_ps( mX, valVec );
        tmp.mY = _mm_div_ps( mY, valVec );
        tmp.mZ = _mm_div_ps( mZ, valVec );
        return tmp;
    }

    // TODO: Which way do we want to do this?  SOA or AOS?
    // For now, keep with the "SOA is behind the scenes" theme, and add the vectors together
    // instead of adding each of them horizontally.
    __forceinline VFloat HorizontalSum() const
    {
        VFloat tmp;
        tmp.mAsVector = _mm_add_ps( _mm_add_ps( mRed, mGreen ),  mBlue );
        return tmp;
    }

/*
    __forceinline VInt AsRgbaVInt() const
    {
        VInt tmp;
        __m128i red   = _mm_cvtps_epi32( mRed );
        __m128i green = _mm_slli_epi32( _mm_cvtps_epi32( mGreen ), 8 );
        __m128i blue  = _mm_slli_epi32( _mm_cvtps_epi32( mBlue ), 16 );
        tmp.mAsVector = _mm_or_si128( red, _mm_or_si128( green, blue ) );
        return tmp;
    }
*/
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

    // Yuck.  What should this do?  Should we have a different method for what this is currently doing?
    __forceinline VFloat3 operator[](int lane)
    {
        // "extraxt" one lane, "promote" to VFloat3.
        return VFloat3(
            VFloat(mX.m128_f32[lane]),
            VFloat(mY.m128_f32[lane]),
            VFloat(mZ.m128_f32[lane])
        );
    }

    __forceinline void Set( int lane, float red, float green, float blue )
    {
        mRed.m128_f32[lane]   = red;
        mGreen.m128_f32[lane] = green;
        mBlue.m128_f32[lane]  = blue;
    }

    __forceinline VFloat3 ShiftVectorLeftByOne()
    {
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mX), 4 ) );
        tmp.mY = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mY), 4 ) );
        tmp.mZ = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mZ), 4 ) );
        return tmp;
    }

    __forceinline VFloat3 ShiftVectorLeftByTwo()
    {
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mX), 8 ) );
        tmp.mY = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mY), 8 ) );
        tmp.mZ = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mZ), 8 ) );
        return tmp;
    }

    __forceinline VFloat3 ShiftVectorLeftByThree()
    {
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mX), 12 ) );
        tmp.mY = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mY), 12 ) );
        tmp.mZ = _mm_castsi128_ps( _mm_slli_si128( _mm_castps_si128(mZ), 12 ) );
        return tmp;
    }

    __forceinline VFloat3 ShiftVectorRightByOne()
    {
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mX), 4 ) );
        tmp.mY = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mY), 4 ) );
        tmp.mZ = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mZ), 4 ) );
        return tmp;
    }

    __forceinline VFloat3 ShiftVectorRightByTwo()
    {
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mX), 8 ) );
        tmp.mY = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mY), 8 ) );
        tmp.mZ = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mZ), 8 ) );
        return tmp;
    }

    __forceinline VFloat3 ShiftVectorRightByThree()
    {
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mX), 12 ) );
        tmp.mY = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mY), 12 ) );
        tmp.mZ = _mm_castsi128_ps( _mm_srli_si128( _mm_castps_si128(mZ), 12 ) );
        return tmp;
    }
/*
    __forceinline VFloat3 AndVector( VFloat v0 )
    {
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mX), _mm_castps_si128(v0.mAsVector) ) );
        tmp.mY = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mY), _mm_castps_si128(v0.mAsVector) ) );
        tmp.mZ = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mZ), _mm_castps_si128(v0.mAsVector) ) );
        return tmp;
    }

    __forceinline VFloat3 AndVector( VFloat3 v0 )
    {
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mX), _mm_castps_si128(v0.mX) ) );
        tmp.mY = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mY), _mm_castps_si128(v0.mY) ) );
        tmp.mZ = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mZ), _mm_castps_si128(v0.mZ) ) );
        return tmp;
    }

    __forceinline VFloat3 OrVector( VFloat v0 )
    {
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mX), _mm_castps_si128(v0.mAsVector) ) );
        tmp.mY = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mY), _mm_castps_si128(v0.mAsVector) ) );
        tmp.mZ = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mZ), _mm_castps_si128(v0.mAsVector) ) );
        return tmp;
    }

    __forceinline VFloat3 OrVector( VFloat3 v0 )
    {
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mX), _mm_castps_si128(v0.mX) ) );
        tmp.mY = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mY), _mm_castps_si128(v0.mY) ) );
        tmp.mZ = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mZ), _mm_castps_si128(v0.mZ) ) );
        return tmp;
    }
*/
/*
    __forceinline VFloat3 Shuffle( VFloat3 v0, int val )
    {
        VFloat3 tmp;
        tmp.mX = _mm_shuffle_ps( mX, v0.mX, val );
        tmp.mY = _mm_shuffle_ps( mY, v0.mY, val );
        tmp.mZ = _mm_shuffle_ps( mZ, v0.mZ, val );
        return tmp;
    }
*/
    VFloat3 Step( float threshold )
    {
        __m128 vThresh = _mm_set1_ps( threshold );
        VFloat3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128( _mm_cmpgt_ps( mX, vThresh)), _mm_castps_si128(mX) ));
        tmp.mY = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128( _mm_cmpgt_ps( mY, vThresh)), _mm_castps_si128(mY) ));
        tmp.mZ = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128( _mm_cmpgt_ps( mZ, vThresh)), _mm_castps_si128(mZ) ));
        return tmp;
    }
/*
    __forceinline void SetHorizontalSumByFours( int lane, VFloat3 source )
    {
        // TODO: Use shuffles instead of these awkward accesses.
        mX.m128_f32[lane]   = source.mX.m128_f32[0] + source.mX.m128_f32[1] + source.mX.m128_f32[2] + source.mX.m128_f32[3];
        mY.m128_f32[lane]   = source.mY.m128_f32[0] + source.mY.m128_f32[1] + source.mY.m128_f32[2] + source.mY.m128_f32[3];
        mZ.m128_f32[lane]   = source.mZ.m128_f32[0] + source.mZ.m128_f32[1] + source.mZ.m128_f32[2] + source.mZ.m128_f32[3];
    }
*/
};


// ******************************************************************
class VInt3
{
public:
    union {
        struct {
            __m128i mRed;
            __m128i mGreen;
            __m128i mBlue;
        };
        struct {
            __m128i mX;
            __m128i mY;
            __m128i mZ;
        };
    };

public:
    VInt3(){};
    ~VInt3(){};

    explicit VInt3( const int val )
    {
        mX = mY = mZ = _mm_set1_epi32( val );
    }

    explicit VInt3( const int xx, const int yy, const int zz )
    {
        mX = _mm_set1_epi32( xx );
        mY = _mm_set1_epi32( yy );
        mZ = _mm_set1_epi32( zz );
    }

    explicit VInt3( const VInt &v0, const VInt &v1, const VInt &v2 )
    {
        mX = v0.mAsVector;
        mY = v1.mAsVector;
        mZ = v2.mAsVector;
    }

    __forceinline VInt3 operator+( const VInt3 &val ) const
    {
        VInt3 tmp;
        tmp.mX = _mm_add_epi32( mX, val.mX );
        tmp.mY = _mm_add_epi32( mY, val.mY );
        tmp.mZ = _mm_add_epi32( mZ, val.mZ );
        return tmp;
    }

    __forceinline VInt3 operator-( const VInt3 &val ) const
    {
        VInt3 tmp;
        tmp.mX = _mm_sub_epi32( mX, val.mX );
        tmp.mY = _mm_sub_epi32( mY, val.mY );
        tmp.mZ = _mm_sub_epi32( mZ, val.mZ );
        return tmp;
    }
/*
    __forceinline VInt3 operator*( const VInt3 &val ) const
    {
        VInt3 tmp;
        tmp.mX = _mm_mul_ps( mX, val.mX );
        tmp.mY = _mm_mul_ps( mY, val.mY );
        tmp.mZ = _mm_mul_ps( mZ, val.mZ );
        return tmp;
    }

    __forceinline VInt3 operator*( const VInt &val ) const
    {
        VInt3 tmp;
        tmp.mX = _mm_mul_ps( mX, val.mAsVector );
        tmp.mY = _mm_mul_ps( mY, val.mAsVector );
        tmp.mZ = _mm_mul_ps( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline VInt3 operator/( const VInt3 &val ) const
    {
        VInt3 tmp;
        tmp.mX = _mm_div_ps( mX, val.mX );
        tmp.mY = _mm_div_ps( mY, val.mY );
        tmp.mZ = _mm_div_ps( mZ, val.mZ );
        return tmp;
    }

    __forceinline VInt3 operator*( const int val ) const
    {
        VInt3 tmp;
        __m128i valVec = _mm_set1_epi32(val);
        tmp.mX = _mm_mul_ps( mX, valVec );
        tmp.mY = _mm_mul_ps( mY, valVec );
        tmp.mZ = _mm_mul_ps( mZ, valVec );
        return tmp;
    }

    __forceinline VInt3 operator/( const int val ) const
    {
        VInt3 tmp;
        __m128i valVec = _mm_set1_epi32(val);
        tmp.mX = _mm_div_ps( mX, valVec );
        tmp.mY = _mm_div_ps( mY, valVec );
        tmp.mZ = _mm_div_ps( mZ, valVec );
        return tmp;
    }

*/

    __forceinline VInt3 operator+( const VInt &val ) const
    {
        VInt3 tmp;
        tmp.mX = _mm_add_epi32( mX, val.mAsVector );
        tmp.mY = _mm_add_epi32( mY, val.mAsVector );
        tmp.mZ = _mm_add_epi32( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline VInt3 operator-( const VInt &val ) const
    {
        VInt3 tmp;
        tmp.mX = _mm_sub_epi32( mX, val.mAsVector );
        tmp.mY = _mm_sub_epi32( mY, val.mAsVector );
        tmp.mZ = _mm_sub_epi32( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline VInt3 operator+( const int val ) const
    {
        VInt3 tmp;
        __m128i valVec = _mm_set1_epi32(val);
        tmp.mX = _mm_add_epi32( mX, valVec );
        tmp.mY = _mm_add_epi32( mY, valVec );
        tmp.mZ = _mm_add_epi32( mZ, valVec );
        return tmp;
    }

    __forceinline VInt3 operator-( const int val ) const
    {
        VInt3 tmp;
        __m128i valVec = _mm_set1_epi32(val);
        tmp.mX = _mm_sub_epi32( mX, valVec );
        tmp.mY = _mm_sub_epi32( mY, valVec );
        tmp.mZ = _mm_sub_epi32( mZ, valVec );
        return tmp;
    }

    // TODO: Which way do we want to do this?  SOA or AOS?
    // For now, keep with the "SOA is behind the scenes" theme, and add the vectors together
    // instead of adding each of them horizontally.
    __forceinline VInt HorizontalSum() const
    {
        VInt tmp;
        tmp.mAsVector = _mm_add_epi32( _mm_add_epi32( mRed, mGreen ),  mBlue );
        return tmp;
    }

    __forceinline VInt AsRgbaVInt() const
    {
        VInt tmp;
        __m128i red   = mRed;
        __m128i green = _mm_slli_epi32( mGreen, 8 );
        __m128i blue  = _mm_slli_epi32( mBlue, 16 );
        tmp.mAsVector = _mm_or_si128( red, _mm_or_si128( green, blue ) );
        return tmp;
    }

    __forceinline VInt Red() const
    {
        VInt tmp;
        tmp.mAsVector = mRed;
        return tmp;
    }

    __forceinline VInt Green() const
    {
        VInt tmp;
        tmp.mAsVector = mGreen;
        return tmp;
    }

    __forceinline VInt Blue() const
    {
        VInt tmp;
        tmp.mAsVector = mBlue;
        return tmp;
    }

    // Yuck.  What should this do?  Should we have a different method for what this is currently doing?
    __forceinline VInt3 operator[](int lane)
    {
        // "extraxt" one lane, "promote" to VInt3.
        return VInt3(
            VInt(mX.m128i_i32[lane]),
            VInt(mY.m128i_i32[lane]),
            VInt(mZ.m128i_i32[lane])
        );
    }

    __forceinline void Set( int lane, int red, int green, int blue )
    {
        mRed.m128i_i32[lane]   = red;
        mGreen.m128i_i32[lane] = green;
        mBlue.m128i_i32[lane]  = blue;
    }

    __forceinline VInt3 ShiftVectorLeftByOne()
    {
        VInt3 tmp;
        tmp.mX = _mm_slli_si128( mX, 4 );
        tmp.mY = _mm_slli_si128( mY, 4 );
        tmp.mZ = _mm_slli_si128( mZ, 4 );
        return tmp;
    }

    __forceinline VInt3 ShiftVectorLeftByTwo()
    {
        VInt3 tmp;
        tmp.mX = _mm_slli_si128( mX, 8 );
        tmp.mY = _mm_slli_si128( mY, 8 );
        tmp.mZ = _mm_slli_si128( mZ, 8 );
        return tmp;
    }

    __forceinline VInt3 ShiftVectorLeftByThree()
    {
        VInt3 tmp;
        tmp.mX = _mm_slli_si128( mX, 12 );
        tmp.mY = _mm_slli_si128( mY, 12 );
        tmp.mZ = _mm_slli_si128( mZ, 12 );
        return tmp;
    }

    __forceinline VInt3 ShiftVectorRightByOne()
    {
        VInt3 tmp;
        tmp.mX = _mm_srli_si128( mX, 4 );
        tmp.mY = _mm_srli_si128( mY, 4 );
        tmp.mZ = _mm_srli_si128( mZ, 4 );
        return tmp;
    }

    __forceinline VInt3 ShiftVectorRightByTwo()
    {
        VInt3 tmp;
        tmp.mX = _mm_srli_si128( mX, 8 );
        tmp.mY = _mm_srli_si128( mY, 8 );
        tmp.mZ = _mm_srli_si128( mZ, 8 );
        return tmp;
    }

    __forceinline VInt3 ShiftVectorRightByThree()
    {
        VInt3 tmp;
        tmp.mX = _mm_srli_si128( mX, 12 );
        tmp.mY = _mm_srli_si128( mY, 12 );
        tmp.mZ = _mm_srli_si128( mZ, 12 );
        return tmp;
    }
/*
    __forceinline VInt3 AndVector( VInt v0 )
    {
        VInt3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mX), _mm_castps_si128(v0.mAsVector) ) );
        tmp.mY = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mY), _mm_castps_si128(v0.mAsVector) ) );
        tmp.mZ = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mZ), _mm_castps_si128(v0.mAsVector) ) );
        return tmp;
    }

    __forceinline VInt3 AndVector( VInt3 v0 )
    {
        VInt3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mX), _mm_castps_si128(v0.mX) ) );
        tmp.mY = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mY), _mm_castps_si128(v0.mY) ) );
        tmp.mZ = _mm_castsi128_ps( _mm_and_si128( _mm_castps_si128(mZ), _mm_castps_si128(v0.mZ) ) );
        return tmp;
    }

    __forceinline VInt3 OrVector( VInt v0 )
    {
        VInt3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mX), _mm_castps_si128(v0.mAsVector) ) );
        tmp.mY = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mY), _mm_castps_si128(v0.mAsVector) ) );
        tmp.mZ = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mZ), _mm_castps_si128(v0.mAsVector) ) );
        return tmp;
    }

    __forceinline VInt3 OrVector( VInt3 v0 )
    {
        VInt3 tmp;
        tmp.mX = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mX), _mm_castps_si128(v0.mX) ) );
        tmp.mY = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mY), _mm_castps_si128(v0.mY) ) );
        tmp.mZ = _mm_castsi128_ps( _mm_or_si128( _mm_castps_si128(mZ), _mm_castps_si128(v0.mZ) ) );
        return tmp;
    }
*/
/*
    __forceinline VInt3 Shuffle( VInt3 v0, int val )
    {
        VInt3 tmp;
        tmp.mX = _mm_shuffle_ps( mX, v0.mX, val );
        tmp.mY = _mm_shuffle_ps( mY, v0.mY, val );
        tmp.mZ = _mm_shuffle_ps( mZ, v0.mZ, val );
        return tmp;
    }
*/
    VInt3 Step( int threshold )
    {
        __m128i vThresh = _mm_set1_epi32( threshold );
        VInt3 tmp;
        tmp.mX = _mm_and_si128( _mm_cmpgt_epi32( mX, vThresh), mX );
        tmp.mY = _mm_and_si128( _mm_cmpgt_epi32( mY, vThresh), mY );
        tmp.mZ = _mm_and_si128( _mm_cmpgt_epi32( mZ, vThresh), mZ );
        return tmp;
    }
/*
    __forceinline void SetHorizontalSumByFours( int lane, VInt3 source )
    {
        // TODO: Use shuffles instead of these awkward accesses.
        mX.m128_f32[lane]   = source.mX.m128_f32[0] + source.mX.m128_f32[1] + source.mX.m128_f32[2] + source.mX.m128_f32[3];
        mY.m128_f32[lane]   = source.mY.m128_f32[0] + source.mY.m128_f32[1] + source.mY.m128_f32[2] + source.mY.m128_f32[3];
        mZ.m128_f32[lane]   = source.mZ.m128_f32[0] + source.mZ.m128_f32[1] + source.mZ.m128_f32[2] + source.mZ.m128_f32[3];
    }
*/
};

#define VECTOR_LENGTH 4

__forceinline VFloat Min( const VFloat &v0, const VFloat &v1 ) 
{
    VFloat tmp;
    tmp.mAsVector = _mm_min_ps( v0.mAsVector, v1.mAsVector );
    return tmp;
}

__forceinline VFloat Max( const VFloat &v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_max_ps( v0.mAsVector, v1.mAsVector );
    return tmp;
}

__forceinline VInt Min( const VInt &v0, const VInt &v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_min_epi32( v0.mAsVector, v1.mAsVector );
    return tmp;
}

__forceinline VInt Max( const VInt &v0, const VInt &v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_max_epi32( v0.mAsVector, v1.mAsVector );
    return tmp;
}

__forceinline void Transpose( VFloat &v0, VFloat &v1, VFloat &v2, VFloat &v3 )
{
    _MM_TRANSPOSE4_PS( v0.mAsVector, v1.mAsVector, v2.mAsVector, v3.mAsVector );
}
    
__forceinline void Transpose( VFloat4 &v0 )
{
    _MM_TRANSPOSE4_PS( v0.mX, v0.mY, v0.mZ, v0.mW );
}

/*
__forceinline float Dot3( VFloat v0, VFloat v1 )
{
    __m128 tmp1 = _mm_mul_ps( v0.mAsVector, v1.mAsVector );
    return tmp1.m128_f32[0] + tmp1.m128_f32[1] + tmp1.m128_f32[2];
}
*/
__forceinline VFloat Dot3( const VFloat3 &v0, const VFloat &v1 )
{
    VFloat tmp;
    __m128 tmpX = _mm_mul_ps( v0.mX, v1.mAsVector );
    __m128 tmpY = _mm_mul_ps( v0.mY, v1.mAsVector );
    __m128 tmpZ = _mm_mul_ps( v0.mZ, v1.mAsVector );

    __m128 sum0 = _mm_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm_add_ps( sum0, tmpZ );
    return tmp;
}

__forceinline VFloat Dot3( const VFloat3 &v0, const VFloat3 &v1 )
{
    VFloat tmp;
    __m128 tmpX = _mm_mul_ps( v0.mX, v1.mX );
    __m128 tmpY = _mm_mul_ps( v0.mY, v1.mY );
    __m128 tmpZ = _mm_mul_ps( v0.mZ, v1.mZ );

    __m128 sum0 = _mm_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm_add_ps( sum0, tmpZ );
    return tmp;
}

__forceinline VFloat Dot3( const VFloat4 &v0, const VFloat &v1 )
{
    VFloat tmp;
    __m128 tmpX = _mm_mul_ps( v0.mX, v1.mAsVector );
    __m128 tmpY = _mm_mul_ps( v0.mY, v1.mAsVector );
    __m128 tmpZ = _mm_mul_ps( v0.mZ, v1.mAsVector );

    __m128 sum0 = _mm_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm_add_ps( sum0, tmpZ );
    return tmp;
}

__forceinline VFloat Dot3( const VFloat4 &v0, const VFloat3 &v1 )
{
    VFloat tmp;
    __m128 tmpX = _mm_mul_ps( v0.mX, v1.mX );
    __m128 tmpY = _mm_mul_ps( v0.mY, v1.mY );
    __m128 tmpZ = _mm_mul_ps( v0.mZ, v1.mZ );

    __m128 sum0 = _mm_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm_add_ps( sum0, tmpZ );
    return tmp;
}
__forceinline VFloat Dot3( const VFloat4 &v0, const VFloat4 &v1 )
{
    VFloat tmp;
    __m128 tmpX = _mm_mul_ps( v0.mX, v1.mX );
    __m128 tmpY = _mm_mul_ps( v0.mY, v1.mY );
    __m128 tmpZ = _mm_mul_ps( v0.mZ, v1.mZ );

    __m128 sum0 = _mm_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm_add_ps( sum0, tmpZ );
    return tmp;
}
__forceinline VFloat Dot( const VFloat3 &v0, const VFloat3 &v1 )
{
    VFloat tmp;
    __m128 tmpX = _mm_mul_ps( v0.mX, v1.mX );
    __m128 tmpY = _mm_mul_ps( v0.mY, v1.mY );
    __m128 tmpZ = _mm_mul_ps( v0.mZ, v1.mZ );

    __m128 sum = _mm_add_ps( tmpX, tmpY );
    tmp.mAsVector = _mm_add_ps( sum, tmpZ );
    return tmp;
}

__forceinline VFloat Dot( const VFloat3 &v0, const VFloat4 &v1 )
{
    VFloat tmp;
    __m128 tmpX = _mm_mul_ps( v0.mX, v1.mX );
    __m128 tmpY = _mm_mul_ps( v0.mY, v1.mY );
    __m128 tmpZ = _mm_mul_ps( v0.mZ, v1.mZ );
    __m128 tmpW = v1.mW;

    __m128 sumXY = _mm_add_ps( tmpX, tmpY );
    __m128 sumZW = _mm_add_ps( tmpZ, tmpW );
    tmp.mAsVector = _mm_add_ps( sumXY, sumZW );
    return tmp;
}

__forceinline VFloat Dot( const VFloat4 &v0, const VFloat4 &v1 )
{
    VFloat tmp;
    __m128 tmpX = _mm_mul_ps( v0.mX, v1.mX );
    __m128 tmpY = _mm_mul_ps( v0.mY, v1.mY );
    __m128 tmpZ = _mm_mul_ps( v0.mZ, v1.mZ );
    __m128 tmpW = _mm_mul_ps( v0.mW, v1.mW );

    __m128 sumXY = _mm_add_ps( tmpX, tmpY );
    __m128 sumZW = _mm_add_ps( tmpZ, tmpW );
    tmp.mAsVector = _mm_add_ps( sumXY, sumZW );

    return tmp;
}

__forceinline VFloat3 Min( float val, const VFloat3 &v0 )
{
    __m128 xx = _mm_set1_ps( val );
    VFloat3 tmp;
    tmp.mX = _mm_min_ps( xx, v0.mX );
    tmp.mY = _mm_min_ps( xx, v0.mY );
    tmp.mZ = _mm_min_ps( xx, v0.mZ );
    return tmp;
}


__forceinline VFloat3 rsqrt( const VFloat3 &src )
{
    VFloat3 tmp;
    tmp.mX = _mm_rsqrt_ps( src.mX );
    tmp.mY = _mm_rsqrt_ps( src.mY );
    tmp.mZ = _mm_rsqrt_ps( src.mZ );
    return tmp;
}

__forceinline VFloat3 sqrt( const VFloat3 &src )
{
    VFloat3 tmp = rsqrt(src);
    return src * tmp;
}


void ExpandByFour( VFloat3 *pOut, VFloat3 *pIn, int count )
{
    int ii;
    for( ii=0; ii<count; ii+=VECTOR_LENGTH )
    {
        pOut->mX = _mm_shuffle_ps( pIn->mX, pIn->mX, 0x00 );
        pOut->mY = _mm_shuffle_ps( pIn->mY, pIn->mY, 0x00 );
        pOut->mZ = _mm_shuffle_ps( pIn->mZ, pIn->mZ, 0x00 );
        pOut++;

        pOut->mX = _mm_shuffle_ps( pIn->mX, pIn->mX, 0x55 );
        pOut->mY = _mm_shuffle_ps( pIn->mY, pIn->mY, 0x55 );
        pOut->mZ = _mm_shuffle_ps( pIn->mZ, pIn->mZ, 0x55 );
        pOut++;

        pOut->mX = _mm_shuffle_ps( pIn->mX, pIn->mX, 0xAA );
        pOut->mY = _mm_shuffle_ps( pIn->mY, pIn->mY, 0xAA );
        pOut->mZ = _mm_shuffle_ps( pIn->mZ, pIn->mZ, 0xAA );
        pOut++;

        pOut->mX = _mm_shuffle_ps( pIn->mX, pIn->mX, 0xFF );
        pOut->mY = _mm_shuffle_ps( pIn->mY, pIn->mY, 0xFF );
        pOut->mZ = _mm_shuffle_ps( pIn->mZ, pIn->mZ, 0xFF );
        pOut++;

        pIn++;
    }}

void ShiftAndExpandByFour( VFloat3 *pOut, VFloat3 *pIn, int count )
{
    int ii;
    for( ii=0; ii<count; ii+=VECTOR_LENGTH )
    {
        // pOut->mX = _mm_shuffle_ps( pIn->mX, pIn->mX, 0x00 );
        // pOut->mY = _mm_shuffle_ps( pIn->mY, pIn->mY, 0x00 );
        // pOut->mZ = _mm_shuffle_ps( pIn->mZ, pIn->mZ, 0x00 );
        // pOut++;

        pOut->mX = _mm_shuffle_ps( pIn->mX, pIn->mX, 0x55 );
        pOut->mY = _mm_shuffle_ps( pIn->mY, pIn->mY, 0x55 );
        pOut->mZ = _mm_shuffle_ps( pIn->mZ, pIn->mZ, 0x55 );
        pOut++;

        pOut->mX = _mm_shuffle_ps( pIn->mX, pIn->mX, 0xAA );
        pOut->mY = _mm_shuffle_ps( pIn->mY, pIn->mY, 0xAA );
        pOut->mZ = _mm_shuffle_ps( pIn->mZ, pIn->mZ, 0xAA );
        pOut++;

        pOut->mX = _mm_shuffle_ps( pIn->mX, pIn->mX, 0xFF );
        pOut->mY = _mm_shuffle_ps( pIn->mY, pIn->mY, 0xFF );
        pOut->mZ = _mm_shuffle_ps( pIn->mZ, pIn->mZ, 0xFF );
        pOut++;

        pIn++;
        pOut->mX = _mm_shuffle_ps( pIn->mX, pIn->mX, 0x00 );
        pOut->mY = _mm_shuffle_ps( pIn->mY, pIn->mY, 0x00 );
        pOut->mZ = _mm_shuffle_ps( pIn->mZ, pIn->mZ, 0x00 );
        pOut++;
    }
}

static const __m128i GREEN_EXTRACT_SHUFFLE_MASK = _mm_set_epi32( 0xFFFFFF0D, 0xFFFFFF09, 0xFFFFFF05, 0xFFFFFF01 );
static const __m128i BLUE_EXTRACT_SHUFFLE_MASK  = _mm_set_epi32( 0xFFFFFF0E, 0xFFFFFF0A, 0xFFFFFF06, 0xFFFFFF02 );

__forceinline VFloat3 UnpackRGBA( const VInt &packedRGBA )
{
    VFloat3 unpackedRGBA;
    unpackedRGBA.mRed   = _mm_cvtepi32_ps( _mm_and_si128( packedRGBA.mAsVector, _mm_set1_epi32( 0x000000FF ) ) );
    unpackedRGBA.mGreen = _mm_cvtepi32_ps( _mm_shuffle_epi8( packedRGBA.mAsVector,  GREEN_EXTRACT_SHUFFLE_MASK) );
    unpackedRGBA.mBlue  = _mm_cvtepi32_ps( _mm_shuffle_epi8( packedRGBA.mAsVector,  BLUE_EXTRACT_SHUFFLE_MASK) );
    return unpackedRGBA;
}

__forceinline VInt PackRGBA( const VFloat3 &unpackedRGBA )
{
    VInt tmp;
    __m128i red   = _mm_cvtps_epi32( unpackedRGBA.mRed );
    __m128i green = _mm_cvtps_epi32( unpackedRGBA.mGreen );
    __m128i blue  = _mm_cvtps_epi32( unpackedRGBA.mBlue );

    tmp.mAsVector = _mm_or_si128( red, _mm_or_si128( _mm_slli_epi32( green, 8 ), _mm_slli_epi32( blue, 16 ) ) );
    return tmp;
}

VFloat operator-( float v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_sub_ps( _mm_set1_ps(v0), v1.mAsVector );
    return tmp;
}

VFloat operator*( float v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_mul_ps( _mm_set1_ps(v0), v1.mAsVector );
    return tmp;
}

VFloat Max( float v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_max_ps( _mm_set1_ps(v0), v1.mAsVector );
    return tmp;
}

VFloat Max( const VFloat &v0, float v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_max_ps( v0.mAsVector, _mm_set1_ps(v1) );
    return tmp;
}

VFloat operator/( float num, const VFloat &den )
{
    VFloat tmp;
    tmp.mAsVector = _mm_div_ps( _mm_set1_ps(num), den.mAsVector );
    return tmp;
}

VInt Max( const VInt &v0, int v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_max_epi32( v0.mAsVector, _mm_set1_epi32(v1) );
    return tmp;
}

VInt Min( const VInt &v0, int v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_min_epi32( v0.mAsVector, _mm_set1_epi32(v1) );
    return tmp;
}

VFloat ceil( const VFloat &v0 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_ceil_ps( v0.mAsVector );
    return tmp;
}


VFloat cmpge( const VFloat &v0, float v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmpge_ps( v0.mAsVector, _mm_set1_ps(v1) );
    return tmp;
}

VFloat cmpge( const VFloat &v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmpge_ps( v0.mAsVector, v1.mAsVector );
    return tmp;
}

VFloat cmpgt( const VFloat &v0, float v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmpgt_ps( v0.mAsVector, _mm_set1_ps(v1) );
    return tmp;
}

VFloat cmplt( const VFloat &v0, float v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmplt_ps( v0.mAsVector, _mm_set1_ps(v1) );
    return tmp;
}

VFloat cmple( const VFloat &v0, float v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmple_ps( v0.mAsVector, _mm_set1_ps(v1) );
    return tmp;
}


VInt cmpgt( const VInt &v0, int v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_cmpgt_epi32( v0.mAsVector, _mm_set1_epi32(v1) );
    return tmp;
}

VInt cmplt( const VInt &v0, int v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_cmplt_epi32( v0.mAsVector, _mm_set1_epi32(v1) );
    return tmp;
}

VFloat blend( const VFloat &v0, const VFloat &v1, const VFloat &mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( v0.mAsVector, v1.mAsVector, mask.mAsVector );
    return tmp;
}

VFloat blend( const VFloat &v0, float v1, const VFloat &mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( v0.mAsVector, _mm_set1_ps(v1), mask.mAsVector );
    return tmp;
}

VFloat blend( float v0, const VFloat &v1, const VFloat &mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( _mm_set1_ps(v0), v1.mAsVector, mask.mAsVector );
    return tmp;
}

VFloat blend( float v0, const VFloat &v1, const VInt &mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( _mm_set1_ps(v0), v1.mAsVector, _mm_castsi128_ps(mask.mAsVector) );
    return tmp;
}

VInt blend( const VInt &v0, const VInt &v1, const VInt &mask )
{
    VInt tmp;
    tmp.mAsVector = _mm_blendv_epi8( v0.mAsVector, v1.mAsVector, mask.mAsVector );
    return tmp;
}

VInt blend( const VInt &v0, const VInt &v1, const VFloat &mask )
{
    VInt tmp;
    tmp.mAsVector = _mm_castps_si128(_mm_blendv_ps( _mm_castsi128_ps(v0.mAsVector), _mm_castsi128_ps(v1.mAsVector), mask.mAsVector) );
    return tmp;
}

VInt blend( int v0, const VInt &v1, const VInt &mask )
{
    VInt tmp;
    tmp.mAsVector = _mm_castps_si128(_mm_blendv_ps( _mm_castsi128_ps(_mm_set1_epi32(v0)), _mm_castsi128_ps(v1.mAsVector), _mm_castsi128_ps(mask.mAsVector)) );
    return tmp;
}

VFloat blend( float v0, float v1, const VInt &mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( _mm_set1_ps(v0), _mm_set1_ps(v1), _mm_castsi128_ps(mask.mAsVector) );
    return tmp;
}

VFloat blend( float v0, float v1, const VFloat &mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( _mm_set1_ps(v0), _mm_set1_ps(v1), mask.mAsVector );
    return tmp;
}


__forceinline VFloat operator&( const VFloat &v0, const VInt &val )
{
    VFloat tmp;
    tmp.mAsVector = _mm_and_ps( v0.mAsVector, _mm_castsi128_ps(val.mAsVector) );
    return tmp;
}
