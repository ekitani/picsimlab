/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2019  Luis Claudio Gambôa Lopes

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


#define dprint if (1) {} else printf

#include"ldd_max72xx.h"

void
ldd_max72xx_rst(ldd_max72xx_t *ldd)
{
 int i;
 for (i = 0; i < 8; i++)
  ldd->ram[i] = 0;
 ldd->bc = 0;
 ldd->aclk = 1;
 ldd->update = 1;
 ldd->dat = 0;
}

void
ldd_max72xx_init(ldd_max72xx_t *ldd)
{
 ldd->bc = 0;
 ldd->aclk = 1;
 ldd->update = 1;
 ldd->dat = 0;
}

void
ldd_max72xx_update(ldd_max72xx_t *ldd)
{
 ldd->update = 1;
}

unsigned char
ldd_max72xx_io(ldd_max72xx_t *ldd, unsigned char din, unsigned char clk, unsigned char ncs)
{

 if ((ldd->ancs == 0)&&(ncs == 1))//cs rising edge
  {

   dprint ("data[%i]:%#02X  \n", (0x0F00 & ldd->dat) >> 8, 0x00FF & ldd->dat);


   switch ((0x0F00 & ldd->dat) >> 8)
    {
    case 0://NOP
     break;
    case 1://DIG0
    case 2://DIG1
    case 3://DIG2
    case 4://DIG3
    case 5://DIG4
    case 6://DIG5
    case 7://DIG6
    case 8://DIG7
     ldd->ram[((0x0F00 & ldd->dat) >> 8) - 1] = 0x00FF & ldd->dat;
     break;
    case 9://decode
     //TODO
     break;
    case 10://itensity
     break;
    case 11://scan limit
     //TODO
     break;
    case 12://shutdown
     //TODO
     break;
    case 13://not defined
     break;
    case 14://not defined
     break;
    case 15://display test
     //TODO
     break;
    }

   ldd->update = 1;

   ldd->bc = 0;
   ldd->ancs = ncs;
   return 1;
  }
 ldd->ancs = ncs;

 //transicao
 if ((ldd->aclk == 0)&&(clk == 1))//rising edge
  {

   if (ldd->bc == 0)
    {
     ldd->dat = 0;
    }
   ldd->dat |= din << (15 - ldd->bc);
   ldd->bc++;

   if (ldd->bc >= 16)//16 bits received
    {
     ldd->bc = 0;
    }

  }

 ldd->aclk = clk;
 return 1;
}

void
ldd_max72xx_draw(ldd_max72xx_t *ldd, CCanvas * canvas, int x1, int y1, int w1, int h1, int picpwr)
{
 int x, y;

 ldd->update = 0;

 for (x = 0; x < 8; x++)
  {
   for (y = 0; y < 8; y++)
    {
     if (ldd->ram[x] & (1 << y))
      {
       canvas->SetFgColor (250, 0, 0);
       canvas->SetColor (250, 0, 0);
      }
     else
      {
       canvas->SetFgColor (100, 100, 100);
       canvas->SetColor (100, 100, 100);
      }
     canvas->Circle (1, x1 + (y * 25)+12, y1 + (x * 25)+12, 10);
    }
  }
}








