//-----------------------------------------------------------------------------------
/*
	NFsSkelton for VS2010
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef NFsSkelton_H
#define NFsSkelton_H

//#include "../FsLibrary/Fs.h"
#include "../NFsLibrary/AE_SDK.h"

#include "Fs_Target.h"


#include "../FsLibrary/FsAE.h"

//���[�U�[�C���^�[�t�F�[�X��ID
//ParamsSetup�֐���Render�֐���params�p�����[�^��ID�ɂȂ�
enum {
	ID_INPUT = 0,	// default input layer

	ID_R,
	ID_G,
	ID_B,

	ID_NOISE,
	ID_NOISE_FRAME,
	ID_NOISE_OFFSET,


	ID_HIDDEN_ON,

	ID_TOPIC,
	ID_ADD_SLIDER,
	ID_FIXED_SLIDER,
	ID_FLOAT_SLIDER,
	ID_COLOR,
	ID_CHECKBOX,
	ID_ANGLE,
	ID_POPUP,
	ID_POINT,
	ID_TOPIC_END,

	ID_NUM_PARAMS
};

//UI�̕\��������
#define	STR_R				"R"
#define	STR_G				"G"
#define	STR_B				"B"
#define	STR_NOISE			"noise"
#define	STR_NOISE_FRAME1	"frame rander"
#define	STR_NOISE_FRAME2	"on"
#define	STR_NOISE_OFFSET	"noise offset"


#define	STR_HIDDEN_ON1		"Hidden UI"
#define	STR_HIDDEN_ON2		"oba-Q!"

#define	STR_TOPIC			"Sample Topics"
#define	STR_ADD_SLIDER		"Add_Slider"
#define	STR_FIXED_SLIDER	"Fixed_Slider"
#define	STR_FLOAT_SLIDER	"Float_Slider"
#define	STR_COLOR			"Color"
#define	STR_CHECKBOX1		"Checkbox"
#define	STR_CHECKBOX2		"on"
#define	STR_ANGLE			"Angle"
#define	STR_POPUP			"Popup"
#define	STR_POPUP_ITEMS		"One|Two|Tree"
#define	STR_POPUP_COUNT		3
#define	STR_POPUP_DFLT		1
#define	STR_POINT			"Point"


//UI�̃p�����[�^
typedef struct ParamInfo {
	PF_FpLong	r;
	PF_FpLong	g;
	PF_FpLong	b;
	
	PF_FpLong	noise;
	PF_Boolean	noise_frame;
	A_long		noise_offset;

	A_long			add;
	PF_Fixed		fxd;
	PF_FpLong		flt;
	PF_Pixel		col;
	PF_Boolean		cbx;
	PF_Fixed		agl;
	A_long			pop;
	PF_FixedPoint	pnt;
} ParamInfo, *ParamInfoP, **ParamInfoH;

//-------------------------------------------------------


//-----------------------------------------------------------------------------------
extern "C" {

DllExport 
PF_Err 
EntryPointFunc (	
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra);
}
#endif // NFsSkelton_H