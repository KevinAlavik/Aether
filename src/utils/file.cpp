#include <utils/file.hpp>

using namespace Aether;

File::File(const std::string &path, Logger *logger) : m_path(path), m_logger(logger)
{
}

File::~File()
{
    if (m_fileStream.is_open())
    {
        m_fileStream.close();
    }
}

void File::open(OpenMode mode)
{
    if (m_fileStream.is_open())
    {
        if (m_logger)
        {
            m_logger->log(LogLevel::ERROR, "File is already open");
            return;
        }
    }

    std::ios::openmode openMode = convertMode(mode);
    m_fileStream.open(m_path, openMode);

    if (!m_fileStream.is_open())
    {
        if (m_logger)
        {
            m_logger->log(LogLevel::ERROR, "Failed to open file: " + m_path);
        }
        throw FileException("Failed to open file: " + m_path);
    }
}

void File::close()
{
    if (!m_fileStream.is_open())
    {
        if (m_logger)
        {
            m_logger->log(LogLevel::ERROR, "File is not open");
        }
        throw FileException("File is not open");
    }
    m_fileStream.close();
}

long File::getSize()
{
    checkIfOpen();

    std::streampos currentPos = m_fileStream.tellg();
    m_fileStream.seekg(0, std::ios::end);
    std::streampos size = m_fileStream.tellg();
    m_fileStream.seekg(currentPos, std::ios::beg);

    return static_cast<long>(size);
}

std::vector<char> File::readAll()
{
    checkIfOpen();

    long size = getSize();
    std::vector<char> buffer(size);

    m_fileStream.seekg(0, std::ios::beg);
    if (!m_fileStream.read(buffer.data(), size))
    {
        if (m_logger)
        {
            m_logger->log(LogLevel::ERROR, "Failed to read file: " + m_path);
        }
        throw FileException("Failed to read file: " + m_path);
        return std::vector<char>();
    }

    return buffer;
}

void File::writeAll(const std::vector<char> &data)
{
    checkIfOpen();

    m_fileStream.write(data.data(), data.size());
    if (!m_fileStream)
    {
        if (m_logger)
        {
            m_logger->log(LogLevel::ERROR, "Failed to write file: " + m_path);
        }
    }
}

int File::read(void *buffer, int size)
{
    checkIfOpen();

    if (!m_fileStream.read(static_cast<char *>(buffer), size))
    {
        if (m_logger)
        {
            m_logger->log(LogLevel::ERROR, "Failed to read file: " + m_path);
        }
        return -1;
    }

    return static_cast<int>(m_fileStream.gcount());
}

int File::write(const void *buffer, int size)
{
    checkIfOpen();

    if (!m_fileStream.write(static_cast<const char *>(buffer), size))
    {
        if (m_logger)
        {
            m_logger->log(LogLevel::ERROR, "Failed to write file: " + m_path);
        }
        return -1;
    }
    return size;
}

bool File::isOpen() const
{
    if (!m_fileStream)
    {
        if (m_logger)
        {
            m_logger->log(LogLevel::FATAL, "File stream is null?");
        }
        return false;
    }
    return m_fileStream.is_open();
}

void File::checkIfOpen() const
{
    if (!m_fileStream.is_open())
    {
        if (m_logger)
        {
            m_logger->log(LogLevel::ERROR, "File is not open.");
        }
        throw FileException("File is not open.");
    }
}

std::ios::openmode File::convertMode(OpenMode mode) const
{
    switch (mode)
    {
    case READ:
        return std::ios::in | std::ios::binary;
    case WRITE:
        return std::ios::out | std::ios::binary | std::ios::binary;
    case APPEND:
        return std::ios::out | std::ios::binary | std::ios::app;
    default:
        if (m_logger)
        {
            m_logger->log(LogLevel::ERROR, "Invalid open mode.");
        }
        throw FileException("Invalid open mode.");
    }
}