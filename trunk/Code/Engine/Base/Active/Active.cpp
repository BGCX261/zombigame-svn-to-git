#include "Active.h"

bool CActive::Init()
{
  m_bIsOk = true;

  if (!m_bIsOk)
  {
    Release();
  }

  return m_bIsOk;
}

void CActive::Done()
{
  if (IsOk())
  {
    Release();
    m_bIsOk = false;
  }
}

bool CActive::GetActive()
{
	return m_bIsActive;
}

void CActive::SetActive(bool state)
{
	m_bIsActive = state;
}

void CActive::Release()
{
	//free memory
}


