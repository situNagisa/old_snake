//==========================================================================================================
// @file	:	NGF
// @author	:	NAGISA
// @data	:	2022/12/29 21:45:56
// @brief	:	
//==========================================================================================================


#include "NGF/NGF.h"
#include "NGF/NGF_Driver.h"

using namespace nagisa;

int main() {
	std::wcout.imbue(std::locale("", LC_CTYPE));

	NGF_Application* app = NGF_Application::Instance();
	return app->Run();
}