#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include "vector3.hpp"

namespace ora
{
    typedef uint32 Outcode;
    const Outcode  OUTCODE_LEFT		= 0x1;	///< Beyond left plane.
    const Outcode  OUTCODE_RIGHT	= 0x2;	///< Beyond right plane.
    const Outcode  OUTCODE_BOTTOM	= 0x4;	///< Beyond bottom plane.
    const Outcode  OUTCODE_TOP		= 0x8;	///< Beyond top plane.
    const Outcode  OUTCODE_NEAR		= 0x10;	///< Beyond near plane.
    const Outcode  OUTCODE_FAR		= 0x20;	///< Beyond far plane.
    const Outcode  OUTCODE_MASK		= OUTCODE_LEFT | \
        OUTCODE_RIGHT | \
        OUTCODE_BOTTOM | \
        OUTCODE_TOP | \
        OUTCODE_NEAR | \
        OUTCODE_FAR;	///< Combination of all outcodes.


    /**
     *	This class implements a vector of four floats.
     *
     *	@ingroup Math
     */
    class Vector4
    {
    public:

        float x, y, z, w;

        Vector4();
        Vector4( float x_, float y_, float z_, float w_ );
        Vector4( const Vector3 & v, float w );
#ifdef SSE_MATH
        Vector4( __m128 v4 );
#endif

        // Use the default compiler implementation for these methods. It is faster.
        //	Vector4( const Vector4& v);
        //	Vector4& operator = ( const Vector4& v );

        void setZero();
        void set( float a, float b, float c, float d ) ;
        void scale( const Vector4& v, float s );
        void scale( float s );
        void parallelMultiply( const Vector4& v );
        float length() const;
        float lengthSquared() const;
        void normalise();
        Vector4 unitVector() const;
        Outcode calculateOutcode() const;

        float dotProduct( const Vector4& v ) const;

        INLINE void operator += ( const Vector4& v);
        INLINE void operator -= ( const Vector4& v);
        INLINE void operator *= ( const Vector4& v);
        INLINE void operator /= ( const Vector4& v);
        INLINE void operator *= ( float s);

        operator float *()				{ return (float *)&x; }
        operator const float *() const	{ return (float *)&x; }

        static const Vector4 & zero()	{ return s_zero; }

    private:
        friend std::ostream& operator <<( std::ostream&, const Vector4& );
        friend std::istream& operator >>( std::istream&, Vector4& );

        // This is to prevent construction like:
        //	Vector4( 0 );
        // It would interpret this as a float * and later crash.
        Vector4( int value );

        static Vector4	s_zero;
    };

    INLINE Vector4 operator +( const Vector4& v1, const Vector4& v2 );
    INLINE Vector4 operator -( const Vector4& v1, const Vector4& v2 );
    INLINE Vector4 operator *( const Vector4& v1, const Vector4& v2 );
    INLINE Vector4 operator /( const Vector4& v1, const Vector4& v2 );
    INLINE Vector4 operator *( const Vector4& v, float s );
    INLINE Vector4 operator *( float s, const Vector4& v );
    INLINE Vector4 operator /( const Vector4& v, float s );
    INLINE bool operator   ==( const Vector4& v1, const Vector4& v2 );
    INLINE bool operator   !=( const Vector4& v1, const Vector4& v2 );
    INLINE bool operator   < ( const Vector4& v1, const Vector4& v2 );

    inline
    bool operator   > ( const Vector4& v1, const Vector4& v2 ) { return v2 < v1; }
    inline
    bool operator   >=( const Vector4& v1, const Vector4& v2 ) { return !(v1 < v2); }
    inline
    bool operator   <=( const Vector4& v1, const Vector4& v2 ) { return !(v2 < v1); }

    INLINE bool almostEqual( const Vector4& v1, const Vector4& v2, float epsilon );

} // end namespace ora

#ifdef CODE_INLINE
#include "vector4.ipp"
#endif

#endif // VECTOR4_HPP

// vector4.hpp
