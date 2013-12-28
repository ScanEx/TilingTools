#pragma once

#include "stdafx.h"
#include "TileName.h"
#include "TileContainer.h"
#include "RasterFile.h"


class GMXTilingParameters
{
public:
//������������ ���������
	string						    input_path_;				//������� ���� ��� ������ ����� �����
	gmx::MercatorProjType	merc_type_;				//��� ���������
	gmx::TileType				  tile_type_;				//��� ������
	

//�������������� ���������
	int							base_zoom_;				//������������ (������� ���)
	int							min_zoom_;				//����������� ���
	string					vector_file_;				//��������� �������
	string					container_file_;			//�������� �����-���������� ������
	bool						use_container_;			//������ ����� � ���������
	BYTE						*p_background_color_;		//RGB-���� ��� ������� ���� � ������
	BYTE						*p_transparent_color_;		//RGB-���� ��� ����� ������������
	int							*p_nodata_value_;			//�������� ��� ����� ������������
	bool						auto_stretch_to_8bit_;		//������������� ������������� �������� � 8 ���		
  string          gdal_resampling_;				


	int							jpeg_quality_;
	double					shift_x_;				//����� �� x
	double					shift_y_;				//����� �� y
	gmx::TileName		*p_tile_name_;			//����� ������
	int							max_tiles_in_cache_;			//������������ ���������� ������ � ����������� ������

  int             max_work_threads_;
  int             max_warp_threads_;

  string          temp_file_path_for_warping_;
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

    max_work_threads_= 0;
    max_warp_threads_= 0;

    temp_file_path_for_warping_ = "";
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

struct GMXAsyncChunkTilingParams
{
	GMXTilingParameters				*p_tiling_params_;
	gmx::BundleOfRasterFiles	*p_bundle_; 
	OGREnvelope               chunk_envp_;
  int								        z_;
	int								        tiles_expected_; 
	int								        *p_tiles_generated_;
  BOOL                      *p_was_error_;
	gmx::ITileContainer				*p_tile_container_;
  BOOL                      stretch_to_8bit_;
  double		                *p_stretch_min_values_;
  double                    *p_stretch_max_values_;
  int                       srand_seed_;
  string                    temp_file_path_;
  //BOOL (*pfCleanAfterTiling)(gmx::RasterBuffer*p_buffer);
};

DWORD WINAPI GMXAsyncWarpChunkAndMakeTiling (LPVOID lpParam);

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