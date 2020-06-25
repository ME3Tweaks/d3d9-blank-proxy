#include <windows.h>

struct d3d9_dll { 
	HMODULE dll;
	FARPROC OrignalD3DPERF_BeginEvent;
	FARPROC OrignalD3DPERF_EndEvent;
	FARPROC OrignalD3DPERF_GetStatus;
	FARPROC OrignalD3DPERF_QueryRepeatFrame;
	FARPROC OrignalD3DPERF_SetMarker;
	FARPROC OrignalD3DPERF_SetOptions;
	FARPROC OrignalD3DPERF_SetRegion;
	FARPROC OrignalDebugSetLevel;
	FARPROC OrignalDebugSetMute;
	FARPROC OrignalDirect3D9EnableMaximizedWindowedModeShim;
	FARPROC OrignalDirect3DCreate9;
	FARPROC OrignalDirect3DCreate9Ex;
	FARPROC OrignalDirect3DShaderValidatorCreate9;
	FARPROC OrignalPSGPError;
	FARPROC OrignalPSGPSampleTexture;
} d3d9;

__declspec(naked) void FakeD3DPERF_BeginEvent() { _asm { jmp[d3d9.OrignalD3DPERF_BeginEvent] } }
__declspec(naked) void FakeD3DPERF_EndEvent() { _asm { jmp[d3d9.OrignalD3DPERF_EndEvent] } }
__declspec(naked) void FakeD3DPERF_GetStatus() { _asm { jmp[d3d9.OrignalD3DPERF_GetStatus] } }
__declspec(naked) void FakeD3DPERF_QueryRepeatFrame() { _asm { jmp[d3d9.OrignalD3DPERF_QueryRepeatFrame] } }
__declspec(naked) void FakeD3DPERF_SetMarker() { _asm { jmp[d3d9.OrignalD3DPERF_SetMarker] } }
__declspec(naked) void FakeD3DPERF_SetOptions() { _asm { jmp[d3d9.OrignalD3DPERF_SetOptions] } }
__declspec(naked) void FakeD3DPERF_SetRegion() { _asm { jmp[d3d9.OrignalD3DPERF_SetRegion] } }
__declspec(naked) void FakeDebugSetLevel() { _asm { jmp[d3d9.OrignalDebugSetLevel] } }
__declspec(naked) void FakeDebugSetMute() { _asm { jmp[d3d9.OrignalDebugSetMute] } }
__declspec(naked) void FakeDirect3D9EnableMaximizedWindowedModeShim() { _asm { jmp[d3d9.OrignalDirect3D9EnableMaximizedWindowedModeShim] } }
__declspec(naked) void FakeDirect3DCreate9() { _asm { jmp[d3d9.OrignalDirect3DCreate9] } }
__declspec(naked) void FakeDirect3DCreate9Ex() { _asm { jmp[d3d9.OrignalDirect3DCreate9Ex] } }
__declspec(naked) void FakeDirect3DShaderValidatorCreate9() { _asm { jmp[d3d9.OrignalDirect3DShaderValidatorCreate9] } }
__declspec(naked) void FakePSGPError() { _asm { jmp[d3d9.OrignalPSGPError] } }
__declspec(naked) void FakePSGPSampleTexture() { _asm { jmp[d3d9.OrignalPSGPSampleTexture] } }

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	char path[MAX_PATH];
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CopyMemory(path + GetSystemDirectory(path, MAX_PATH - 10), "\\d3d9.dll", 11);
		d3d9.dll = LoadLibrary(path);
		if (NULL == d3d9.dll)
		{
			MessageBox(0, "Cannot load original d3d9.dll library", "Proxy", MB_ICONERROR);
			ExitProcess(0);
		}
		d3d9.OrignalD3DPERF_BeginEvent = GetProcAddress(d3d9.dll, "D3DPERF_BeginEvent");
		d3d9.OrignalD3DPERF_EndEvent = GetProcAddress(d3d9.dll, "D3DPERF_EndEvent");
		d3d9.OrignalD3DPERF_GetStatus = GetProcAddress(d3d9.dll, "D3DPERF_GetStatus");
		d3d9.OrignalD3DPERF_QueryRepeatFrame = GetProcAddress(d3d9.dll, "D3DPERF_QueryRepeatFrame");
		d3d9.OrignalD3DPERF_SetMarker = GetProcAddress(d3d9.dll, "D3DPERF_SetMarker");
		d3d9.OrignalD3DPERF_SetOptions = GetProcAddress(d3d9.dll, "D3DPERF_SetOptions");
		d3d9.OrignalD3DPERF_SetRegion = GetProcAddress(d3d9.dll, "D3DPERF_SetRegion");
		d3d9.OrignalDebugSetLevel = GetProcAddress(d3d9.dll, "DebugSetLevel");
		d3d9.OrignalDebugSetMute = GetProcAddress(d3d9.dll, "DebugSetMute");
		d3d9.OrignalDirect3D9EnableMaximizedWindowedModeShim = GetProcAddress(d3d9.dll, "Direct3D9EnableMaximizedWindowedModeShim");
		d3d9.OrignalDirect3DCreate9 = GetProcAddress(d3d9.dll, "Direct3DCreate9");
		d3d9.OrignalDirect3DCreate9Ex = GetProcAddress(d3d9.dll, "Direct3DCreate9Ex");
		d3d9.OrignalDirect3DShaderValidatorCreate9 = GetProcAddress(d3d9.dll, "Direct3DShaderValidatorCreate9");
		d3d9.OrignalPSGPError = GetProcAddress(d3d9.dll, "PSGPError");
		d3d9.OrignalPSGPSampleTexture = GetProcAddress(d3d9.dll, "PSGPSampleTexture");

		break;
	}
	case DLL_PROCESS_DETACH:
	{
		FreeLibrary(d3d9.dll);
	}
	break;
	}
	return TRUE;
}
