/**
 * @file SXDictionary.hpp
 * @brief Implementation of the SXDictionary class.
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

#include "SXDictionary.hpp"
#include "SXString.hpp"

namespace spalx {

SXDictionary::SXDictionary()
{
    m_pMap = new std::unordered_map<std::string, SXObject*>;
}

SXDictionary::~SXDictionary()
{
    removeAllObjects();
    delete m_pMap;
    m_pMap = nullptr;
}

SXDictionary* SXDictionary::create()
{
    SXDictionary* pDictionary = new SXDictionary();

    if (pDictionary) {
        pDictionary->autorelease();
    }
        
    return pDictionary;
}

SXObject* SXDictionary::operator[](const std::string& rKey) const
{
    return objectForKey(rKey);
}

unsigned int SXDictionary::count() const
{
    return static_cast<unsigned int>(m_pMap->size());
}

SXArray* SXDictionary::allKeys() const
{
    SXArray* pKeys = SXArray::create();
    for (const auto& [key, value]: *m_pMap) {
        pKeys->addObject(SXString::create(key.c_str()));
    }
    return pKeys;
}

SXObject* SXDictionary::objectForKey(const std::string& rKey) const
{
    return (*m_pMap)[rKey];
}

void SXDictionary::setObject(SXObject* pObject, const std::string& rKey)
{
    // Remove previous object for this key (if exists).
    removeObjectForKey(rKey);
    pObject->retain();
    (*m_pMap)[rKey] = pObject;
}

void SXDictionary::removeObjectForKey(const std::string& rKey)
{
    SXObject* pObject = (*this)[rKey];
    if (pObject) {
        pObject->release();
        m_pMap->erase(rKey);
    }
}

void SXDictionary::removeObjectsForKeys(SXArray* pKeys)
{
    for (unsigned int i = 0; i < pKeys->count(); i++) {
        removeObjectForKey((dynamic_cast<SXString*>((*pKeys)[i]))->getCString());
    }
}

void SXDictionary::removeAllObjects()
{
    for (const auto& [key, value]: *m_pMap) {
        value->release();
    }
    m_pMap->clear();
}

SXDictionaryIterator SXDictionary::begin() const
{
    return m_pMap->begin();
}

SXDictionaryIterator SXDictionary::end() const
{
    return m_pMap->end();
}

SXObject* SXDictionary::copy() const
{
    SXDictionary* pDictionary = new SXDictionary();
    for (auto& [key, value]: *m_pMap) {
        SXObject* pTmpObject = value->copy();
        pDictionary->setObject(pTmpObject, key);
        pTmpObject->release();
    }
    return pDictionary;
}

}
