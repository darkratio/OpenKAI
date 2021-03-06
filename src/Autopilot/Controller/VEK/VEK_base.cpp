#include "VEK_base.h"

namespace kai
{

VEK_base::VEK_base()
{
	m_pVEK = NULL;
	m_pCMD = NULL;

	m_pwmU = 2000;
	m_pwmN = 1500;
	m_pwmL = 1000;
	m_vL = 0.0;
	m_vR = 0.0;
	m_vForward = 1.0;

	m_dT.init();
	m_dRot.init();
}

VEK_base::~VEK_base()
{
}

bool VEK_base::init(void* pKiss)
{
	IF_F(!this->ActionBase::init(pKiss));
	Kiss* pK = (Kiss*)pKiss;
	pK->m_pInst = this;

	KISSm(pK,pwmU);
	KISSm(pK,pwmN);
	KISSm(pK,pwmL);
	KISSm(pK,vForward);

	return true;
}

bool VEK_base::link(void)
{
	IF_F(!this->ActionBase::link());
	Kiss* pK = (Kiss*)m_pKiss;

	string iName;

	iName = "";
	F_ERROR_F(pK->v("_IOBase", &iName));
	m_pVEK = (_IOBase*) (pK->root()->getChildInstByName(&iName));

	return true;
}

void VEK_base::update(void)
{
	this->ActionBase::update();
	NULL_(m_pAM);

	cmd();

	int pwmL;
	int pwmR;
	double dPWML;
	double dPWMR;

	if(m_vL > 0.0)
		dPWML = m_pwmU - m_pwmN;
	else
		dPWML = m_pwmN - m_pwmL;

	if(m_vR > 0.0)
		dPWMR = m_pwmU - m_pwmN;
	else
		dPWMR = m_pwmN - m_pwmL;

	pwmL = m_pwmN + (int)(dPWML * m_vL);
	pwmR = m_pwmN + (int)(dPWMR * m_vR);

	NULL_(m_pVEK);

	static uint8_t pVekCMD[5];
	pVekCMD[0] = 0xff;
	pVekCMD[1] = pwmL >> 8;
	pVekCMD[2] = pwmL;
	pVekCMD[3] = pwmR >> 8;
	pVekCMD[4] = pwmR;

	m_pVEK->write(pVekCMD,5);
	LOG_I("PWM: L=" + i2str(pwmL) + " R=" + i2str(pwmR));

	string stateName = "VEK_RUN";
	m_pAM->transit(&stateName);
	m_vL = -m_vForward;
	m_vR = -m_vForward;

}

void VEK_base::cmd(void)
{
	NULL_(m_pCMD);

	if (!m_pCMD->isOpen())
	{
		m_pCMD->open();
		return;
	}
}

bool VEK_base::draw(void)
{
	IF_F(!this->ActionBase::draw());
	Window* pWin = (Window*) this->m_pWindow;
	Mat* pMat = pWin->getFrame()->m();
	NULL_F(pMat);
	IF_F(pMat->empty());

	string msg = *this->getName()
			+ ": vL=" + f2str(m_vL)
			+ ", vR=" + f2str(m_vR);
	pWin->addMsg(&msg);

	return true;
}

}
