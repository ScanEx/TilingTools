#pragma once
#include "stdafx.h"

namespace gmx
{

#ifdef GDAL_OF_VECTOR
#define VECTORDS GDALDataset  
#else
#define VECTORDS OGRDataSource
#endif

class VectorOperations
{
public:
	//static GDALDataset* CreateVirtualVectorLayer(string strLayerName, 
	//	OGRSpatialReference* poSRS=0, OGRwkbGeometryType eType=wkbPolygon);
	
	static OGRMultiPolygon*   ConvertFromSRSToPixelLine(OGRGeometry *p_ogr_geom, double geotransform[6]);
	static VECTORDS*          OpenVectorFile(string strVectorFile, bool bReadOnly=true);
	static void               CloseVECTORDS(VECTORDS* poVecDS);
	static OGRGeometry*		    ReadAndTransformGeometry				(string vector_file, OGRSpatialReference  *p_tiling_srs);
	static string				      GetVectorFileNameByRasterFileName	(string raster_file);
	static OGRPolygon*			  CreateOGRPolygonByOGREnvelope		(const OGREnvelope &envelope);
	static OGREnvelope			  MergeEnvelopes					(const OGREnvelope	&envp1, const OGREnvelope	&envp2);
	static OGREnvelope			  InetersectEnvelopes				(const OGREnvelope	&envp1, const OGREnvelope	&envp2);
	static OGRLinearRing**		GetLinearRingsRef					(OGRGeometry	*p_ogr_geom, int &num_rings);
	static bool               IsPointInsidePixelLineGeometry (OGRPoint point, OGRGeometry *po_ogr_geom);

	static bool               AddIntermediatePoints(OGRPolygon *p_polygon, int points_on_segmet=10);
	static OGRMultiPolygon*		ReadMultiPolygonFromOGRDataSource(VECTORDS* poVecDS);

};


}