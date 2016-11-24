#include <string>
#include <gflags/gflags.h>

#include "util/file.h"
#include "util/logging.h"
#include "util/strutil.h"
#include "imapp.h"

int main(int argc, char *argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    ImApp app("GL Fun");
    app.Init();
    app.Run();
    return 0;
}
