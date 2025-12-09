#include "includes.hpp"

// Basic.cpp was added to the VS project
// Engine_functions.cpp was added to the VS project

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent = NULL;
Resize oResize = NULL;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;


void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL;
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkResize(IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	if (mainRenderTargetView)
	{
		pContext->OMSetRenderTargets(0, 0, 0);
		mainRenderTargetView->Release();
	}

	HRESULT hr = oResize(pThis, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	ID3D11Texture2D* pBuffer;
	pThis->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);

	pDevice->CreateRenderTargetView(pBuffer, NULL, &mainRenderTargetView);

	pBuffer->Release();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);

	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1, &vp);
	return hr;
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    bool bMenuVisible = true;

	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();

			init = true;
		}
		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame(); //First Window

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

	ImGui::Begin(("##scene"), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

	auto& io = ImGui::GetIO();
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
		
	if (cfg->init_hooks) {
		sdk->cheat_thread();
	}

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);

	if (GetAsyncKeyState(VK_INSERT) & 1)
		cfg->menu_open = !cfg->menu_open;

	ImGui::GetIO().MouseDrawCursor = cfg->menu_open;

	if (cfg->menu_open)
	{
		if (io.WantCaptureMouse)
			ImGui::StyleColorsDark();
		gui->cheat_gui();
	}

	ImGui::EndFrame(); //End First frame

	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID Module)
{
    /*console*/
	//AllocConsole();
	//FILE* Dummy;
	//freopen(("CONIN$"), "r", stdin);
	//freopen(("CONOUT$"), "w", stdout);
	//freopen(("CONOUT$"), "w", stderr);

	cfg = static_cast<settings*>(malloc(sizeof(settings)));
	if (!cfg) return 0;

	sdk = static_cast<cheat_manager*>(malloc(sizeof(cheat_manager)));
	if (!sdk) return 0;

	gui = static_cast<menu_imgui*>(malloc(sizeof(menu_imgui)));
	if (!gui) return 0;

	draw = static_cast<drawings*>(malloc(sizeof(drawings)));
	if (!draw) return 0;

	cfg->initialize_settings();

	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(13, (void**)&oResize, hkResize);
			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);

	return TRUE;

}

__declspec(dllexport) BOOL WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), nullptr, NULL, nullptr);
        break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
    return TRUE;
}
