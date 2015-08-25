#pragma once 
#ifndef __RECYCLING_ARRAY_H__
#define __RECYCLING_ARRAY_H__

#include "base.h"
#include "BaseControl.h"

template<class T>

class CRecyclingArray: public CBaseControl
{
  public:
  //constructor
  CRecyclingArray(uint32 _uiMax):
                  m_uiUsedElements(0),m_uiFreeElements(_uiMax),m_uiTotalElements(_uiMax),
                  m_vRecyclingArray(0),m_vRecyclingArrayStatus(0)
                  { Init(); };
  
  //destructor                
  ~CRecyclingArray() { Done(); };

  //Devuelve numero de elementos libres en el array
  const uint32 GetNumFreeElements() const { return m_uiFreeElements; };
  
  //Devuelve numero de elementos ocupados en el array
  const uint32 GetNumUsedElements() const { return m_uiUsedElements; };
  
  //Devuelve total de elementos
  const uint32 GetTotalElements()   const { return m_uiTotalElements; };

  //Obtiene elemento por indice
  T* GetAt(uint32 _uiIndex) const;
  
  //Devuelve si la posicion del array esta libre 
  bool IsFree(uint32 _uiIndex) const;
  
  //Crea nuevo elemento en el array
  T* New();
  
  //Libera una posicion del array
  void Free(uint32 _uiIndex);
  
  //Borra todos los elementos
  void DeleteAllElements();

protected:
  void Release();

private:
  void Init();

  uint32  m_uiFreeElements;
  uint32  m_uiUsedElements;
  uint32  m_uiTotalElements;
  T*      m_vRecyclingArray;
  T       m_TDefault;
  bool*   m_vRecyclingArrayStatus;    //Array con el estado booleano del RecyclingArray
};


/**
 * Init
 */
template<class T> void CRecyclingArray<T>::Init(void)
{
  //comprueba si el numero de elementos es positivo para inicializar el array
  if(m_uiTotalElements > 0)
    SetOk(true);
  else
  {
    return;
    SetOk(false);
  }


  //Crea los arrays de contenido y de estado
  m_vRecyclingArray       = new T[m_uiTotalElements];
  m_vRecyclingArrayStatus = new bool[m_uiTotalElements];


  //cada elemento de estado a true
  for(uint32 i = 0; i < m_uiTotalElements; i++)
    m_vRecyclingArrayStatus[i] = true;
};


/**
 * Release
 */
template<class T> void CRecyclingArray<T>::Release(void)
{
  CHECKED_DELETE_ARRAY(m_vRecyclingArray);
  CHECKED_DELETE_ARRAY(m_vRecyclingArrayStatus);
};


/**
 * DeleteAllElements
 */
template<class T> void CRecyclingArray<T>::DeleteAllElements(void)
{
  assert(IsOk());

  //elementos vacios
  for(uint32 i = 0; i < m_uiTotalElements; i++)
    m_vRecyclingArrayStatus[i] = true;

  m_uiFreeElements = m_uiTotalElements;
  m_uiUsedElements = 0;
};


/**
 * Free
 */
template<class T> void CRecyclingArray<T>::Free(uint32 _uiIndex)
{
  assert(IsOk());

  //libera elemento
  //solo si su status es false, si ya esta libre no lo borra
  if(!m_vRecyclingArrayStatus[_uiIndex])
  {
    m_uiUsedElements--;
    m_uiFreeElements++;
    m_vRecyclingArrayStatus[_uiIndex] = true;
  }
};


/**
 * New
 */
template<class T> T* CRecyclingArray<T>::New(void)
{
  assert(IsOk());

  bool   l_bFound  = false;
  uint32 l_uiIndex = 0;
  
  //busca el primer elemento libre
  if(m_uiFreeElements > 0)
  {
    while(!l_bFound && l_uiIndex < m_uiTotalElements)
    {
      l_bFound = m_vRecyclingArrayStatus[l_uiIndex];
      l_uiIndex++;
    }
  }

  //añade el elemento al array y lo marca con estado 'no libre'
  if(l_bFound)
  {
    l_uiIndex--;
    m_uiFreeElements--;
    m_uiUsedElements++;
    m_vRecyclingArrayStatus[l_uiIndex] = false;
    m_vRecyclingArray[l_uiIndex] = m_TDefault;
    //devuelve la posicion de memoria del objeto
    return &(m_vRecyclingArray[l_uiIndex]);
  }else
    return 0;
};


/**
 * IsFree - devuelve si la posicion del array dada esta libre
 */
template<class T> bool CRecyclingArray<T>::IsFree(uint32 _uiIndex) const
{
  assert(IsOk());

  return m_vRecyclingArrayStatus[_uiIndex];
};


/**
 * GetAt - devuelve el objeto de la posicion dada del array
 */
template<class T> T* CRecyclingArray<T>::GetAt(uint32 _uiIndex) const
{
  assert(IsOk());

  return &(m_vRecyclingArray[_uiIndex]);
};

#endif