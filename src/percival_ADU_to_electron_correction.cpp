/*
 * ADC_to_electron_correction.cpp
 *
 *  Created on: 4 Aug 2015
 *      Author: pqm78245
 */
#include "percival_ADU_to_electron_correction.h"

void percival_ADU_to_electron_correction(percival_frame<float> &CDS_Img, percival_frame<float> &output, const percival_calib_params & calib){
		//dimension checks
		float *ADU_per_el = calib.ADU_to_electrons_conversion.data;
		int width = calib.ADU_to_electrons_conversion.width;
		int height = calib.ADU_to_electrons_conversion.height;

		if((CDS_Img.width != width) || (CDS_Img.height != height))
			throw dataspace_exception{"In percival_ADU_to_electron_correction(): CDS_Img dimension and ADU_per_el dimension mismatch."};

		if((output.width != CDS_Img.width) || (output.height != CDS_Img.height))		//todo:change this to a inline function
			output.set_frame_size(CDS_Img.height, CDS_Img.width);

		//can also put this as operator overloading
		//exclude points in the list
		for(int i = 0; i < CDS_Img.width * CDS_Img.height; i ++){
				*( output.data + i ) = *( CDS_Img.data + i ) / *( ADU_per_el + i );			//todo:apply the delta mask!!!!!!!!
		}
}

