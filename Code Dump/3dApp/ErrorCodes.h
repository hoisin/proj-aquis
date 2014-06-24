/*
	Error Codes
*/

#ifndef __ERRORCODES_H__
#define __ERRORCODES_H__
	
#define ERROR_PASS									0x00000001
#define ERROR_FAIL									0x00000010

#define ERROR_GFX									0x00000101

// D3DBase errors
#define ERROR_GFX_CREATE_INDEPEND_RES				0x00000201
#define ERROR_GFX_CREATE_WIN_DEPEND_RES				0x00000212
#define ERROR_GFX_CREATE_DEVICE_DEPEND_RES			0x00000223

// Buffer errors
#define ERROR_GFX_SHADER_INIT						0x00000301

#define ERROR_GFX_VERT_BUFFER_CREATE				0x00000311		
#define ERROR_GFX_INSTANCE_BUFFER_CREATE			0x00000312		
#define ERROR_GFX_INDEX_BUFFER_CREATE				0x00000313	

#define ERROR_GFX_WIC_CREATE_TEXTURE				0x00000321

#define ERROR_GFX_MODEL_INIT						0x00000355

#define ERROR_GFX_MODEL_REMOVE						0x00000381

// Shader errors
#define ERROR_GFX_SHADER_VERT_COMPILE				0x00000401
#define ERROR_GFX_SHADER_PIX_COMPILE				0x00000402

#define ERROR_GFX_SHADER_VERT_CREATE				0x00000411
#define ERROR_GFX_SHADER_PIX_CREATE					0x00000412
#define ERROR_GFX_SHADER_LAYOUT_CREATE				0x00000413
#define ERROR_GFX_SHADER_CONST_BUFF_CREATE			0x00000414
#define ERROR_GFX_SHADER_SAMPLER_CREATE				0x00000415
#define ERROR_GFX_SHADER_PARAMSET					0x00000416


#define ERROR_GFX_SHADER_REMOVE						0x00000451


inline bool SUCCESS(int errorCode)
{
	if(errorCode == ERROR_PASS)
		return true;

	return false;
}

#endif