/**
 * @file SXData.hpp
 * @brief Implementation of the SXData class.
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

#include "SXData.hpp"
#include <fstream>

namespace spalx {

SXData::SXData()
{
    m_pBytes = new std::vector<char>;
}

SXData::~SXData()
{
    m_pBytes->clear();
    delete m_pBytes;
    m_pBytes = nullptr;
}

SXData* SXData::create()
{
    SXData* pData = new SXData();
    
    if (pData) {
        pData->autorelease();
    }
    
    return pData;
}

SXData* SXData::createWithContentsOfFile(const char* pFilePath)
{
    SXData* pData = create();
    
    if (pData->initWithContentsOfFile(pFilePath)) {
        return pData;
    }
    
    return nullptr;
}

bool SXData::initWithData(const std::vector<char>& rData)
{
    *m_pBytes = rData;
    return true;
}

bool SXData::initWithContentsOfFile(const char* pFilePath)
{
    std::fstream file(pFilePath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    m_pBytes->resize(fileSize);
    file.read(m_pBytes->data(), fileSize);
    
    if (!file) {
        return false;
    }
    
    file.close();
    
    return true;
}

unsigned long SXData::length() const
{
    return m_pBytes->size();
}

bool SXData::writeToFile(const char* pFilePath) const
{
    std::ofstream file(pFilePath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    file.write(m_pBytes->data(), m_pBytes->size());
    if (!file) {
        return false;
    }
    
    file.close();
    
    return true;
}

SXObject* SXData::copy() const
{
    SXData* pData = new SXData();
    bool res = pData->initWithData(*m_pBytes);
    
    if (!res) {
        delete pData;
        pData = nullptr;
    }
    
    return pData;
}

}
