# include "lib.hpp"

namespace fs = std::filesystem;

TintinReporter::TintinReporter(void) {
    if (!fs::exists(LOGDIR))
        if (!fs::create_directories(LOGDIR))
            throw CustomError("Error: create_directory failed");

    if (!fs::exists(LOGFILE)) {
        std::ofstream ofs(LOGFILE);
        if (!ofs)
            throw CustomError("Error: init ofstream failed");
        ofs.close();
    }
}

void    TintinReporter::save_logs(std::string logtype, std::string msg) {
    time_t          rawtime;
    struct tm       *timeinfo;
    char            buffer[80];
    std::fstream    logstream;

    logstream.open(LOGFILE, std::fstream::out | std::fstream::app);
    if (!logstream.is_open())
        throw CustomError("Error: open fstream failed");

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%d/%m/%Y - %H:%M:%S",timeinfo);

    logstream << "["<< buffer << "] [ " << logtype << " ] - Matt_daemon: " << msg << std::endl;
    if (logstream.is_open())
        logstream.close();
}