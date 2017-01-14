/*
 * _AIbase.h
 *
 *  Created on: Aug 17, 2016
 *      Author: yankai
 */

#ifndef AI__AIBASE_H_
#define AI__AIBASE_H_

#include "../Base/common.h"

#include "../Base/_ThreadBase.h"
#include "../Stream/_StreamBase.h"

namespace kai
{

struct OBJECT
{
	vInt4 m_bbox;
	vInt2 m_camSize;
	double m_dist;
	double m_prob;
	int m_iClass;
	string m_name;
	uint8_t m_safety;
	vector<Point> m_contour;
	int64_t m_frameID;
};

class _AIbase: public _ThreadBase
{
public:
	_AIbase();
	~_AIbase();

	virtual bool init(void* pKiss);
	virtual bool link(void);
	virtual bool start(void);
	virtual bool draw(void);

	int size(void);
	bool add(OBJECT* pNewObj);
	OBJECT* get(int i, int64_t frameID);
	OBJECT* getByClass(int iClass);

	void update(void);
	static void* getUpdateThread(void* This)
	{
		((_AIbase*) This)->update();
		return NULL;
	}

public:
	_StreamBase* m_pStream;

	string m_fileModel;
	string m_fileTrained;
	string m_fileMean;
	string m_fileLabel;

	OBJECT* m_pObj;
	int m_nObj;
	int m_iObj;
	int64_t m_obsLifetime;

	double m_sizeName;
	double m_sizeDist;
	Scalar m_colName;
	Scalar m_colDist;
	Scalar m_colObs;

	double m_contourBlend;
	bool m_bDrawContour;



};

}

#endif