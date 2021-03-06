// VisualBoyAdvance - Nintendo Gameboy/GameboyAdvance (TM) emulator.
// Copyright (C) 2009 VBA-M development team

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or(at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#ifndef __VBA_GAME_H__
#define __VBA_GAME_H__

#include <string>

namespace Cartridge
{

class GameInfos
{
protected:
	std::string m_sTitle;
	std::string m_sCode;

	bool m_bHasSRAM;
	bool m_bHasEEPROM;
	bool m_bHasFlash;
	bool m_bHasRTC;
	int m_iEEPROMSize;
	int m_iFlashSize;

	void reset();

public:
	GameInfos();

	const std::string& getTitle() const;
	bool hasSRAM() const;
	bool hasFlash() const;
	bool hasEEPROM() const;
	bool hasRTC() const;
	int getEEPROMSize() const;
	int getFlashSize() const;
};

}

#endif // __VBA_GAME_H__
