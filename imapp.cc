#include <gflags/gflags.h>
#include "imapp.h"
#include "imgui.h"
#include "examples/sdl_opengl_example/imgui_impl_sdl.h"
#include "util/os.h"


DEFINE_int32(audio_frequency, 48000, "Audio sample frequency");
//DEFINE_int32(audio_bufsize, 256, "Audio buffer size");
DEFINE_int32(audio_bufsize, 2048, "Audio buffer size");

ImApp* ImApp::singleton_;

ImApp::ImApp(const std::string& name, int width, int height)
  : name_(name),
    width_(width),
    height_(height),
    audio_producer_(0),
    audio_consumer_(0)
{
    singleton_ = this;
    SDL_Init(SDL_INIT_VIDEO |
             SDL_INIT_AUDIO |
             SDL_INIT_TIMER |
             SDL_INIT_JOYSTICK |
             SDL_INIT_GAMECONTROLLER);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    window_ = SDL_CreateWindow(name.c_str(),
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width_, height_,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    glcontext_ = SDL_GL_CreateContext(window_);
    ImGui_ImplSdl_Init(window_);
    fpsmgr_.SetRate(60);

    ///audiobufsz_ = FLAGS_audio_bufsize * 2;
    ///audiobuf_.reset(new float[audiobufsz_]);
    ///InitAudio(FLAGS_audio_frequency, 1, FLAGS_audio_bufsize, AUDIO_F32);
}

ImApp::~ImApp() {
    ImGui_ImplSdl_Shutdown();
    SDL_GL_DeleteContext(glcontext_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void ImApp::Init() {
    RegisterCommand("quit", "Quit the application.", this, &ImApp::Quit);
}

void ImApp::Quit(DebugConsole* console, int argc, char **argv) {
    running_ = false;
}

void ImApp::Run() {
    running_ = true;
    while(running_) {
        if (!ProcessEvents())
            break;
        Draw();
        // Play audio here if you have audio
        // PlayAudio(...)
        fpsmgr_.Delay();
    }
}

bool ImApp::ProcessEvents() {
    SDL_Event event;
    bool done = false;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSdl_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            done = true;
    }
    return !done;
}

void ImApp::Draw() {
    static bool open = true;
    ImVec4 clear_color = ImColor(114, 144, 154);
    ImGui_ImplSdl_NewFrame(window_);

    ImGui::SetNextWindowSize(ImVec2(500,300), ImGuiSetCond_FirstUseEver);
    if (ImGui::Begin(name_.c_str(), &open, ImGuiWindowFlags_MenuBar)) { 
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Windows")) {
                ImGui::MenuItem("Debug Console", nullptr,
                                console_.visible());
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::Text("Hello World");
    }

    console_.Draw();
    ImGui::End();

    glViewport(0, 0,
               (int)ImGui::GetIO().DisplaySize.x,
               (int)ImGui::GetIO().DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    SDL_GL_SwapWindow(window_);
}


void ImApp::InitAudio(int freq, int chan, int bufsz, SDL_AudioFormat fmt) {
    SDL_AudioSpec want, have;
    SDL_AudioDeviceID dev;

    SDL_memset(&want, 0, sizeof(want));
    want.freq = freq;
    want.channels = chan;
    want.samples = bufsz;
    want.format = fmt;
    want.callback = ImApp::AudioCallback_;
    want.userdata = (void*)this;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have,
                              SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    SDL_PauseAudioDevice(dev, 0);
}

void ImApp::PlayAudio(float* data, int len) {
    int producer = audio_producer_;
    while(len) {
        audiobuf_[producer] = *data++;
        len--;
        producer = (producer + 1) % audiobufsz_;
        while(producer == audio_consumer_) {
            // Audio overrun.
            os::Yield();
        }
        audio_producer_ = producer;
    }
}

void ImApp::AudioCallback(float* stream, int len) {
    while(audio_consumer_ != audio_producer_ && len) {
        *stream++ = audiobuf_[audio_consumer_];
        len--;
        audio_consumer_ = (audio_consumer_ + 1) % audiobufsz_;
    }
    if (len) {
        fprintf(stderr, "Audio underrun!\n");
        while(len--) {
            *stream++ = 0;
        }
    }
}

void ImApp::AudioCallback_(void* userdata, uint8_t* stream, int len) {
    ImApp* instance = (ImApp*)userdata;
    instance->AudioCallback((float*)stream, len/sizeof(float));
}
