#include "FileReader.h"
#include <iostream>
#include <cstdlib>
#include <locale>
#include <string>

static const int STRING_BUFFER = 255;
static const char SPACE = ' ';
static char m_delimiter = '\t'; // TAB as default value


FileReader::FileReader()
{ }

FileReader::FileReader(const std::string &path)
{
    m_file_path = path;
}

FileReader::~FileReader()
{
    if(m_file.is_open())
        m_file.close();
}

void FileReader::SetFilePath(const std::string &path)
{
    m_file_path = path;
}

void FileReader::OpenFile()
{
    if(m_file_path.empty())
        return;

    if(m_file.is_open())
        m_file.close();

    m_file.open(m_file_path);
}

void FileReader::CloseFile()
{
    if(m_file.is_open())
        m_file.close();
}

/**
* Reads line. Prepares tokenizer (cursor).
* Returns false at the end of file.
*/
bool FileReader::ReadLine()
{
    m_line_cursor = 0;

    if(std::getline(m_file, m_line))
        return true;
    else
        return false;
}

/**
* Check is the line empty.
*/
bool FileReader::IsEmpty()
{
    return m_line.empty();
}

/**
* Get first symbol of the line excluding white-spaces.
*/
const char& FileReader::StartsWith()
{
    if(m_line.empty())
        return SPACE;

    for(std::string::size_type i=0; i<m_line.length(); i++)
    {
        if(!isspace(m_line.at(i)))
            return m_line.at(i);
    }
    return m_line.at(0);
}

/**
* Get the full line that has been read before.
*/
const std::string& FileReader::GetLine()
{
    return m_line;
}

void FileReader::SetDelimiter(char d)
{
    m_delimiter = d;
}

/**
* Returns string-value before defined delimiter.
*/
std::string FileReader::GetString()
{
    static char out_c_string[STRING_BUFFER];

    for(int i=0; i<STRING_BUFFER; i++)
        out_c_string[i] = '\0';

    if((m_line.empty())||(m_line_cursor>=m_line.length()))
        return std::string();

    int cursor = 0;
    while((m_line_cursor<m_line.length()) && (m_line.at(m_line_cursor)!=m_delimiter))
    {
        out_c_string[cursor] = m_line.at(m_line_cursor);
        cursor++;
        m_line_cursor++;
    }
    m_line_cursor++;

    return std::string(out_c_string);
}

/**
* Returns string-value before defined delimiter.
* The string is trimmed from the both sides.
*/
std::string FileReader::GetStringTrimmed()
{
    static char out_c_string[STRING_BUFFER];

    for(int i=0; i<STRING_BUFFER; i++)
        out_c_string[i] = '\0';

    if((m_line.empty())||(m_line_cursor>=m_line.length()))
        return std::string();

    int cursor = 0;
    // Left trim
    while((m_line_cursor<m_line.length()) && (isspace(m_line.at(m_line_cursor))))
    {
        if(m_line.at(m_line_cursor)==m_delimiter)
            return std::string(out_c_string);
        m_line_cursor++;
    }
    // Copy
    while((m_line_cursor<m_line.length()) && (m_line.at(m_line_cursor)!=m_delimiter))
    {
        out_c_string[cursor] = m_line.at(m_line_cursor);
        cursor++;
        m_line_cursor++;
    }
    m_line_cursor++;
    // Right trim
    cursor--;
    while((cursor>0) && (isspace(out_c_string[cursor])))
    {
        out_c_string[cursor] = '\0';
        cursor--;

    }

    return std::string(out_c_string);
}

int FileReader::GetInteger()
{
    return std::atoi(this->GetCharArray());
}

long FileReader::GetLong()
{
    return std::atol(this->GetCharArray());
}

double FileReader::GetDouble()
{
    return std::atof(this->GetCharArray());
}

/**
* Reads boolean value.
* False values are kept in FALSE_STR-array.
* Returns true if extracted string does not contain false-value.
*/
bool FileReader::GetBoolean()
{
    static std::string FALSE_STR[] = {"false", "f", "0"};

    std::locale loc;
    std::string result = this->GetStringTrimmed();

    for(std::string::size_type i=0; i<result.length(); i++)
        result[i] = std::tolower(result[i], loc);

    for(unsigned int i=0; i<sizeof(FALSE_STR)/sizeof(FALSE_STR[0]); i++)
    {
        if (result==FALSE_STR[i])
            return false;
    }

    return true;
}

/**
* Helper for GetInt and GetDouble methods.
* Inline version of GetString.
* Returns character array to be cast to numeric value.
*/
char* FileReader::GetCharArray()
{
    char* VOID_STRING = (char*)"0";
    static char out_c_string[STRING_BUFFER];

    for(int i=0; i<STRING_BUFFER; i++)
        out_c_string[i] = '\0';

    if((m_line.empty())||(m_line_cursor>=m_line.length()))
        return VOID_STRING;

    int cursor = 0;
    while((m_line_cursor<m_line.length()) && (m_line.at(m_line_cursor)!=m_delimiter))
    {
        out_c_string[cursor] = m_line.at(m_line_cursor);
        cursor++;
        m_line_cursor++;
    }
    m_line_cursor++;

    return out_c_string;
}

