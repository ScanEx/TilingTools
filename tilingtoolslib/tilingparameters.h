#pragma once

#include "stdafx.h"
#include "filesystemfuncs.h"
#include "stringfuncs.h"
#include "tilename.h"


namespace gmx
{

class BundleInputData
{
public:
  BundleInputData()
  {
    bands_num_=0;
  };

  bool  InitByConsoleParams ( list<string> listInputParam, 
                              list<string> listBorderParam, 
                              list<string> listBandParam);

  int   GetBandsNum   () {return bands_num_;};
 
  map<string,int*> GetBandMapping();
  map<string,string> GetFiles();
  list<string> GetRasterFiles();

  ~BundleInputData();

protected:
  void ClearAll();


protected:
  int bands_num_;
  map<string,pair<string,int*>> m_mapInputData;
};


typedef enum { 
  NDEF_CONTAINER_TYPE=-1,
	GMXTILES=0,
	MBTILES=1,
	TILEFOLDER=2
} TileContainerType;


class TilingParameters
{
public:
  TilingParameters()
  {
    jpeg_quality_ = 0;
    p_tile_name_ = NULL;
    p_background_color_	= NULL;
    p_transparent_color_ = NULL;
    nodata_tolerance_ = 0;
    base_zoom_	= 0;
    min_zoom_	= 0;
    auto_stretching_ = FALSE;

    p_bundle_input_ = 0;

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
	string output_path_;		//�������� �����-���������� ������
  TileContainerType container_type_;
  
  gmx::MercatorProjType	merc_type_;				//��� ���������
	gmx::TileType tile_type_;				//������ ������
	int	base_zoom_;				//������������ ��� (������� ���)
	int	min_zoom_;				//����������� ���
	string vector_file_;			//��������� �������
	unsigned char *p_background_color_;		//RGB-���� ��� ������� ���� � ������
  unsigned char *p_transparent_color_;		//RGB-���� ��� ����� ������������
	int nodata_tolerance_;     //������ ����� ��� ����� ������������
	bool auto_stretching_;		//������������� ������������� �������� � 8 ���		
  GDALResampleAlg gdal_resampling_;	      //�������� ������� ��� �����������			

  bool            calculate_histogram_;    //������������ �����������

	int							jpeg_quality_;  //������� ������ (jpeg, jpeg2000)
	gmx::TileName		*p_tile_name_;			//����� ������
  int             max_work_threads_;
  int             tile_chunk_size_;
  gmx::BundleInputData     *p_bundle_input_;
  map<string,string>    options_;

};


}