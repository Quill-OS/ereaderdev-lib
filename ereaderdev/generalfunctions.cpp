#include "generalfunctions.h"

// https://stackoverflow.com/questions/31655462/no-type-named-unique-ptr-in-namespace-std-when-compiling-under-llvm-clang
#include <memory>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

// This may not work in inkbox user apps?
QString execShell(const char *cmd) {
    std::array<char, 128> buffer;
    QString result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result.trimmed();
}
