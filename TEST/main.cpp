//==========================================================================================================
// @file	:	main
// @author	:	NAGISA
// @data	:	2023/1/26 14:10:55
// @brief	:	
//==========================================================================================================
#include "NGS/NGS.h"
#include "NMath/Math.h"
#define CUSTOM_NDA_TYPE_COLOR _TYP RGB15

#include "N_WIN/N_WIN.h"
#include "Snake_Plus/Font.h"
//#include "NGF/NGF.h"

#include <vector>
#include <iostream>
#include <stdarg.h>

#include "resource.h"
//#include "Snake_Plus/Font.h"

USE_NGS_TYPE
USE_NGS
USE_NGS_CONCEPT
USE_NGS_TYTR
/*
using rgb = RGB_Default<CUSTOM_NDA_TYPE_COLOR>;

BitmapData background(800, 600, rgb::blue);
BitmapData bd_bg(160, 128, rgb::black);

template<_TYP FLAG F>
struct Snake_Data {
    NGS_INL_CSTEXPR static auto flag = F;
    _TYP SIZE_T16 width = 0;
    _TYP SIZE_T16 height = 0;
    _TYP PBYTE data = nullptr;
};
_TYP BYTE mode_menu_snake[] = {
#include "data_menu_snake.h"
};
Snake_Data<Encoder::BYTE_INVERSE> menu_snake = {
    .width = 107,
    .height = 84,
    .data = mode_menu_snake
};

const auto GetTextFontData(_TYP CHAR8 c) {
    return ASCII_1608[c - ' '];
}
_TYP VOID Handler(Event& e) {
    auto& evt = *(MouseEvent*)&e;
    const auto& param = *evt.GetParam();
    
    param.pWindow->Render();
}

template<_TYP FLAG flag>
_TYP VOID InitSnakeData(Snake_Data<flag>& config) {
    Encoder::RGB_ModelTrans<RGB15, flag>(config.data, config.width, config.height);
}
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

struct WaveHeader {
    _TYP CHAR8 chunk_id[4];
    _TYP SIZE_T32 chunk_size;
    _TYP CHAR8 format[4];
    _TYP CHAR8 subchunk1_id[4];
    _TYP SIZE_T32 subchunk1_size;
    _TYP SIZE_T16 audioFormat;
    _TYP SIZE_T16 channels;
    _TYP SIZE_T32 sampleRate;
    _TYP SIZE_T32 byteRate;
    _TYP SIZE_T16 blockAlign;
    _TYP SIZE_T16 bitsPerSample;
    _TYP CHAR8 subchunk2_id[4];
    _TYP SIZE_T32 subchunk2_size;

    _TYP BOOL Check() const {
        auto comp = []<_TYP SIZE_T32 N>(const _TYP CHAR8(&a)[N - 1], const _TYP CHAR8(&b)[N]) {
            for (_TYP SIZE_T32 i = 0; i < N - 1; i++)
                if (a[i] != b[i])return FALSE;
            return TRUE;
        };
        _TYP BOOL b = TRUE;
        b &= comp(chunk_id, "RIFF");
        b &= comp(format, "WAVE");
        b &= comp(subchunk2_id, "data");
        return b;
    }
    _TYP VOID Print() const{
        std::cout << std::format(
            ""
            "\n=============================="
            "\n音频数据格式为：{:d}"
            "\n声道数:{:d}"
            "\n每秒采样:{:d}个样本，{:d}字节"
            "\n样本大小:{:d}字节,{:d}比特"
            "\n数据大小：{:d}字节"
            "\n==============================",
            audioFormat,
            channels,
            sampleRate,byteRate,
            blockAlign,bitsPerSample,
            subchunk2_size
        ) << std::endl;
    }
};
struct Wave{
    using WaveData = _TYP PVOID;
    WaveHeader header;
    WaveData data = nullptr;

    ~Wave() {
        if (data)Delete(data);
    }
    
    _TYP BOOL ReadFrom(ifstream& file) {
        file.read((char*)&header, sizeof(WaveHeader));
        if (!header.Check())return FALSE;
        data = New(new _TYP BYTE[header.subchunk2_size](), header.subchunk2_size);
        file.read((char*)data, header.subchunk2_size);
        return TRUE;
    }
    _TYP SIZE_T32 Length()const { return header.subchunk2_size / header.blockAlign; }

    template<_CPT Integral INT>
    INT& At(_TYP SIZE_T32 index) { return ((INT*)data)[index]; }
    template<_CPT Integral INT>
    const INT& At(_TYP SIZE_T32 index)const { return ((INT*)data)[index]; }
};

void LoadWavFile(const char* fname, Wave& wave) {
    ifstream file;
    file.open(fname, std::ios::in | std::ios::binary);
    if (!file.is_open()) return;
    wave.ReadFrom(file);
    file.close();
}

#define BASE_DIR(filename) "F:\\Projects\\C_CPP\\VisualStudio\\NGF\\Bin\\Win32\\Debug\\" #filename

int main() {

    Wave wave;
    LoadWavFile(
        BASE_DIR(game.wav),
        wave
    );
    wave.header.Print();
    wave.Length();
    ofstream waveData;
    waveData.open(BASE_DIR(waveData.h),std::ios::out | std::ios::binary | std::ios::trunc);
    waveData << "constexpr unsigned char waveData[] = { \n";
    for (size_t i = 0; i < wave.Length(); i++)
    {
        waveData << (unsigned int)wave.At<_TYP BYTE>(i) << ',';
    }
    waveData << "}";
    waveData.close();

    return 0;
}
/*
int main() {
    FILE* fp = nullptr;
    auto res = fopen_s(&fp, "F:\\Projects\\C_CPP\\VisualStudio\\NGF\\Bin\\Win32\\.\\game.wav", "rb");

    return 0 ;
    InitSnakeData(menu_snake);

    auto& window = App::I().CreateWindow(L"test", { 300,300,800,600 });

    auto& stage = window.GetStage();
    
    using fontConfig = FontMessage<ASCII_1608_Width, ASCII_1608_Height, Encoder::IS_VERTICAL, _TYP UINT16, 0>;
    
    Matrix<NDA_TYPE_NUM> matrix;
    matrix.Tilt(AsRadian(45), 0);
    background.DrawRect(rgb::white, 100, 100, 100, 100);
    background.Fill(rgb::white, { 500,40,100,100 }, matrix);
    auto& bitmap = *New(new Bitmap(background));
    auto& textfied = *New(new TextField<fontConfig>(L"start"));
    textfied.X() = 300;
    textfied.Y() = 300;
    
    stage.AddChild(bitmap);
    stage.AddChild(textfied);
    
    Allocator::I().Show();

    auto& test_pic = *New(new BitmapData(menu_snake.width, menu_snake.height, (BitmapData::__color_ptr)menu_snake.data));
    auto& b = *New(new Bitmap(test_pic));
    b.X() = 50;
    b.Y() = 50;
    b.Matrix()
        .Scale(1, 1);
    b.Resize();
    stage.AddChild(b);
    Tweens<NDA_TYPE_NUM> tween{ ease::Cubic::EaseOut, 30 };
    tween += {b.X()};
    tween += {b.Y()};
    tween.YoYo(TRUE);
    tween.From(30, 250);

    window.Listen(WM_Event::UPDATE, [&](Event& e) {
        auto& window = e.CurrentTarget<Window>();
        tween.Update();
        window.Render();
    });

    App::I().Update();


    return 0;
}*/