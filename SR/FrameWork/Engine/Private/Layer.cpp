#include "Layer.h"

CLayer::CLayer()
{
}

CLayer* CLayer::Create()
{
	CLayer* pInstance = new CLayer;

	return pInstance;
}

void CLayer::Free()
{
}

