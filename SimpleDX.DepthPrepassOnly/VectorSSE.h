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
#define VECTOR_LENGTH    4

class VInt;

template <UINT MANTISSA_BITS>
class VFixPt;

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

    explicit VFloat( const VInt );
    template <UINT MANTISSA_BITS>
    explicit VFloat( const VFixPt<MANTISSA_BITS> );

    explicit VFloat( const __m128i &v0 )
    {
        mAsVector = _mm_cvtepi32_ps(v0);
    }

    explicit VFloat( const float v0, const float v1, const float v2, const float v3 )
    {
        mAsVector = _mm_set_ps( v0, v1, v2, v3 );
    }

    __forceinline VFloat ExtractLaneAsSIMD(int lane)
    {
        VFloat tmp;
        // tmp.mAsVector = _mm_set1_ps( _mm_cvtss_f32( mAsVector) ); // This extracts lane 0
// TODO: it isn't clear to me which of these approaches is fastest
//        __m128i laneSimd = _mm_set1_epi32( lane*0x55);
//        tmp.mAsVector = _mm_permutevar_ps( mAsVector, laneSimd );
        tmp.mAsVector = _mm_set1_ps( mAsVector.m128_f32[lane] );
        return tmp;
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

    __forceinline VFloat operator*=( const float val )
    {
        mAsVector = _mm_mul_ps( mAsVector, _mm_set1_ps( val ) );
        return *this;
    }

    __forceinline VFloat operator*=( const VFloat val )
    {
        mAsVector = _mm_mul_ps( mAsVector, val.mAsVector );
        return *this;
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
//    __forceinline VFloat operator[](int lane)
//    {
//        // "extract" one lane, "promote" to VFloat3.
//        return VFloat( VFloat(mAsVector.m128_f32[lane]) );
//    }
    __forceinline float operator[](int lane)
    {
        return mAsVector.m128_f32[lane];
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

    template <UINT MANTISSA_BITS>
    explicit VInt( const VFixPt<MANTISSA_BITS> &v0 );

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

    __forceinline VInt operator-( const int val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_sub_epi32( mAsVector, _mm_set1_epi32(val) );
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

    __forceinline VInt operator>>( UINT val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_srai_epi32( mAsVector, val );
        return tmp;
    }
/*
    __forceinline VInt operator>>( VInt val ) const
    {
        // Unfortunately, no SIMD shift by SIMD instruction available
        VInt tmp(
            mAsVector.m128i_i32[3] >> val.mAsVector.m128i_i32[3],
            mAsVector.m128i_i32[2] >> val.mAsVector.m128i_i32[2],
            mAsVector.m128i_i32[1] >> val.mAsVector.m128i_i32[1],
            mAsVector.m128i_i32[0] >> val.mAsVector.m128i_i32[0]
        );
        return tmp;
    }
*/
//    VInt operator/( VInt val )
//    {
//        VInt tmp;
//        tmp.mAsVector = _mm_div_epi32( mAsVector, val.mAsVector );
//    }

    __forceinline int operator[](int lane)
    {
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
    __forceinline VInt operator&( const VFloat &val ) const
    {
        VInt tmp;
        tmp.mAsVector = _mm_and_si128( mAsVector, _mm_castps_si128(val.mAsVector) );
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
/*
    __forceinline VInt operator<<( const VInt count ) const
    {

        // Unfortunately, no SIMD shift by SIMD instruction available
        VInt tmp(
            mAsVector.m128i_i32[3] << count.mAsVector.m128i_i32[3],
            mAsVector.m128i_i32[2] << count.mAsVector.m128i_i32[2],
            mAsVector.m128i_i32[1] << count.mAsVector.m128i_i32[1],
            mAsVector.m128i_i32[0] << count.mAsVector.m128i_i32[0]
        );
        return tmp;
    }
*/
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

    explicit VFloat3( const VFloat val )
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
        // "extract" one lane, "promote" to VFloat3.
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
        struct {
            VInt x;
            VInt y;
            VInt z;
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
        // "extract" one lane, "promote" to VInt3.
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

}; // VInt3;

// ******************************************************************
template <UINT MANTISSA_BITS>
class VFixPt
{
public:
    __m128i mAsVector;

public:
    VFixPt(){};
    ~VFixPt(){};

    __forceinline static VFixPt Zero()
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_setzero_si128();
        return tmp;
    }

    const int MantissaBits() const { return MANTISSA_BITS; }
    explicit VFixPt( const int val )
    {
        if( MANTISSA_BITS > 0 )
        {
            mAsVector = _mm_set1_epi32( val<<MANTISSA_BITS );
        }
        else
        {
            mAsVector = _mm_set1_epi32( val );
        }
    }

    explicit VFixPt( const int v0, const int v1, const int v2, const int v3 )
    {
        if( MANTISSA_BITS > 0 )
        {
            mAsVector = _mm_slli_epi32( _mm_set_epi32( v0, v1, v2, v3 ), MANTISSA_BITS );
        }
        else
        {
            mAsVector = _mm_set_epi32( v0, v1, v2, v3 );
        }
    }

    explicit VFixPt( const VFloat &v0 )
    {
        if( MANTISSA_BITS > 0 )
        {
            __m128 bias = _mm_set1_ps( float(1<<MANTISSA_BITS) );
            mAsVector = _mm_cvtps_epi32( _mm_mul_ps( v0.mAsVector, bias ) );
        }
        else
        {
            mAsVector = _mm_cvtps_epi32( v0.mAsVector );
        }
    }

    __forceinline VFixPt ExtractLaneAsSIMD(VInt lane)
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_castps_si128(_mm_permutevar_ps( _mm_castsi128_ps(mAsVector), lane.mAsVector ));
        // tmp.mAsVector = _mm_set1_epi32( _mm_extract_epi32(mAsVector,0) );
        return tmp;
    }

/*
    __forceinline VFixPt ExtractLaneAsSIMD( int lane )
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_set1_epi32( mAsVector.m128i_i32[lane] );
        return tmp;
    }
*/
    __forceinline VFixPt ExtractLaneAsSIMD(int lane)
    {
        VFixPt tmp;
// TODO: it isn't clear to me which of these approaches is fastest
//        __m128i laneSimd = _mm_set1_epi32( lane*0x55);
//        tmp.mAsVector = _mm_castps_si128(_mm_permutevar_ps( _mm_castsi128_ps(mAsVector), laneSimd ));
        tmp.mAsVector = _mm_set1_epi32( mAsVector.m128i_i32[lane] );
        return tmp;
    }

    __forceinline VFixPt operator+( const VFixPt &val ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_add_epi32( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VFixPt operator+( const int &val ) const
    {
        VFixPt tmp;
        if( MANTISSA_BITS > 0 )
        {
            tmp.mAsVector = _mm_add_epi32( mAsVector, _mm_set1_epi32(val<<MANTISSA_BITS) );
        }
        else
        {
            tmp.mAsVector = _mm_add_epi32( mAsVector, _mm_set1_epi32(val) );
        }
        return tmp;
    }

    __forceinline VFixPt operator-( const VFixPt &val ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_sub_epi32( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VFixPt operator*( const VFixPt &val ) const
    {
        // Multiply moves the radix point.  28.4 * 28.4 gives 24.8
        VFixPt tmp;
        tmp.mAsVector = _mm_mullo_epi32( mAsVector, val.mAsVector );
#if 1
        if( MANTISSA_BITS > 0 )
        {
            __m128i half = _mm_set1_epi32(1<<(MANTISSA_BITS-1)); // Add this to get rounding-up behavior
            int shift = val.MantissaBits();
            tmp.mAsVector = _mm_srai_epi32( _mm_add_epi32( tmp.mAsVector, half ), shift );
        }
#endif
        return tmp;
    }

    __forceinline VFixPt operator*( const VInt &val ) const
    {
        // Multiply by VInt doesn't move the radix point.  28.4 * 32.0 gives 24.8
        VFixPt tmp;
        tmp.mAsVector = _mm_mullo_epi32( mAsVector, val.mAsVector );
        return tmp;
    }

    __forceinline VFixPt operator*( int val ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_mullo_epi32( mAsVector, _mm_set1_epi32(val) );
        return tmp;
    }

    __forceinline VFixPt operator>>( UINT val ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_srai_epi32( mAsVector, val );
        return tmp;
    }
/*
    __forceinline VFixPt operator>>( VFixPt val ) const
    {
        VFixPt tmp;
        // Unfortunately, no SIMD shift by SIMD instruction available
        tmp.mAsVector.m128i_i32[3] = mAsVector.m128i_i32[3] >> val.mAsVector.m128i_i32[3];
        tmp.mAsVector.m128i_i32[2] = mAsVector.m128i_i32[2] >> val.mAsVector.m128i_i32[2];
        tmp.mAsVector.m128i_i32[1] = mAsVector.m128i_i32[1] >> val.mAsVector.m128i_i32[1];
        tmp.mAsVector.m128i_i32[0] = mAsVector.m128i_i32[0] >> val.mAsVector.m128i_i32[0];
        return tmp;
    }
*/
//    What to do about divide?  Convert to float, do divide, convert back?
//    VFixPt operator/( VFixPt val )
//    {
//        VFixPt tmp;
//        tmp.mAsVector = _mm_div_epi32( mAsVector, val.mAsVector );
//    }

    __forceinline int operator[](int lane)
    {
        return mAsVector.m128i_i32[lane];
    }

    __forceinline VFixPt UnpackHi16( const VFixPt &src ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_unpackhi_epi16( src.mAsVector, _mm_setzero_si128() );
        return tmp;
    }
    __forceinline VFixPt UnpackLow16( const VFixPt &src ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_unpacklo_epi16( src.mAsVector, _mm_setzero_si128() );
        return tmp;
    }
    __forceinline VFixPt operator&( const VFixPt &val ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_and_si128( mAsVector, val.mAsVector );
        return tmp;
    }
    __forceinline VFixPt operator|( const VFixPt &val ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_or_si128( mAsVector, val.mAsVector );
        return tmp;
    }
    __forceinline VFixPt operator&( const VFloat &val ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_and_si128( mAsVector, _mm_castps_si128(val.mAsVector) );
        return tmp;
    }

/*
What to do here?  Convert to 28.4 first, then do operation?

    __forceinline VFixPt operator&( const int &val ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_and_si128( mAsVector, _mm_set1_epi32(val) );
        return tmp;
    }
    __forceinline VFixPt operator|( const VFixPt &val ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_or_si128( mAsVector, val.mAsVector );
        return tmp;
    }
*/
    __forceinline VFixPt operator<<( const int count ) const
    {
        VFixPt tmp;
        tmp.mAsVector = _mm_slli_epi32( mAsVector, count ); // TODO: What about overflow?
        return tmp;
    }
}; // VFixPt

// ******************************************************************
template <UINT MANTISSA_BITS>
class VFixPt4
{
public:
    union {
        struct {
            __m128i mRed;
            __m128i mGreen;
            __m128i mBlue;
            __m128i mAlpha;
        };
        struct {
            __m128i mX;
            __m128i mY;
            __m128i mZ;
            __m128i mW;
        };
        struct {
            VFixPt<MANTISSA_BITS> x;
            VFixPt<MANTISSA_BITS> y;
            VFixPt<MANTISSA_BITS> z;
            VFixPt<MANTISSA_BITS> w;
        };
    };

public:
    VFixPt4(){};
    ~VFixPt4(){};

    __forceinline static VFixPt4 Zero()
    {
        VFixPt4 tmp;
        tmp.mX =
        tmp.mY =
        tmp.mZ =
        tmp.mW = _mm_setzero_si128();
        return tmp;
    }

    explicit VFixPt4( const float val )
    {
        // TODO: round up?
        if( MANTISSA_BITS > 0 )
        {
            mX = mY = mZ = mW = _mm_set1_epi32( (int)(val*float(1<<MANTISSA_BITS)) );
        }
        else
        {
            mX = mY = mZ = mW = _mm_set1_epi32( (int)val );
        }
    }

    explicit VFixPt4( const int val )
    {
        if( MANTISSA_BITS > 0 )
        {
            mX = mY = mZ = mW = _mm_set1_epi32( val<<MANTISSA_BITS );
        }
        else
        {
            mX = mY = mZ = mW = _mm_set1_epi32( val );
        }
    }

    explicit VFixPt4( const float xx, const float yy, const float zz, const float ww )
    {
        if( MANTISSA_BITS > 0 )
        {
			float bias = 1<<MANTISSA_BITS;
			mX = _mm_set1_epi32( (int)(xx*bias) );
			mY = _mm_set1_epi32( (int)(yy*bias) );
			mZ = _mm_set1_epi32( (int)(zz*bias) );
			mW = _mm_set1_epi32( (int)(ww*bias) );
		}
		else
		{
			mX = _mm_set1_epi32( (int)xx );
			mY = _mm_set1_epi32( (int)yy );
			mZ = _mm_set1_epi32( (int)zz );
			mW = _mm_set1_epi32( (int)ww );
		}
    }

    explicit VFixPt4( const VFloat &v0, const VFloat &v1, const VFloat &v2, const VFloat &v3 )
    {
        if( MANTISSA_BITS > 0 )
        {
            const __m128 bias = _mm_set1_ps(float(1<<MANTISSA_BITS));
            mX = _mm_cvtps_epi32( _mm_mul_ps( v0.mAsVector, bias ) );
            mY = _mm_cvtps_epi32( _mm_mul_ps( v1.mAsVector, bias ) );
            mZ = _mm_cvtps_epi32( _mm_mul_ps( v2.mAsVector, bias ) );
            mW = _mm_cvtps_epi32( _mm_mul_ps( v3.mAsVector, bias ) );
        }
        else
        {
            mX = _mm_cvtps_epi32( v0.mAsVector );
            mY = _mm_cvtps_epi32( v1.mAsVector );
            mZ = _mm_cvtps_epi32( v2.mAsVector );
            mW = _mm_cvtps_epi32( v3.mAsVector );
        }
    }

    explicit VFixPt4( const VInt &v0, const VInt &v1, const VInt &v2, const VInt &v3 )
    {
        if( MANTISSA_BITS > 0 )
        {
			mX = _mm_slli_epi32(v0.mAsVector, MANTISSA_BITS);
			mY = _mm_slli_epi32(v1.mAsVector, MANTISSA_BITS);
			mZ = _mm_slli_epi32(v2.mAsVector, MANTISSA_BITS);
			mW = _mm_slli_epi32(v3.mAsVector, MANTISSA_BITS);
		}
		else
		{
			mX = v0.mAsVector;
			mY = v1.mAsVector;
			mZ = v2.mAsVector;
			mW = v3.mAsVector;
		}
    }

    explicit VFixPt4( const VFloat4 &v0)
    {
        if( MANTISSA_BITS > 0 )
        {
            __m128 bias = _mm_set1_ps(float(1<<MANTISSA_BITS));
            mX = _mm_cvtps_epi32( _mm_mul_ps( v0.mX, bias ) );
            mY = _mm_cvtps_epi32( _mm_mul_ps( v0.mY, bias ) );
            mZ = _mm_cvtps_epi32( _mm_mul_ps( v0.mZ, bias ) );
            mW = _mm_cvtps_epi32( _mm_mul_ps( v0.mW, bias ) );
        }
        else
        {
            mX = _mm_cvtps_epi32( v0.mX );
            mY = _mm_cvtps_epi32( v0.mY );
            mZ = _mm_cvtps_epi32( v0.mZ );
            mW = _mm_cvtps_epi32( v0.mW );
        }
    }

    __forceinline const VFixPt4 operator+( const VFixPt4 &val ) const
    {
        VFixPt4 tmp;
        tmp.mX = _mm_add_epi32( mX, val.mX );
        tmp.mY = _mm_add_epi32( mY, val.mY );
        tmp.mZ = _mm_add_epi32( mZ, val.mZ );
        tmp.mW = _mm_add_epi32( mW, val.mW );
        return tmp;
    }

    __forceinline const VFixPt4 operator-( const VFixPt4 &val ) const
    {
        VFixPt4 tmp;
        tmp.mX = _mm_sub_epi32( mX, val.mX );
        tmp.mY = _mm_sub_epi32( mY, val.mY );
        tmp.mZ = _mm_sub_epi32( mZ, val.mZ );
        tmp.mW = _mm_sub_epi32( mW, val.mW );
        return tmp;
    }

    __forceinline const VFixPt4 operator*( const VFixPt4 &val ) const
    {
        // Multiply.  Keep 32 lsbs.  Multiplying two 28.4 ops gives 24.8 result.
        // Add "1/2", and shift right by four to round to 28.4
        VFixPt4 tmp;
        if( MANTISSA_BITS > 0 )
        {
            __m128i half = _mm_set1_epi32(1<<(MANTISSA_BITS-1));
            tmp.mX = _mm_srai_epi32( _mm_add_epi32( _mm_mullo_epi32( mX, val.mX ), half ), MANTISSA_BITS );
            tmp.mY = _mm_srai_epi32( _mm_add_epi32( _mm_mullo_epi32( mY, val.mY ), half ), MANTISSA_BITS );
            tmp.mZ = _mm_srai_epi32( _mm_add_epi32( _mm_mullo_epi32( mZ, val.mZ ), half ), MANTISSA_BITS );
            tmp.mW = _mm_srai_epi32( _mm_add_epi32( _mm_mullo_epi32( mW, val.mW ), half ), MANTISSA_BITS );
        }
        else
        {
            tmp.mX = _mm_mullo_epi32( mX, val.mX ); // No opportunity to round up - don't have a shift-left operation.
            tmp.mY = _mm_mullo_epi32( mY, val.mY );
            tmp.mZ = _mm_mullo_epi32( mZ, val.mZ );
            tmp.mW = _mm_mullo_epi32( mW, val.mW );
        }
        return tmp;
    }

    __forceinline const VFixPt4 operator*( int val ) const
    {
        VFixPt4 tmp;
        __m128i vv = _mm_set1_epi32( val );
        tmp.mX = _mm_mullo_epi32( mX, vv );
        tmp.mY = _mm_mullo_epi32( mY, vv );
        tmp.mZ = _mm_mullo_epi32( mZ, vv );
        tmp.mW = _mm_mullo_epi32( mW, vv );
        return tmp;
    }
/*
TODO: need to shift the int before add or subtract
    __forceinline const VFixPt4 operator+( const VInt &val ) const
    {
        VFixPt4 tmp;
        tmp.mX = _mm_add_epi32( mX, val.mAsVector );
        tmp.mY = _mm_add_epi32( mY, val.mAsVector );
        tmp.mZ = _mm_add_epi32( mZ, val.mAsVector );
        tmp.mW = _mm_add_epi32( mW, val.mAsVector );
        return tmp;
    }

    __forceinline const VFixPt4 operator-( const VInt &val ) const
    {
        VFixPt4 tmp;
        tmp.mX = _mm_sub_epi32( mX, val.mAsVector );
        tmp.mY = _mm_sub_epi32( mY, val.mAsVector );
        tmp.mZ = _mm_sub_epi32( mZ, val.mAsVector );
        tmp.mW = _mm_sub_epi32( mW, val.mAsVector );
        return tmp;
    }
*/
    __forceinline const VFixPt4 operator*( const VInt &val ) const
    {
        VFixPt4 tmp;
        tmp.mX = _mm_mullo_epi32( mX, val.mAsVector );
        tmp.mY = _mm_mullo_epi32( mY, val.mAsVector );
        tmp.mZ = _mm_mullo_epi32( mZ, val.mAsVector );
        tmp.mW = _mm_mullo_epi32( mW, val.mAsVector );
        return tmp;
    }

}; // VFixPt4

// ******************************************************************
template <UINT MANTISSA_BITS>
class VFixPt3
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
        struct {
            VFixPt<MANTISSA_BITS> x;
            VFixPt<MANTISSA_BITS> y;
            VFixPt<MANTISSA_BITS> z;
        };
    };

public:
    VFixPt3(){};
    ~VFixPt3(){};

    __forceinline static VFixPt3 Zero()
    {
        VFixPt3 tmp;
        tmp.mX =
        tmp.mY =
        tmp.mZ = _mm_setzero_si128();
        return tmp;
    }

    explicit VFixPt3( const float val )
    {
        // TODO: round up?
        if( MANTISSA_BITS > 0 )
        {
            mX = mY = mZ = _mm_set1_epi32( (int)(val*float(1<<MANTISSA_BITS)) );
        }
        else
        {
            mX = mY = mZ = _mm_set1_epi32( (int)val );
        }
    }

    explicit VFixPt3( const int val )
    {
        if( MANTISSA_BITS > 0 )
        {
            mX = mY = mZ = _mm_set1_epi32( val<<MANTISSA_BITS );
        }
        else
        {
            mX = mY = mZ = _mm_set1_epi32( val );
        }
    }

    explicit VFixPt3( const float xx, const float yy, const float zz )
    {
        if( MANTISSA_BITS > 0 )
        {
			float bias = 1<<MANTISSA_BITS;
			mX = _mm_set1_epi32( (int)(xx*bias) );
			mY = _mm_set1_epi32( (int)(yy*bias) );
			mZ = _mm_set1_epi32( (int)(zz*bias) );
		}
		else
		{
			mX = _mm_set1_epi32( (int)xx );
			mY = _mm_set1_epi32( (int)yy );
			mZ = _mm_set1_epi32( (int)zz );
		}
    }

    explicit VFixPt3( const VFloat &v0, const VFloat &v1, const VFloat &v2 )
    {
        if( MANTISSA_BITS > 0 )
        {
            const __m128 bias = _mm_set1_ps(float(1<<MANTISSA_BITS));
            mX = _mm_cvtps_epi32( _mm_mul_ps( v0.mAsVector, bias ) );
            mY = _mm_cvtps_epi32( _mm_mul_ps( v1.mAsVector, bias ) );
            mZ = _mm_cvtps_epi32( _mm_mul_ps( v2.mAsVector, bias ) );
        }
        else
        {
            mX = _mm_cvtps_epi32( v0.mAsVector );
            mY = _mm_cvtps_epi32( v1.mAsVector );
            mZ = _mm_cvtps_epi32( v2.mAsVector );
        }
    }

    explicit VFixPt3( const VInt &v0, const VInt &v1, const VInt &v2 )
    {
        if( MANTISSA_BITS > 0 )
        {
			mX = _mm_slli_epi32(v0.mAsVector, MANTISSA_BITS);
			mY = _mm_slli_epi32(v1.mAsVector, MANTISSA_BITS);
			mZ = _mm_slli_epi32(v2.mAsVector, MANTISSA_BITS);
		}
		else
		{
			mX = v0.mAsVector;
			mY = v1.mAsVector;
			mZ = v2.mAsVector;
		}
    }

	// TODO: What about fixed-point numbers with different radix point?
    explicit VFixPt3( const VFixPt<MANTISSA_BITS> &v0, const VFixPt<MANTISSA_BITS> &v1, const VFixPt<MANTISSA_BITS> &v2 )
    {
		mX = v0.mAsVector;
		mY = v1.mAsVector;
		mZ = v2.mAsVector;
    }

    explicit VFixPt3( const VFloat3 &v0)
    {
        if( MANTISSA_BITS > 0 )
        {
            __m128 bias = _mm_set1_ps(float(1<<MANTISSA_BITS));
            mX = _mm_cvtps_epi32( _mm_mul_ps( v0.mX, bias ) );
            mY = _mm_cvtps_epi32( _mm_mul_ps( v0.mY, bias ) );
            mZ = _mm_cvtps_epi32( _mm_mul_ps( v0.mZ, bias ) );
        }
        else
        {
            mX = _mm_cvtps_epi32( v0.mX );
            mY = _mm_cvtps_epi32( v0.mY );
            mZ = _mm_cvtps_epi32( v0.mZ );
        }
    }

    __forceinline const VFixPt3 ExtractLaneAsSIMD( int lane )
    {
        VFixPt3 tmp;
        tmp.x = x.ExtractLaneAsSIMD(lane);
        tmp.y = y.ExtractLaneAsSIMD(lane);
        tmp.z = z.ExtractLaneAsSIMD(lane);
        return tmp;
    }

    __forceinline const VFixPt3 operator+( const VFixPt3 &val ) const
    {
        VFixPt3 tmp;
        tmp.mX = _mm_add_epi32( mX, val.mX );
        tmp.mY = _mm_add_epi32( mY, val.mY );
        tmp.mZ = _mm_add_epi32( mZ, val.mZ );
        return tmp;
    }

    __forceinline const VFixPt3 operator-( const VFixPt3 &val ) const
    {
        VFixPt3 tmp;
        tmp.mX = _mm_sub_epi32( mX, val.mX );
        tmp.mY = _mm_sub_epi32( mY, val.mY );
        tmp.mZ = _mm_sub_epi32( mZ, val.mZ );
        return tmp;
    }

    __forceinline const VFixPt3 operator*( const VFixPt3 &val ) const
    {
        // Multiply.  Keep 32 lsbs.  Multiplying two 28.4 ops gives 24.8 result.
        // Add "1/2", and shift right by four to round to 28.4
        VFixPt3 tmp;
        if( MANTISSA_BITS > 0 )
        {
            __m128i half = _mm_set1_epi32(1<<(MANTISSA_BITS-1));
            tmp.mX = _mm_srai_epi32( _mm_add_epi32( _mm_mullo_epi32( mX, val.mX ), half ), MANTISSA_BITS );
            tmp.mY = _mm_srai_epi32( _mm_add_epi32( _mm_mullo_epi32( mY, val.mY ), half ), MANTISSA_BITS );
            tmp.mZ = _mm_srai_epi32( _mm_add_epi32( _mm_mullo_epi32( mZ, val.mZ ), half ), MANTISSA_BITS );
        }
        else
        {
            tmp.mX = _mm_mullo_epi32( mX, val.mX ); // No opportunity to round up - don't have a shift-left operation.
            tmp.mY = _mm_mullo_epi32( mY, val.mY );
            tmp.mZ = _mm_mullo_epi32( mZ, val.mZ );
        }
        return tmp;
    }

    __forceinline const VFixPt3 operator*( int val ) const
    {
        VFixPt3 tmp;
        __m128i vv = _mm_set1_epi32( val );
        tmp.mX = _mm_mullo_epi32( mX, vv );
        tmp.mY = _mm_mullo_epi32( mY, vv );
        tmp.mZ = _mm_mullo_epi32( mZ, vv );
        return tmp;
    }
/*
TODO: need to shift the int before add or subtract
    __forceinline const VFixPt3 operator+( const VInt &val ) const
    {
        VFixPt3 tmp;
        tmp.mX = _mm_add_epi32( mX, val.mAsVector );
        tmp.mY = _mm_add_epi32( mY, val.mAsVector );
        tmp.mZ = _mm_add_epi32( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline const VFixPt3 operator-( const VInt &val ) const
    {
        VFixPt3 tmp;
        tmp.mX = _mm_sub_epi32( mX, val.mAsVector );
        tmp.mY = _mm_sub_epi32( mY, val.mAsVector );
        tmp.mZ = _mm_sub_epi32( mZ, val.mAsVector );
        return tmp;
    }
*/
    __forceinline const VFixPt3 operator*( const VInt &val ) const
    {
        VFixPt3 tmp;
        tmp.mX = _mm_mullo_epi32( mX, val.mAsVector );
        tmp.mY = _mm_mullo_epi32( mY, val.mAsVector );
        tmp.mZ = _mm_mullo_epi32( mZ, val.mAsVector );
        return tmp;
    }

    __forceinline const VFixPt3 operator<<( int ii )
    {
        VFixPt3 tmp;
        tmp.x = x << ii;
        tmp.x = y << ii;
        tmp.x = z << ii;
        return tmp;
    }

}; // VFixPt3

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

__forceinline VFloat operator-( float v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_sub_ps( _mm_set1_ps(v0), v1.mAsVector );
    return tmp;
}

__forceinline VFloat operator*( float v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_mul_ps( _mm_set1_ps(v0), v1.mAsVector );
    return tmp;
}

__forceinline VFloat Max( float v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_max_ps( _mm_set1_ps(v0), v1.mAsVector );
    return tmp;
}

__forceinline VFloat Min( float v0, const VFloat &v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_min_ps( _mm_set1_ps(v0), v1.mAsVector );
    return tmp;
}

__forceinline VFloat Max( const VFloat &v0, float v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_max_ps( v0.mAsVector, _mm_set1_ps(v1) );
    return tmp;
}

__forceinline VFloat operator/( float num, VFloat den )
{
    VFloat tmp;
    tmp.mAsVector = _mm_div_ps( _mm_set1_ps(num), den.mAsVector );
    return tmp;
}

__forceinline VInt Max( const VInt &v0, int v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_max_epi32( v0.mAsVector, _mm_set1_epi32(v1) );
    return tmp;
}

__forceinline VInt Min( const VInt &v0, int v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_min_epi32( v0.mAsVector, _mm_set1_epi32(v1) );
    return tmp;
}

__forceinline VFloat ceil( VFloat v0 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_ceil_ps( v0.mAsVector );
    return tmp;
}

__forceinline VFloat cmpge( VFloat v0, float v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmpge_ps( v0.mAsVector, _mm_set1_ps(v1) );
    return tmp;
}

__forceinline VFloat cmpge( VFloat v0, VFloat v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmpge_ps( v0.mAsVector, v1.mAsVector );
    return tmp;
}

template <UINT MANTISSA_BITS>
__forceinline VInt cmpgt( VFixPt<MANTISSA_BITS> v0, VFixPt<MANTISSA_BITS>  v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_cmpgt_epi32( v0.mAsVector, v1.mAsVector );
    return tmp;
}

template <UINT MANTISSA_BITS>
__forceinline VInt cmplt( VFixPt<MANTISSA_BITS> v0, VFixPt<MANTISSA_BITS>  v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_cmplt_epi32( v0.mAsVector, v1.mAsVector );
    return tmp;
}

__forceinline VFloat cmpgt( VFloat v0, float v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmpgt_ps( v0.mAsVector, _mm_set1_ps(v1) );
    return tmp;
}

__forceinline VFloat cmpgt( VFloat v0, VFloat v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmpgt_ps( v0.mAsVector, v1.mAsVector );
    return tmp;
}

__forceinline VFloat cmplt( VFloat v0, float v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmplt_ps( v0.mAsVector, _mm_set1_ps(v1) );
    return tmp;
}

__forceinline VFloat cmple( VFloat v0, float v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_cmple_ps( v0.mAsVector, _mm_set1_ps(v1) );
    return tmp;
}

__forceinline VInt cmpgt( VInt v0, int v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_cmpgt_epi32( v0.mAsVector, _mm_set1_epi32(v1) );
    return tmp;
}

__forceinline VInt cmpgt( int v0, VInt v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_cmpgt_epi32( _mm_set1_epi32(v0), v1.mAsVector );
    return tmp;
}

__forceinline VInt cmpeq( VInt v0, int v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_cmpeq_epi32( v0.mAsVector, _mm_set1_epi32(v1) );
    return tmp;
}

__forceinline VInt cmplt( VInt v0, int v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_cmplt_epi32( v0.mAsVector, _mm_set1_epi32(v1) );
    return tmp;
}

__forceinline VFloat blend( VFloat v0, VFloat v1, VFloat mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( v0.mAsVector, v1.mAsVector, mask.mAsVector );
    return tmp;
}

__forceinline VFloat blend( VFloat v0, VFloat v1, VInt mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( v0.mAsVector, v1.mAsVector, _mm_castsi128_ps(mask.mAsVector) );
    return tmp;
}

__forceinline VFloat blend( VFloat v0, float v1, VFloat mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( v0.mAsVector, _mm_set1_ps(v1), mask.mAsVector );
    return tmp;
}

__forceinline VFloat blend( float v0, VFloat v1, VFloat mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( _mm_set1_ps(v0), v1.mAsVector, mask.mAsVector );
    return tmp;
}

__forceinline VFloat blend( float v0, VFloat v1, VInt mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( _mm_set1_ps(v0), v1.mAsVector, _mm_castsi128_ps(mask.mAsVector) );
    return tmp;
}

__forceinline VInt blend( VInt v0, VInt v1, VInt mask )
{
    VInt tmp;
    tmp.mAsVector = _mm_blendv_epi8( v0.mAsVector, v1.mAsVector, mask.mAsVector );
    return tmp;
}

__forceinline VInt blend( VInt v0, VInt v1, VFloat mask )
{
    VInt tmp;
    tmp.mAsVector = _mm_castps_si128(_mm_blendv_ps( _mm_castsi128_ps(v0.mAsVector), _mm_castsi128_ps(v1.mAsVector), mask.mAsVector) );
    return tmp;
}

__forceinline VInt blend( int v0, VInt v1, VInt mask )
{
    VInt tmp;
    tmp.mAsVector = _mm_castps_si128(_mm_blendv_ps( _mm_castsi128_ps(_mm_set1_epi32(v0)), _mm_castsi128_ps(v1.mAsVector), _mm_castsi128_ps(mask.mAsVector)) );
    return tmp;
}

__forceinline VInt blend( VInt v0, int v1, VInt mask )
{
    VInt tmp;
    tmp.mAsVector = _mm_castps_si128(_mm_blendv_ps( _mm_castsi128_ps(v0.mAsVector), _mm_castsi128_ps(_mm_set1_epi32(v1)), _mm_castsi128_ps(mask.mAsVector)) );
    return tmp;
}

__forceinline VInt blend( VInt v0, int v1, VFloat mask )
{
    VInt tmp;
    tmp.mAsVector = _mm_castps_si128(_mm_blendv_ps( _mm_castsi128_ps(v0.mAsVector), _mm_set1_ps((float)v1), mask.mAsVector ));
    return tmp;
}

__forceinline VFloat blend( float v0, float v1, VInt mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( _mm_set1_ps(v0), _mm_set1_ps(v1), _mm_castsi128_ps(mask.mAsVector) );
    return tmp;
}

__forceinline VFloat blend( float v0, float v1, VFloat mask )
{
    VFloat tmp;
    tmp.mAsVector = _mm_blendv_ps( _mm_set1_ps(v0), _mm_set1_ps(v1), mask.mAsVector );
    return tmp;
}

__forceinline VInt blend( UINT v0, UINT v1, VFloat mask )
{
    VInt tmp;
    tmp.mAsVector = _mm_blendv_epi8( _mm_set1_epi32(v0), _mm_set1_epi32(v1), _mm_castps_si128(mask.mAsVector ));
    return tmp;
}

__forceinline VInt blend( int v0, VInt v1, VFloat mask )
{
    VInt tmp;
    tmp.mAsVector = _mm_blendv_epi8( _mm_set1_epi32(v0), v1.mAsVector, _mm_castps_si128( mask.mAsVector) );
    return tmp;
}

__forceinline VFloat operator&( const VFloat v0, const VInt &val )
{
    VFloat tmp;
    tmp.mAsVector = _mm_and_ps( v0.mAsVector, _mm_castsi128_ps(val.mAsVector) );
    return tmp;
}

__forceinline VFloat operator*( const VFloat v0, const VInt v1 )
{
    VFloat tmp;
    tmp.mAsVector = _mm_mul_ps( v0.mAsVector, _mm_cvtepi32_ps(v1.mAsVector) );
    return tmp;
}


__forceinline VFloat::VFloat( const VInt v0 )
{
    mAsVector = _mm_cvtepi32_ps( v0.mAsVector );
}


template <UINT MANTISSA_BITS>
__forceinline VFloat::VFloat( const VFixPt<MANTISSA_BITS> v0 )
{
    if( MANTISSA_BITS > 0 )
    {
        mAsVector = _mm_mul_ps( _mm_cvtepi32_ps( v0.mAsVector ), _mm_set1_ps(1.0f/float(1<<MANTISSA_BITS)) );
    }
    else
    {
        mAsVector = _mm_cvtepi32_ps( v0.mAsVector );
    }
}

template <UINT MANTISSA_BITS>
__forceinline  VInt::VInt( const VFixPt<MANTISSA_BITS> &v0 )
{
    if( MANTISSA_BITS > 0 )
    {
        mAsVector = _mm_srai_epi32( v0.mAsVector, MANTISSA_BITS );
    }
    else
    {
        mAsVector = v0.mAsVector;
    }
}

template <UINT MANTISSA_BITS>
__forceinline VFloat operator*( VFixPt<MANTISSA_BITS> &v0, VFloat &v1 )
{
    VFloat tmp;
    if( MANTISSA_BITS > 0 )
    {
        VFloat v1DivFixedPoint( v1*(1.0f/float(1<<MANTISSA_BITS)) );
        tmp.mAsVector = _mm_mul_ps( _mm_cvtepi32_ps(v0.mAsVector), v1DivFixedPoint.mAsVector );
    }
    else
    {
        tmp.mAsVector = _mm_mul_ps( _mm_cvtepi32_ps(v0.mAsVector), v1.mAsVector );
    }
    return tmp;
}

__forceinline VInt operator-( const int v0, const VInt &v1 )
{
    VInt tmp;
    tmp.mAsVector = _mm_sub_epi32( _mm_set1_epi32(v0), v1.mAsVector );
    return tmp;
}

/*
__forceinline VInt operator<<( const int val, const VInt &count )
{
    VInt tmp(
        val << count.mAsVector.m128i_i32[3],
        val << count.mAsVector.m128i_i32[2],
        val << count.mAsVector.m128i_i32[1],
        val << count.mAsVector.m128i_i32[0]
    );
    return tmp;
}
*/

template<UINT MANTISSA_BITS>
__forceinline VFixPt<MANTISSA_BITS> Min( VFixPt<MANTISSA_BITS> v0, VFixPt<MANTISSA_BITS> v1 )
{
    VFixPt<MANTISSA_BITS> tmp;
    tmp.mAsVector = _mm_min_epi32( v0.mAsVector, v1.mAsVector );
    return tmp;
}

template<UINT MANTISSA_BITS>
__forceinline VFixPt<MANTISSA_BITS> Max( VFixPt<MANTISSA_BITS> v0, VFixPt<MANTISSA_BITS> v1 )
{
    VFixPt<MANTISSA_BITS> tmp;
    tmp.mAsVector = _mm_max_epi32( v0.mAsVector, v1.mAsVector );
    return tmp;
}

template<UINT MANTISSA_BITS>
__forceinline VFixPt<MANTISSA_BITS> Max( const VFixPt<MANTISSA_BITS> &v0, int v1 )
{
    VFixPt<MANTISSA_BITS> tmp;
    if( MANTISSA_BITS > 0 )
    {
        tmp.mAsVector = _mm_max_epi32( v0.mAsVector, _mm_set1_epi32( v1<<MANTISSA_BITS ) );
    }
    else
    {
        tmp.mAsVector = _mm_max_epi32( v0.mAsVector, _mm_set1_epi32( v1 ) );
    }
    return tmp;
}

template<UINT MANTISSA_BITS>
__forceinline VFixPt<MANTISSA_BITS> Min( const VFixPt<MANTISSA_BITS> &v0, int v1 )
{
    VFixPt<MANTISSA_BITS> tmp;
    if( MANTISSA_BITS > 0 )
    {
        tmp.mAsVector = _mm_min_epi32( v0.mAsVector, _mm_set1_epi32( v1<<MANTISSA_BITS ) );
    }
    else
    {
        tmp.mAsVector = _mm_min_epi32( v0.mAsVector, _mm_set1_epi32( v1 ) );
    }
    return tmp;
}

