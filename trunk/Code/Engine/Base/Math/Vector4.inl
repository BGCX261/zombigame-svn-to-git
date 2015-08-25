//-----------------------------------------------------------------------
// Vector4 inline
/// Definiciones de funciones inline de la clase 'Vector4'
/// Este fichero es realmente parte de la cabecera 'Vector4.h' 
//-----------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Costructor versi�n 1
/// Construcci�n sin inicializaci�n de par�metros  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>::Vector4 ()
{
}
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor versi�n 2
/// Constructor de copia
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>::Vector4 (const Vector4<T>& otro)
{
  (*this) = otro;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor versi�n 3
/// A partir de un vector 3D. La componente w se iniciar� a cero
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>::Vector4 (const Vector3<T>& otro)
{
  x = otro.x;
  y = otro.y;
  z = otro.z;
  w = Zero<T>();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor versi�n 4
/// Constructor a partir de un Vector 3D y un escalar para la componente 'w' 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>::Vector4 (const Vector3<T>& otro, const T tw)
{
  x = otro.x;
  y = otro.y;
  z = otro.z;
  w = tw;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor versi�n 5
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>::Vector4 (const T tx, const T ty, const T tz, const T tw)
{
  x = tx;
  y = ty;
  z = tz;
  w = tw;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor versi�n 6: a partir de un escalar que se establece en las 4 componentes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>::Vector4 (const T escalar)
{
  x = escalar;
  y = escalar;
  z = escalar;
  w = escalar;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico: suma de vectores
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> Vector4<T>::operator + (const Vector4<T>& otro) const
{
  return (Vector4<T>(x + otro.x,
                     y + otro.y,
                     z + otro.z,
                     w + otro.w));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico: resta de vectores
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> Vector4<T>::operator - (const Vector4<T>& otro) const
{
  return (Vector4<T>(x - otro.x,
                     y - otro.y,
                     z - otro.z,
                     w - otro.w));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico: producto vector x escalar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> Vector4<T>::operator * (const T escalar) const
{
  return (Vector4<T>(x * escalar,
                     y * escalar,
                     z * escalar,
                     w * escalar)); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico: cociente vector / escalar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> Vector4<T>::operator / (const T escalar) const
{
#ifdef CHECK_MATH_SINGULARITY
  //--------------------------------------------------------<<<
  // Con chequeo de divisi�n por cero
  Vector4<T> retVector(*this);

  ASSERTMSG(escalar != Zero<T>(), "Divisi�n por cero en cociente vector-escalar");
  if(escalar != Zero<T>())
  {
    T inv_escalar = One<T>() / escalar;
    retVector.x *= inv_escalar;
    retVector.y *= inv_escalar;
    retVector.z *= inv_escalar;
    retVector.w *= inv_escalar;
  }
  
  return retVector;
  //-------------------------------------------------------->>>
#else
  //--------------------------------------------------------<<<�
  // Sin chequeo
  T inv_escalar = One<T>() / escalar;
  return (Vector4<T>(x * inv_escalar,
                     y * inv_escalar,
                     z * inv_escalar,
                     w * inv_escalar)); 
  //-------------------------------------------------------->>>
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico: suma de un escalar a las cuatro componentes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> Vector4<T>::operator + (const T escalar) const
{
  return Vector4<T>(x + escalar,
                    y + escalar,
                    z + escalar,
                    w + escalar);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Funci�n externa operador aritm�tico: suma de un escalar
/// a las cuatro componentes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> operator + (const T escalar, const Vector4<T>& vector)
{
  return Vector4<T>(vector.x + escalar,
                    vector.y + escalar,
                    vector.z + escalar,
                    vector.w + escalar);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico: resta de un escalar a las tres componentes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> Vector4<T>::operator - (const T escalar) const
{
  return Vector4<T>(x - escalar,
                    y - escalar,
                    z - escalar,
                    w - escalar);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Funci�n externa operador aritm�tico: resta de las componentes a
/// un escalar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> operator - (const T escalar, const Vector4<T>& vector)
{
  return Vector4<T>(escalar - vector.x,
                    escalar - vector.y,
                    escalar - vector.z,
                    escalar - vector.w);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico: cambio de signo
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> Vector4<T>::operator - () const
{
  return (Vector4<T>(-x, -y, -z, -w));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico: signo positivo 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>& Vector4<T>::operator + ()
{
  return (*this); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico: signo positivo (versi�n const)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const Vector4<T>& Vector4<T>::operator + () const
{
  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Funci�n externa operador aritm�tico: producto escalar x vector 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> operator * (const T escalar, const Vector4<T>& otro)
{
  return (Vector4<T>(escalar * otro.x,
                     escalar * otro.y,
                     escalar * otro.z,
                     escalar * otro.w)); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Funci�n externa operador aritm�tico: cociente escalar / vector
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> operator / (const T escalar, const Vector4<T>& otro)
{
#ifdef CHECK_MATH_SINGULARITY
  //--------------------------------------------------------<<<
  // Con chequeo de divisi�n por cero
  Vector4<T> retVector(escalar);

  ASSERTMSG(otro.x != Zero<T>() &&
            otro.y != Zero<T>() &&
            otro.z != Zero<T>() &&
            otro.x != Zero<T>(),
            "Divisi�n por cero en cociente escalar-vector");
  if(otro.x != Zero<T>())
  {
    retVector.x /= otro.x;
  }
  if(otro.y != Zero<T>())
  {
    retVector.y /= otro.y;
  }
  if(otro.z != Zero<T>())
  {
    retVector.z /= otro.z;
  }
  if(otro.w != Zero<T>())
  {
    retVector.w /= otro.w;
  }

  return retVector;
  //-------------------------------------------------------->>>
#else
  //--------------------------------------------------------<<<
  // Sin chequeo
  return (Vector4<T>(escalar / otro.x,
                     escalar / otro.y,
                     escalar / otro.z,
                     escalar / otro.w)); 
  //-------------------------------------------------------->>>
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico de actualizaci�n: incremento
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>& Vector4<T>::operator += (const Vector4<T>& otro)
{
  x += otro.x;
  y += otro.y;
  z += otro.z;
  w += otro.w;

  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico de actualizaci�n: decremento
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>& Vector4<T>::operator -= (const Vector4<T>& otro)
{
  x -= otro.x;
  y -= otro.y;
  z -= otro.z;
  w -= otro.w;

  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico de actualizaci�n: vector x escalar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>& Vector4<T>::operator *= (const T escalar)
{
  x *= escalar;
  y *= escalar;
  z *= escalar;
  w *= escalar;

  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico de actualizaci�n: vector / escalar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>& Vector4<T>::operator /= (const T escalar)
{
#ifdef CHECK_MATH_SINGULARITY
  //-----------------------------------------------------<<<
  ASSERTMSG(escalar != Zero<T>(), "Divisi�n por cero en cociente de matriz por escalar");
  if(escalar != Zero<T>())
  {
    T inv_escalar = One<T>() / escalar;
    x *= inv_escalar;
    y *= inv_escalar;
    z *= inv_escalar;
    w *= inv_escalar;
  }
  //----------------------------------------------------->>>
#else
  //-----------------------------------------------------<<<
  T inv_escalar = One<T>() / escalar;
  x *= inv_escalar;
  y *= inv_escalar;
  z *= inv_escalar;
  w *= inv_escalar;
  //----------------------------------------------------->>>
#endif 
  
  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico de actualizaci�n: vector + escalar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>& Vector4<T>::operator += (const T escalar)
{
  x += escalar;
  y += escalar;
  z += escalar;
  w += escalar;

  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador aritm�tico de actualizaci�n: vector - escalar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>& Vector4<T>::operator -= (const T escalar)
{
  x -= escalar;
  y -= escalar;
  z -= escalar;
  w -= escalar;

  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador de asignaci�n de componentes par�ntesis
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>& Vector4<T>::operator () (const T tx, const T ty, const T tz, const T tw)
{
  x = tx;
  y = ty;
  z = tz;
  w = tw;

  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Funci�n de asignaci�n de componentes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void Vector4<T>::Set (const T tx, const T ty, const T tz, const T tw)
{
  x = tx;
  y = ty;
  z = tz;
  w = tw;
}
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Establece el vector a  [0, 0, 0, 0]
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void Vector4<T>::SetZero ()
{
  x = Zero<T>();
  y = Zero<T>();
  z = Zero<T>();
  w = Zero<T>();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador vectorial: producto escalar (dot product)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T Vector4<T>::operator * (const Vector4<T>& otro) const
{
  return (x * otro.x + y * otro.y + z * otro.z + w * otro.w);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador de igualdad absoluto
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool Vector4<T>::operator == (const Vector4<T>& otro) const
{
  return (x == otro.x &&
          y == otro.y &&
          z == otro.z &&
          w == otro.w);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador de desigualdad absoluto
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool Vector4<T>::operator != (const Vector4<T>& otro) const
{
      return (x != otro.x ||
              y != otro.y ||
              z != otro.z ||
              w != otro.w);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador de igualdad con epsilon global
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool Vector4<T>::IsEqualEpsilon (const Vector4<T>& otro) const
{
  return (mathUtils::Compare(x, otro.x) == 0 &&
          mathUtils::Compare(y, otro.y) == 0 &&
          mathUtils::Compare(z, otro.z) == 0 &&
          mathUtils::Compare(w, otro.w) == 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador de desigualdad con epsilon global
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool Vector4<T>::IsNotEqualEpsilon (const Vector4<T>& otro) const
{
  return (mathUtils::Compare(x, otro.x) != 0 ||
          mathUtils::Compare(y, otro.y) != 0 ||
          mathUtils::Compare(z, otro.z) != 0 ||
          mathUtils::Compare(w, otro.w) != 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Producto por componentes (escalado). Versi�n que modifica el vector
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector2<T>& Vector4<T>::Scale (const Vector2<T>& otro)
{
  x *= otro.x;
  y *= otro.y;
  z *= otro.z;
  w *= otro.w;

  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Producto por componentes (escalado). Versi�n que devuelve un vector modificado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector2<T> Vector4<T>::GetScaled (const Vector2<T>& otro) const
{
  return Vector3<T>(x * otro.x, y * otro.y, z * otro.z, w * otro.w);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Cambia cada componente del vector actual por la correspondiente del vector pasado en el par�metro si
/// esta es menor (su tipo devuelve 'true' al operador '<')
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const Vector2<T>& Vector4<T>::SetIfMinComponents (const Vector2<T>& otro)
{
  if(otro.x < x)
  {
    x = otro.x;
  }
  if(otro.y < y)
  {
    y = otro.y;
  }
  if(otro.z < z)
  {
    z = otro.z;
  }
  if(otro.w < w)
  {
    w = otro.w;
  }

  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Cambia cada componente del vector actual por la correspondiente del vector pasado en el par�metro si
/// esta es mayor (su tipo devuelve 'true' al operador '>')
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const Vector2<T>& Vector4<T>::SetIfMaxComponents (const Vector2<T>& otro)
{
  if(otro.x > x)
  {
    x = otro.x;
  }
  if(otro.y > y)
  {
    y = otro.y;
  }
  if(otro.z > z)
  {
    z = otro.z;
  }
  if(otro.w > w)
  {
    w = otro.w;
  }

  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador de acceso []
/// (Versi�n const)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T Vector4<T>::operator [] (int i) const
{
  return ((T*)this)[i];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operador de acceso []
/// (Versi�n no const)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T& Vector4<T>::operator [] (int i)
{
  return ((T*)this)[i];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Funci�n de normalizaci�n
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>& Vector4<T>::Normalize (const T tk)
{
#ifdef CHECK_MATH_SINGULARITY
  //--------------------------------------------<<<
  // Con chequeo de divisi�n por cero
  T length = Length();

  ASSERTMSG(length != Zero<T>(), "Divisi�n por cero en normalizaci�n de vector");
  if(length != Zero<T>())
  {
    T aux = tk / length;
    x *= aux;
    y *= aux;
    z *= aux;
    w *= aux;
  }
  //-------------------------------------------->>>
#else
  //--------------------------------------------<<<
  // Sin chequeo
  T aux = tk / Lenght(); 
  x *= aux;
  y *= aux;
  z *= aux;
  w *= aux;
  //-------------------------------------------->>>
#endif
  
  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Devuelve el vector normalizado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> Vector4<T>::GetNormalized () const
{
  return Vector4<T>(*this).Normalize();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Longitud
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T Vector4<T>::Length () const
{
  return ((T)sqrt(x * x + y * y + z * z + w * w));
}
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Longitud al cuadrado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T Vector4<T>::SquaredLength () const
{
  return (x * x + y * y + z * z + w * w);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Interpolaci�n lineal entre el vector actual y el pasado en el par�metro
/// usando t como 'lambda', teniendo que si:
///    t=0 --> actual
///    t=1 --> otro
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T>& Vector4<T>::Lerp (const Vector4<T>& otro, const T t)
{
  x += (otro.x - x) * t;
  y += (otro.y - y) * t;
  z += (otro.z - z) * t;
  w += (otro.w - w) * t;

  return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Interpolaci�n lineal entre el vector actual y el pasado en el par�metro
/// usando t como 'lambda', teniendo que si:
///    t=0 --> actual
///    t=1 --> otro
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector4<T> Vector4<T>::GetLerp (const Vector4<T>& otro, const T t) const
{
  return Vector4<T>(*this).Lerp(otro, t);
}
