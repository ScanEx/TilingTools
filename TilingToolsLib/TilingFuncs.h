#pragma once

#include "stdafx.h"
#include "TileName.h"
#include "TileContainer.h"
#include "RasterFile.h"


class GMXTilingParameters
{
public:
//������������ ���������
	string						input_path_;				//������� ���� ��� ������ ����� �����
	gmx::MercatorProjType		merc_type_;				//��� ���������
	gmx::TileType				tile_type_;				//��� ������
	

//�������������� ���������
	int							base_zoom_;				//������������ (������� ���)
	int							min_zoom_;				//����������� ���
	string						vector_file_;				//��������� �������
	string						container_file_;			//�������� �����-���������� ������
	bool						use_container_;			//������ ����� � ���������
	BYTE						*p_background_color_;		//RGB-���� ��� ������� ���� � ������
	BYTE						*p_transparent_color_;		//RGB-���� ��� ����� ������������
	int							*p_nodata_value_;			//�������� ��� ����� ������������
	bool						auto_stretch_to_8bit_;		//������������� ������������� �������� � 8 ���		
  string          gdal_resampling_;				


	int							jpeg_quality_;
	double						shift_x_;				//����� �� x
	double						shift_y_;				//����� �� y
	gmx::TileName				*p_tile_name_;			//����� ������
	int							max_tiles_in_cache_;			//������������ ���������� ������ � ����������� ������

	//static const int			DEFAULT_JPEG_QUALITY = 85;


	GMXTilingParameters(string input_path, gmx::MercatorProjType merc_type, gmx::TileType tile_type)
	{
		input_path_ = input_path;
		merc_type_	= merc_type;
		tile_type_	= tile_type;
		
		use_container_ = TRUE;
		jpeg_quality_ = 0;
		shift_x_ = 0;
		shift_y_ = 0;
		p_tile_name_ = NULL;
		p_background_color_	= NULL;
		p_transparent_color_ = NULL;
		p_nodata_value_		= NULL;
		base_zoom_	= 0;
		min_zoom_	= 0;
		max_tiles_in_cache_	= 0;
		auto_stretch_to_8bit_ = FALSE;
	}

		
	~GMXTilingParameters ()
	{
		delete(p_background_color_);
		delete(p_transparent_color_);
		delete(p_nodata_value_);		
	}
};

BOOL GMXMakeTiling (	GMXTilingParameters		*p_tiling_params);


BOOL GMXMakeBaseZoomTiling (GMXTilingParameters				*p_tiling_params, 
							gmx::BundleOfRasterFiles		*p_bundle, 
							gmx::ITileContainer				*p_tile_container);



BOOL GMXMakePyramidFromBaseZoom (	gmx::VectorBorder	&vb, 
								int					base_zoom, 
								int					min_zoom, 
								GMXTilingParameters	*p_tiling_params, 
								int					&tiles_expected, 
								int					&tiles_generated, 
								BOOL				only_calculate, 
								gmx::ITileContainer	*p_itile_pyramid
								);


struct GMXTilingFromBufferParams
{
	GMXTilingParameters				*p_tiling_params_;
	gmx::RasterBuffer				*p_buffer_;
	gmx::BundleOfRasterFiles		*p_bundle_; 
	int								ul_x_; 
	int								ul_y_;
	int								z_;
	int								tiles_expected_; 
	int								*p_tiles_generated_;
  BOOL              *p_was_error_;
	gmx::ITileContainer				*p_tile_container_;
	BOOL (*pfCleanAfterTiling)(gmx::RasterBuffer*p_buffer);
};

BOOL GMXPrintTilingProgress (int tiles_expected, int tiles_generated);



BOOL GMXMakeTilingFromBuffer	(	GMXTilingParameters				*p_tiling_params,
								gmx::RasterBuffer				*p_buffer, 
								gmx::BundleOfRasterFiles		*p_bundle, 
								int								ul_x, 
								int								ul_y,
								int								z,
								int								tiles_expected, 
								int								*p_tiles_generated,
								gmx::ITileContainer				*p_tile_container
								);

/*
int GMXCalcTilesAtZoomForBundle (GMXTilingParameters			*p_tiling_params, 
									gmx::BundleOfRasterFiles	*p_bundle, 
									int							&num_all_tiles, 
									list<string>				&tile_list );
*/

DWORD WINAPIGMXCallTilingFromBuffer( LPVOID lpParam);

BOOL GMXCleanAfterTilingFromBufer (gmx::RasterBuffer				*p_buffer);


HANDLE GMXAsyncMakeTilingFromBuffer	(GMXTilingParameters			*p_tiling_params,
								gmx::RasterBuffer				*p_buffer, 
								gmx::BundleOfRasterFiles		*p_bundle, 
								int								ul_x, 
								int								ul_y,
								int								z,
								int								tiles_expected, 
								int								*p_tiles_generated,
								gmx::ITileContainer				*p_tile_container,
								unsigned long					&thread_id,
                BOOL              *p_was_error);
	

BOOL GMXMakePyramidTileRecursively (	gmx::VectorBorder				&vb,
								int								zoom,
								int								x,
								int								y,
								int								base_zoom,
								int								min_zoom,
								GMXTilingParameters				*p_tiling_params,
								gmx::RasterBuffer				&buffer, 
								int								&tiles_expected,
								int								&tiles_generated,
								BOOL							only_calculate,
								gmx::ITileContainer				*p_itile_pyramid,
                BOOL              *p_was_error);


BOOL GMXZoomOutTileBuffer		(	gmx::RasterBuffer			src_quarter_tile_buffers[4], 
								BOOL							src_quarter_tile_buffers_def[4], 
								gmx::RasterBuffer				&zoomed_out_tile_buffer); 


/*
int GMXCalcTilesAtZoomForImage (	string						image_file, 
									string						vector_file, 
									GMXTilingParameters			*p_tiling_params, 
									gmx::BundleOfRasterFiles	*p_bundle, 
									list<string>				&tile_list);
*/