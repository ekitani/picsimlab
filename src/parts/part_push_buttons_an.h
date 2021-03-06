/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2020  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#ifndef PART_PUSH_BUTTONS_AN_H
#define	PART_PUSH_BUTTONS_AN_H

#include<lxrad.h>
#include"part.h"


class cpart_pbuttons_an:public part
{
   public:
      String GetName(void){return lxT("Push buttons (Analogic)");};
      cpart_pbuttons_an(unsigned x, unsigned y);
      ~cpart_pbuttons_an(void);
      void Draw(void);
      void Process(void);
      String GetPictureFileName(void){return lxT("push_buttons.png");};
      String GetInputMapFile(void){return lxT("push_buttons_i.map");};
      String GetOutputMapFile(void){return lxT("push_buttons_o.map");};
      String GetPropertiesWindowFile(void){return lxT("push_buttons_an.lxrad");};
      void Reset(void); 
      void EvMouseButtonPress(uint button, uint x, uint y,uint state);
      void EvMouseButtonRelease(uint button, uint x, uint y,uint state);
      void ConfigurePropertiesWindow(CPWindow *  wprop);
      void ReadPropertiesWindow(void);
      String WritePreferences(void);
      void ReadPreferences(String value);
      unsigned short get_in_id(char * name);
      unsigned short get_out_id(char * name);
    private:
      unsigned char active;  
      unsigned char output_pins[1];    
      float output_value;
};




#endif	/* PART_PUSH_BUTTONS_AN_H */

