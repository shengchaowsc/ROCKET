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
 * @file CiraExponentialDrag.hpp
 * Computes the acceleration due to drag on a satellite
 * using an exponential Earth atmosphere model.
 */

#ifndef   GPSTK_CIRA_EXPONENTIAL_DRAG_HPP
#define   GPSTK_CIRA_EXPONENTIAL_DRAG_HPP

#include "AtmosphericDrag.hpp"

namespace gpstk
{
      /** @addtogroup GeoDynamics */
      //@{

      /**
       * This class computes the acceleration due to drag on a satellite
       * using an exponential Earth atmosphere model. The min altitude is
       * currently 200 km. To go lower, just need to add more values from 
       * the table.
       *
       * This Model is checked on Sep 28th,2009, OK!!!
       *
       * Reference: Vallado, Table 8-4.
       */
   class CiraExponentialDrag : public AtmosphericDrag
   {
   public:
         /// Default construtor
      CiraExponentialDrag() {};

         /// Default destructor
      virtual ~CiraExponentialDrag() {};

      void test();

      
         /** Compute the atmospheric density using an exponential atmosphere model.
          * @param utc  Time in UTC.
          * @param rb   EarthBody.
          * @param r    ECI position vector in meters.
          * @param v    ECI velocity vector in m/s.
          * @return     Atmospheric density in kg/m^3.
          */
      virtual double computeDensity(CommonTime utc, 
                                    EarthBody& rb, 
                                    Vector<double> r, 
                                    Vector<double> v);

   protected:

      int brack;

   }; // End of class 'CiraExponentialDrag'

      // @}

}  // End of namespace 'gpstk'

#endif   // GPSTK_CIRA_EXPONENTIAL_DRAG_HPP
