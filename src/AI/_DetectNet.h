/*
 * _DetectNet.h
 *
 *  Created on: Aug 17, 2016
 *      Author: yankai
 */

#ifndef AI__DetectNet_H_
#define AI__DetectNet_H_

#include "../Base/common.h"

#ifdef USE_TENSORRT
#include "../Base/_ThreadBase.h"
#include "../Navigation/Object.h"
#include "../Stream/_StreamBase.h"

#include <cuda_runtime.h>
#include "cudaMappedMemory.h"
#include "cudaNormalize.h"
#include "detectNet.h"

namespace kai
{

class _DetectNet: public _ThreadBase
{
public:
	_DetectNet();
	~_DetectNet();

	bool init(void* pKiss);
	bool link(void);
	bool draw(void);

	bool start(void);

	int addObjClass(string* pName, uint8_t safety);
	OBJECT* addObject(OBJECT* pNewObj);

private:
	void detect(void);
	void update(void);
	static void* getUpdateThread(void* This)
	{
		((_DetectNet*) This)->update();
		return NULL;
	}

private:
	uint64_t m_frameID;
	int num_channels_;
	cv::Mat mean_;
	Frame* m_pRGBA;
	Frame* m_pRGBAf;
	double m_confidence_threshold;

	detectNet* m_pDN;
	int m_nBox;
	int m_nBoxMax;
	uint32_t m_nClass;

	float* m_bbCPU;
	float* m_bbCUDA;
	float* m_confCPU;
	float* m_confCUDA;

	string m_className;

public:
	_StreamBase* m_pStream;
	Object* m_pObj;

	string modelFile;
	string trainedFile;
	string meanFile;
	string labelFile;

};

}

#endif
#endif
