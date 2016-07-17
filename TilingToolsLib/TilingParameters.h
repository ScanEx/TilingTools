#pragma once

#include "stdafx.h"
#include "FileSystemFuncs.h"
#include "StringFuncs.h"
#include "TileName.h"


namespace gmx
{

class BandMapping
{
public:
  BandMapping()
  {
    bands_num_=0;
  };
  bool  InitByConsoleParams (string file_param, string bands_param);
  bool  InitLandsat8  (string file_param, string bands_param);
  bool  GetBands      (string file_name, int &bands_num, int *&p_bands); 
  int   GetBandsNum   () {return bands_num_;};
  //ToDo
  list<string>  GetFileList();
  bool  GetBandMappingData (int &output_bands_num, int **&pp_band_mapping);
  ~BandMapping();
  static bool    ParseFileParameter (string str_file_param, list<string> &file_list, int &output_bands_num, int **&pp_band_mapping);

protected:
  bool  AddFile       (string file_name, int *p_bands); 


protected:
  int bands_num_;
  map<string,int*> data_map_;

};

class TilingParameters
{
public:
  TilingParameters(list<string> file_list, gmx::MercatorProjType merc_type, gmx::TileType tile_type)
  {
    file_list_ = file_list;
    merc_type_	= merc_type;
    tile_type_	= tile_type;
		
    use_container_ = TRUE;
    jpeg_quality_ = 0;
    p_tile_name_ = NULL;
    p_background_color_	= NULL;
    p_transparent_color_ = NULL;
    nodata_tolerance_ = 0;
    base_zoom_	= 0;
    min_zoom_	= 0;
    max_cache_size_	= 0;
    max_gmx_volume_size_ =0;
    auto_stretching_ = FALSE;

    p_band_mapping_ = 0;

    max_work_threads_= 0;
    tile_chunk_size_= 0;
    
    calculate_histogram_=false;
  };		
  ~TilingParameters ()
  {
    if (p_background_color_)  delete(p_background_color_);
	  if (p_transparent_color_) delete(p_transparent_color_);
    if (p_tile_name_)         delete(p_tile_name_);
  };


public:
//������������ ���������
	list<string>          file_list_;
	gmx::MercatorProjType	merc_type_;				//��� ���������
	gmx::TileType				  tile_type_;				//������ ������
	

//�������������� ���������
	int							base_zoom_;				//������������ ��� (������� ���)
	int							min_zoom_;				//����������� ���
	string					vector_file_;			//��������� �������
	string					container_file_;		//�������� �����-���������� ������
	bool						use_container_;			//������ ����� � ���������
	BYTE						*p_background_color_;		//RGB-���� ��� ������� ���� � ������
	BYTE						*p_transparent_color_;		//RGB-���� ��� ����� ������������
	int             nodata_tolerance_;     //������ ����� ��� ����� ������������
	bool						auto_stretching_;		//������������� ������������� �������� � 8 ���		
  GDALResampleAlg gdal_resampling_;	      //�������� ������� ��� �����������			

  bool            calculate_histogram_;    //������������ �����������

	int							jpeg_quality_;  //������� ������ (jpeg, jpeg2000)
	gmx::TileName		*p_tile_name_;			//����� ������
	unsigned int		max_cache_size_;		//������������ ������ ��������� ���� � ����������� ������
  int             max_work_threads_;
  int             tile_chunk_size_;
  unsigned int    max_gmx_volume_size_; //������������ ������ ����� � gmx-��������� 
  gmx::BandMapping     *p_band_mapping_;

};


}