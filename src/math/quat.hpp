#ifndef QUAT_HPP
#define QUAT_HPP

#include "matrix.hpp"

namespace ora
{
    /**
     *	This class is used to represent a quaternion. Quaternions are useful when
     *	working with angles in 3 dimensions.
     *
     *	@ingroup Math
     */
    class Quaternion
    {
    public:

        float x, y, z, w;

        /// @name Construction/Destruction
        //@{
        Quaternion();
        Quaternion( const Matrix &m );
        Quaternion( float x, float y, float z, float w );
        Quaternion( const Vector3 &v, float w );
        //@}

        void			setZero();
        void            setIdentity();
        void			set( float x, float y, float z, float w );
        void			set( const Vector3 &v, float w );

        void			fromAngleAxis( float angle, const Vector3 &axis );

        void			fromMatrix( const Matrix &m );

        void			normalise();
        void			invert();
        void			minimise();

        void			slerp( const Quaternion& qStart, const Quaternion &qEnd,
                               float t );

        void			multiply( const Quaternion& q1, const Quaternion& q2 );
        void			preMultiply( const Quaternion& q );
        void			postMultiply( const Quaternion& q );

        float			dotProduct( const Quaternion& q ) const;
        float			length() const;
        float			lengthSquared() const;

        operator float *()				{ return (float *)&x; }
        operator const float *() const	{ return (float *)&x; }

        static const Quaternion& identity() { return s_identity; }
        static const Quaternion& zero(){ return s_zero; }

        bool isIdentity() const;
        bool isZero() const;


    private:
        static const Quaternion s_identity;
        static const Quaternion s_zero;
    };

    Quaternion  operator *( const Quaternion& q1, const Quaternion& q2 );
    bool		operator ==( const Quaternion& q1, const Quaternion& q2 );

} // end namespace ora

#ifdef CODE_INLINE
#include "quat.ipp"
#endif


#endif // QUAT_HPP
/*quat.hpp*/
