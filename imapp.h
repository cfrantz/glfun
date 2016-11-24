#ifndef GLFUN_IMAPP_H
#define GLFUN_IMAPP_H
#include <memory>

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "util/fpsmgr.h"
#include "imwidget/debug_console.h"

class ImApp {
  public:
    static ImApp* Get() { return singleton_; }
    ImApp(const std::string& name, int width, int height);
    ImApp(const std::string& name) : ImApp(name, 1280, 720) {}
    ~ImApp();

    virtual void Init();
    virtual bool ProcessEvents();
    virtual void Draw();
    virtual void Run();

    // Convenience helpers for registering debug console commands
    inline void RegisterCommand(const char* cmd, const char* shorthelp,
                                std::function<void(DebugConsole*,
                                                   int argc, char **argv)> fn) {
        console_.RegisterCommand(cmd, shorthelp, fn);
    }

    template<typename T>
    inline void RegisterCommand(const char* cmd, const char* shorthelp,
                         T* that, void (T::*fn)(DebugConsole*,
                                                int argc, char **argv)) {
        console_.RegisterCommand(cmd, shorthelp, that, fn);
    }

    void PlayAudio(float* data, int len);
  private:
    void Quit(DebugConsole* console, int argc, char **argv);

    void InitAudio(int freq, int chan, int bufsz, SDL_AudioFormat fmt);
    void AudioCallback(float* stream, int len);

    static ImApp* singleton_;
    std::string name_;
    int width_;
    int height_;
    bool running_;
    DebugConsole console_;

    std::unique_ptr<float[]> audiobuf_;
    int audiobufsz_;
    int audio_producer_, audio_consumer_;

    SDL_Window *window_;
    SDL_Renderer *renderer_;
    SDL_Texture *texture_;
    SDL_PixelFormat *format_;
    SDL_GLContext glcontext_;
    FPSManager fpsmgr_;

    static void AudioCallback_(void* userdata, uint8_t* stream, int len);
};

#endif // GLFUN_IMAPP_H
