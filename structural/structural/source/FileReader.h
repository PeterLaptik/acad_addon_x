#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>

/**
* File reader for text files.
* Separate tokens divided by delimiter can be read inside each line.
*/


class FileReader
{
    public:
        FileReader();
        FileReader(const std::string &path);
        virtual ~FileReader();

        void SetFilePath(const std::string &path);
        void OpenFile(void);
        void CloseFile(void);
        bool ReadLine(void);
        bool IsEmpty(void);
        const char& StartsWith(void);
        const std::string& GetLine(void);
        void SetDelimiter(char d);
        std::string GetString(void);
        std::string GetStringTrimmed(void);
        int GetInteger(void);
        double GetDouble(void);
        long GetLong(void);
        bool GetBoolean(void);

    protected:

    private:
        inline char* GetCharArray(void);

        std::string m_file_path;
        std::fstream m_file;
        std::string m_line;
        std::string::size_type m_line_cursor;
};

#endif // FILEREADER_H
