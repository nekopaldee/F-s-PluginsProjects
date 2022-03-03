//-----------------------------------------------------------------------------------
/*
	UsedColorList for VS2010
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef UsedColorListMain_H
#define UsedColorListMain_H

#include "../NFsLibrary/AE_SDK.h"
#include "../NFsLibrary/AEInfo.h"
#include "../NFsLibrary/NFsWorld.h"


#include "NFs_Target.h"



//UI�̃p�����[�^
typedef struct ParamInfo {
	PF_Pixel	Colors[64];
	A_long		ColorsMax[64];
	A_long		ColorCount;
	PF_Boolean	IsGridDisp;
	PF_Pixel	ExceptColor0;
	PF_Pixel	ExceptColor1;
	PF_Pixel	ExceptColor2;
	A_long		GridWidth;
	A_long		GridHeight;
	A_Rect		Area;
	A_long		GridXCount;
	A_long		GridYCount;

} ParamInfo, * ParamInfoP, ** ParamInfoH;

#include "UsedColorListFX.h"

//���[�U�[�C���^�[�t�F�[�X��ID
//ParamsSetup�֐���Render�֐���params�p�����[�^��ID�ɂȂ�
enum {
	ID_INPUT = 0,	// default input layer
	ID_POS0,
	ID_POS1,
	ID_ExceptColor0,
	ID_ExceptColor1,
	ID_ExceptColor2,
	ID_ISDISP,
	ID_GRID_WIDTH,
	ID_GRID_HEIGHT,
	ID_NUM_PARAMS
};

//UI�̕\��������
#define	STR_POS0			"PosStart"
#define	STR_POS1			"PosEnd"
#define	STR_ISDISP			"Disp"
#define	STR_ON				"on"
#define	STR_GRID_WIDTH		"GridWidrh"
#define	STR_GRID_HEIGHT		"GridHeight"

#define	STR_ExceptColor0	"ExceptColor0"
#define	STR_ExceptColor1	"ExceptColor1"
#define	STR_ExceptColor2	"ExceptColor2"




//-------------------------------------------------------
class UsedColorList : public AEInfo
{
public:
	// ******************************************************
	PF_Err GetParams(ParamInfo *infoP);
	PF_Err Exec(ParamInfo* infoP);
	PF_Err ParamsSetup(
		PF_InData* in_dataP,
		PF_OutData* out_dataP,
		PF_ParamDef* paramsP[],
		PF_LayerDef* outputP) override;
	// ******************************************************
	PF_Err	About(
		PF_InData* in_dataP,
		PF_OutData* out_dataP,
		PF_ParamDef* paramsP[],
		PF_LayerDef* outputP) override
	{
		PF_Err err = PF_Err_NONE;
		Init();
		m_cmd = PF_Cmd_ABOUT;
		in_data = in_dataP;
		out_data = out_dataP;

		GetFrame(in_dataP);
		GetSuites(in_dataP);

		A_char MJV[64] = { '\0' };
		A_char MNV[64] = { '\0' };
		PF_SPRINTF(MJV, "%d", MAJOR_VERSION);
		PF_SPRINTF(MNV, "%d", MINOR_VERSION);

		ERR(AboutBox(
			NFS_DISPNAME,
			MJV,
			MNV,
			NFS_DESCRIPTION));

		return err;

	};
	// ******************************************************
	PF_Err	GlobalSetup(
		PF_InData* in_dataP,
		PF_OutData* out_dataP,
		PF_ParamDef* paramsP[],
		PF_LayerDef* outputP) override
	{
		PF_Err	err = PF_Err_NONE;
		Init();
		m_cmd = PF_Cmd_GLOBAL_SETUP;
		in_data = in_dataP;
		out_data = out_dataP;

		suitesP = new AEGP_SuiteHandler(in_dataP->pica_basicP);

		//Fs_Target.h�Œ�`
		out_dataP->my_version = NFS_VERSION;
		out_dataP->out_flags = NFS_OUT_FLAGS;
		out_dataP->out_flags2 = NFS_OUT_FLAGS2;
		/*
		�v���O�C��ID���l�����āA�O���[�o���ɃA�N�Z�X�ł���悤�ɕۑ�
		*/
		ae_plugin_idH = suitesP->HandleSuite1()->host_new_handle(sizeof(ae_global_data));

		if (ae_plugin_idH) {
			ae_plugin_idP = reinterpret_cast<ae_global_dataP>(suitesP->HandleSuite1()->host_lock_handle(ae_plugin_idH));
			if (ae_plugin_idP) {
				ae_plugin_idP->initializedB = TRUE;

				if (in_data->appl_id != 'PrMr') {
					ERR(suitesP->UtilitySuite3()->AEGP_RegisterWithAEGP(NULL, NFS_NAME, &ae_plugin_idP->my_id));
				}
				if (!err) {
					out_data->global_data = ae_plugin_idH;
				}
			}
			suitesP->HandleSuite1()->host_unlock_handle(ae_plugin_idH);
		}
		else {
			err = PF_Err_INTERNAL_STRUCT_DAMAGED;
		}

		return err;
	}
	// ******************************************************
	PF_Err GlobalSetdown(PF_InData* in_dataP) override
	{
		PF_Err	err = PF_Err_NONE;
		Init();
		m_cmd = PF_Cmd_GLOBAL_SETDOWN;
		suitesP = new AEGP_SuiteHandler(in_dataP->pica_basicP);
		in_data = in_dataP;

		//ae_plugin_idH
		if (in_dataP->global_data) {
			suitesP->HandleSuite1()->host_dispose_handle(in_dataP->global_data);
		}

		return err;
	}
	// ******************************************************
	

};
#ifndef EFFEC_TMAIN_H
#define EFFEC_TMAIN_H
//-----------------------------------------------------------------------------------
extern "C" {

	DllExport
		PF_Err
		EffectMain(
			PF_Cmd			cmd,
			PF_InData* in_dataP,
			PF_OutData* out_dataP,
			PF_ParamDef* paramsP[],
			PF_LayerDef* outputP,
			void* extraP)
	
	{
		PF_Err err = PF_Err_NONE;
		PF_Err err2 = PF_Err_NONE;

		try
		{
			
			UsedColorList ae;
			ae.in_data = in_dataP;

			switch (cmd) {
			case PF_Cmd_ABOUT:
				err = ae.About(in_dataP, out_dataP, paramsP, outputP);
				break;
			case PF_Cmd_GLOBAL_SETUP:
				err = ae.GlobalSetup(in_dataP, out_dataP, paramsP, outputP);
				break;
			case PF_Cmd_GLOBAL_SETDOWN:
				err = ae.GlobalSetdown(in_dataP);
				break;
			case PF_Cmd_PARAMS_SETUP:
				err = ae.ParamsSetup(in_dataP, out_dataP, paramsP, outputP);
				break;
			case PF_Cmd_SEQUENCE_SETUP:
				err = ae.SequenceSetup(in_dataP, out_dataP, paramsP, outputP);
				break;
			case PF_Cmd_SEQUENCE_SETDOWN:
				err = ae.SequenceSetdown(in_dataP, out_dataP, paramsP, outputP);
				break;
			case PF_Cmd_SEQUENCE_RESETUP:
				err = ae.SequenceResetup(in_dataP, out_dataP, paramsP, outputP);
				break;
			case PF_Cmd_RENDER:
				err = ae.Render(in_dataP, out_dataP, paramsP, outputP,ID_NUM_PARAMS);
				if (!err)
				{
					ParamInfo info;
					ERR(ae.GetParams(&info));
					ERR(ae.Exec(&info));
				}
				break;
			case PF_Cmd_SMART_PRE_RENDER:
				err = ae.PreRender(in_dataP, out_dataP, reinterpret_cast<PF_PreRenderExtra*>(extraP),ID_NUM_PARAMS,sizeof(ParamInfo));
				if (!err)
				{
					ParamInfo* infoP = reinterpret_cast<ParamInfo*>(ae.LockPreRenderData());
					ERR(ae.SetHostPreRenderData());
					ERR(ae.GetParams(infoP));
					ERR(ae.UnSetPreRenderData());
					ERR(ae.UnlockPreRenderData());

				}
				break;
			case PF_Cmd_SMART_RENDER:
				err = ae.SmartRender(in_dataP, out_dataP, reinterpret_cast<PF_SmartRenderExtra*>(extraP),ID_NUM_PARAMS);
				if (!err) {
					ParamInfo* infoP = reinterpret_cast<ParamInfo*>(ae.LockPreRenderData());
					if (infoP) {
						ERR(ae.Exec(infoP));
						ERR2(ae.UnsetSmartRender());
						ae.UnlockPreRenderData();
					}
					else {
						err = PF_Err_OUT_OF_MEMORY;
					}
				}
				break;
			case PF_Cmd_COMPLETELY_GENERAL:
				err = ae.RespondtoAEGP(in_dataP, out_dataP, paramsP, outputP, extraP);
				break;
			case PF_Cmd_DO_DIALOG:
				//err = PopDialog(in_data,out_data,params,output);
				break;
			case PF_Cmd_USER_CHANGED_PARAM:
				err = ae.HandleChangedParam(in_dataP,
					out_dataP,
					paramsP,
					outputP,
					reinterpret_cast<PF_UserChangedParamExtra*>(extraP));
				break;
			case PF_Cmd_QUERY_DYNAMIC_FLAGS:
				err = ae.QueryDynamicFlags(in_dataP,
					out_dataP,
					paramsP,
					reinterpret_cast<PF_UserChangedParamExtra*>(extraP));
				break;
			}
		}
		catch (PF_Err& thrown_err) {
			err = thrown_err;
		}
		return err;
	}
#endif
}
#endif // UsedColorList_H