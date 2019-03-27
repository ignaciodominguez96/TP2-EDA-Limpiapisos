#pragma once

#ifndef DIMENSION_H
#define DIMENSION_H



#define UNITY_TILE		35								//cantidad de pixeles por unidad de baldosa 
#define	UNITY_ROBOT		(UNITY_TILE/2.0)				//cantidad de pixeles por unidad de robot 
#define UNITY_VECTOR	(UNITY_TILE)					//cantidad de pixeles por vector
#define	UNITY_VECTOR_HEAD	(UNITY_TILE/5.0)			//cantidad de pixeles por la cabeza de vector

#define	UNITY_FONT_SPACE	20							//cantidad de pixeles por ' ' en la escritura
#define	UNITY_FONT_LETTER	 (UNITY_FONT_SPACE/2.0)		//cantidad de pixeles por letra o numero en la escritura modo 1

#define	VECTOR_THICKNESS (UNITY_TILE/20.0)				//grosor del vector del robot

#define OFFSET_HISTOGRAM 8								
#define FONT_SIZE_HISTOGRAM (OFFSET_HISTOGRAM)			//cantidad de pixeles por letra o numero en la escritura en el histograma (sobre los puntos)


#define FONT_SIZE_AXIS	(FONT_SIZE_HISTOGRAM*(1.1))		//cantidad de pixeles por letra o numero en la escritura en los ejes

#define OFFSET_AXIS (0.1)								
#define OFFSET_AXIS_INDICATOR 3							
#define SEPARATION_AXIS_Y 4								

#define THICKNESS_AXIS 3								//grosor del eje



#endif // DIMENSION_H
