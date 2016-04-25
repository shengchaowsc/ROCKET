//============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GPSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GPSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//  
//  Copyright 2004, The University of Texas at Austin
//  Wei Yan - Chinese Academy of Sciences . 2009, 2010
//
//============================================================================


/**
 * @file CiraExponentialDrag.cpp
 * Computes the acceleration due to drag on a satellite
 * using an exponential Earth atmosphere model.
 */

#include "CiraExponentialDrag.hpp"
#include "IERSConventions.hpp"
#include "StringUtils.hpp"

using namespace std;
using namespace gpstk::StringUtils;

namespace gpstk
{
   
   void CiraExponentialDrag::test()
   {
      cout<<"testing CiraExponentialDrag"<<endl;

   
      Vector<double> r(3),v(3);
      r(0)=-4453783.586;
      r(1)=-5038203.756;
      r(2)=-426384.456;

      v(0) =  3831.888;
      v(1) = -2887.221;
      v(2) = -6.018232;

      EarthBody body;
      CommonTime t;
      Spacecraft sc;

      (void)computeDensity(t,body,r,v);
      doCompute(t,body,sc);

      (void)getAccel();
   }

      /* Compute the atmospheric density using an exponential atmosphere model.
       * @param utc Time in UTC.
       * @param rb  EarthBody.
       * @param r   ECI position vector in m.
       * @param v   ECI velocity vector in m/s.
       * @return    Atmospheric density in kg/m^3.
       */
   double CiraExponentialDrag::computeDensity(CommonTime utc, 
                                              EarthBody& rb,
                                              Vector<double> r, 
                                              Vector<double> v)
   {
      // Get the J2000 to TOD transformation
      Matrix<double> N = C2TMatrix(utc);

      // Transform r from J2000 to TOD
      Vector<double> r_tod = N*r;

      Position geoidPos(r_tod(0),r_tod(1),r_tod(3),Position::Cartesian);
      double height = geoidPos.getAltitude()/1000.0;              //  convert to [km]

      // check to see if too low
      if (height < h0[0])
      {
         string msg = "CiraExponentialDrag is valid for 50.0 km t0 1000.0 km"
            + string("the altitude you try is ")
            + asString(height) + " km!";

         Exception e(msg);

         GPSTK_THROW(e);
      }

      // find the right height bracket
      int n = CIRA_SIZE; //h0.length;
      int bracket = 0;
      if (height >= h0[n-1]) 
      {
         bracket = n - 1;
      }
      else 
      {
         for (int i = 0; i < (n-1); i++) 
         {
            if ((height >= h0[i]) && (height < h0[i+1]))
            {
               bracket = i;
            }
         }
      }

      // compute the density
      this->brack = bracket;
      double rho = rho_0[bracket] * std::exp((h0[bracket] - height)/H[bracket]);

      return rho;

   }  // End of method 'CiraExponentialDrag::computeDensity()'

}  // End of namespace 'gpstk'
