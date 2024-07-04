#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "logger.hpp"

namespace Aether
{
    class FileException : public std::runtime_error
    {
    public:
        explicit FileException(const std::string &message) : std::runtime_error(message) {}
    };

    class File
    {
    public:
        enum OpenMode
        {
            READ,
            WRITE,
            APPEND
        };

        File(const std::string &path, Logger *logger = nullptr);
        ~File();

        void open(OpenMode mode);
        void close();
        long getSize();
        std::vector<char> readAll();
        void writeAll(const std::vector<char> &data);

        int read(void *buffer, int size);
        int write(const void *buffer, int size);

        bool isOpen() const;

        std::string getPath() const
        {
            return m_path;
        }

    private:
        std::string m_path;
        std::fstream m_fileStream;
        Logger *m_logger;

        void checkIfOpen() const;
        std::ios::openmode convertMode(OpenMode mode) const;
    };
}