/**
 * @file SXString.hpp
 * @brief Implementation of the SXString class.
 *
 * @copyright (c) 2024 Artavazd Barseghyan
 * @details This software is released under the MIT License.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "SXString.hpp"
#include <fstream>
#include <sstream>

namespace spalx {

SXString::SXString()
:m_string("")
{
}

SXString::SXString(const char* pString)
:m_string(pString)
{
}

SXString::SXString(const SXString& rString)
:m_string(rString.getCString())
{
}

SXString::~SXString()
{
    m_string.clear();
}

SXString* SXString::create(const char* pString)
{
    SXString* pNewString = new SXString(pString);
    
    if (pNewString) {
        pNewString->autorelease();
    }
    
    return pNewString;
}

SXString* SXString::createWithContentsOfFile(const char* pFilePath)
{
    std::ifstream file(pFilePath);
    if (!file.is_open()) {
        return nullptr;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    return create(buffer.str().c_str());
}

SXString& SXString::operator=(const SXString& rOtherString)
{
    setValue(rOtherString.getCString());
    return *this;
}

char SXString::operator[](unsigned int index) const
{
    if (index < length()) {
        return m_string[index];
    }
    return '\0'; // Out-of-bounds access.
}

void SXString::setValue(const char* pString)
{
    m_string = pString;
}

int SXString::intValue() const
{
    if (m_string.empty()) {
        return 0;
    }
    return std::stoi(m_string);
}

unsigned long SXString::ulValue() const
{
    if (m_string.empty()) {
        return 0;
    }
    return std::stoul(m_string);
}

float SXString::floatValue() const
{
    if (m_string.empty()) {
        return 0.0f;
    }
    return std::stof(m_string);
}

double SXString::doubleValue() const
{
    if (m_string.empty()) {
        return 0.0;
    }
    return std::stod(m_string);
}

bool SXString::boolValue() const
{
    if (m_string.empty()) {
        return false;
    }
    return (intValue() != 0) || (m_string == "true");
}

const char* SXString::getCString() const
{
    return m_string.c_str();
}

unsigned long SXString::length() const
{
    return m_string.length();
}

int SXString::compare(const char* pString) const
{
    return m_string.compare(pString);
}

bool SXString::isEqual(const SXObject* pObject) const
{
    const SXString* pString = dynamic_cast<const SXString*>(pObject);
    return (pString != nullptr) && (m_string == pString->getCString());
}

SXObject* SXString::copy() const
{
    return new SXString(m_string.c_str());
}

}
