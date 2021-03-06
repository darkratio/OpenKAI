
#ifndef OpenKAI_src_Autopilot_Controller_APcopter_depthVision_H_
#define OpenKAI_src_Autopilot_Controller_APcopter_depthVision_H_

#include "../../../Base/common.h"
#include "../../../Vision/_DepthVisionBase.h"
#include "../../ActionBase.h"
#include "APcopter_base.h"

#define N_DEPTH_ROI 16

namespace kai
{

struct DEPTH_ROI
{
	uint8_t			m_orientation;
	vDouble4		m_roi;
	double 			m_minD;
	double 			m_dScale;

	void init(void)
	{
		m_minD = 0.0;
		m_dScale = 1.0;
		m_orientation = 0;
		m_roi.init();
	}
};

class APcopter_depthVision: public ActionBase
{
public:
	APcopter_depthVision();
	~APcopter_depthVision();

	bool init(void* pKiss);
	bool link(void);
	void update(void);
	bool draw(void);

private:
	void updateMavlink(void);

	APcopter_base* m_pAP;
	_DepthVisionBase* m_pDV;

	int m_nROI;
	DEPTH_ROI m_pROI[N_DEPTH_ROI];

};

}

#endif

