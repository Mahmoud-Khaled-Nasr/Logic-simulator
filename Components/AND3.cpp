#include "AND3.h"

#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

#include <string>
#include <fstream>
#include <streambuf>
#include <iomanip>

AND3::AND3(const GraphicsInfo & r_GfxInfo, std::string r_Label): Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 6)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void AND3::Operate()
{
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
		if (m_InputPins[i].GetStatus() == LOW)
		{
			m_OutputPin.SetStatus(LOW);
			return;
		}
	m_OutputPin.SetStatus(HIGH);
}

void AND3::Draw(Interface * pInterface) const
{
	pInterface->DrawComponent(GetGraphicsInfo(), "AND3", GetStatus());
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
		m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
    if (GetStatus() == SELECTED)
        pInterface->DrawLabel(GraphicsInfo(GetGraphicsInfo().GetX(), GetGraphicsInfo().GetY()+GetGraphicsInfo().GetHeight()*2/3, GetGraphicsInfo().GetWidth(), GetGraphicsInfo().GetHeight()/3), GetLabel());
}

void AND3::Copy(ApplicationManager* pManager) const
{
    pManager->PushIntoClipboard(new AND3(*this));
}

void AND3::Save(std::fstream& File) const
{
    File.clear();
    File.seekg(0);
    std::string dummy((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
    File.clear();
    File.seekp(0);
    File << std::setw(15) << std::left << "AND3" << std::setw(5) << std::left << GetGraphicsInfo().GetX() << std::setw(5) << std::left << GetGraphicsInfo().GetY() << std::setw(5) << std::left << GetGraphicsInfo().GetWidth() << std::setw(5) << std::left << GetGraphicsInfo().GetHeight() << GetLabel() << std::endl;
    File << dummy;
}
