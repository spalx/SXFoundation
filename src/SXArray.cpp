/**
 * @file SXArray.hpp
 * @brief Implementation of the SXArray class.
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

#include "SXArray.hpp"
#include "SXString.hpp"
#include <fstream>
#include <string>

namespace spalx {

SXArray::SXArray()
:m_count(0), m_capacity(SX_ARRAY_DEFAULT_CAPACITY_INCREMENT)
{
    m_pArray = new SXObject*[m_capacity](); // Initialize to nullptr.
}

SXArray::~SXArray()
{
    removeAllObjects();
    
    if (m_pArray) {
        delete[] m_pArray;
        m_pArray = nullptr;
    }
}

SXArray* SXArray::create()
{
    return createWithCapacity(SX_ARRAY_DEFAULT_CAPACITY_INCREMENT);
}

SXArray* SXArray::createWithCapacity(unsigned int capacity)
{
    SXArray* pArray = new SXArray();

    if (pArray) {
        if (pArray->initWithCapacity(capacity)) {
            pArray->autorelease();
        } else {
            delete pArray;
            pArray = nullptr;
        }
    }
        
    return pArray;
}

SXArray* SXArray::createWithArray(SXArray* pOtherArray)
{
    SXArray* pArray = static_cast<SXArray*>(pOtherArray->copy());

    if (pArray) {
        pArray->autorelease();
    }
    
    return pArray;
}

SXArray* SXArray::createWithContentsOfFile(const char* pFilePath)
{
    std::ifstream file(pFilePath);
    if (!file.is_open()) {
        return nullptr;
    }
    
    SXArray* pArray = create();
    std::string line;
    
    while (getline(file, line)) {
        SXString* pStr = SXString::create(line.c_str());
        pArray->addObject(pStr);
    }
    
    file.close();
    return pArray;
}

SXObject* SXArray::operator[](unsigned int index) const
{
    return objectAtIndex(index);
}

bool SXArray::init()
{
    return initWithCapacity(SX_ARRAY_DEFAULT_CAPACITY_INCREMENT);
}

bool SXArray::initWithCapacity(unsigned int capacity)
{
    resizeArray(capacity);
    m_count = 0;
    return true;
}

bool SXArray::initWithArray(SXArray* pOtherArray)
{
    if (initWithCapacity(pOtherArray->count())) {
        for (unsigned int i = 0; i < pOtherArray->count(); i++) {
            addObject((*pOtherArray)[i]);
        }
    }
    
    return false;
}

unsigned int SXArray::count() const
{
    return m_count;
}

unsigned int SXArray::indexOfObject(const SXObject* pObject) const
{
    for (unsigned int i = 0; i < m_count; i++) {
        if (m_pArray[i] == pObject) {
            return i;
        }
    }
    return UINT_MAX;
}

SXObject* SXArray::lastObject() const
{
    return (m_count > 0) ? m_pArray[m_count - 1] : nullptr;
}

SXObject* SXArray::objectAtIndex(unsigned int index) const
{
    return (index < m_count) ? m_pArray[index] : nullptr;
}

bool SXArray::containsObject(SXObject* pObject) const
{
    return (indexOfObject(pObject) != UINT_MAX);
}

void SXArray::addObject(SXObject* pObject)
{
    if (pObject) {
        if (m_count == m_capacity) {
            resizeArray(m_capacity + SX_ARRAY_DEFAULT_CAPACITY_INCREMENT);
        }

        pObject->retain();
        m_pArray[m_count++] = pObject;
    }
}

void SXArray::addObjectsFromArray(SXArray* pOtherArray)
{
    for (unsigned int i = 0; i < pOtherArray->count(); i++) {
        addObject((*pOtherArray)[i]);
    }
}

void SXArray::insertObject(SXObject* pObject, unsigned int index)
{
    if (index > m_count) {
        return;
    }
    
    if (m_count == m_capacity) {
        resizeArray(m_capacity + SX_ARRAY_DEFAULT_CAPACITY_INCREMENT);
    }
    
    // Swap all elements at index, making a room.
    for (unsigned int i = m_count; i > index; i--) {
        m_pArray[i] = m_pArray[i - 1];
    }
    
    pObject->retain();
    m_pArray[index] = pObject;
    m_count++;
}

void SXArray::removeObject(SXObject* pObject)
{
    unsigned int index = indexOfObject(pObject);
    if (index != UINT_MAX) {
        pObject->release();
        m_pArray[index] = nullptr;
        reorderArrayAtIndex(index);
        m_count--;
    }
}

void SXArray::removeObjectAtIndex(unsigned int index)
{
    if (index < m_count) {
        SXObject* pObject = m_pArray[index];
        pObject->release();
        m_pArray[index] = nullptr;
        reorderArrayAtIndex(index);
        m_count--;
    }
}

void SXArray::removeLastObject()
{
    if (m_count > 0) {
        SXObject* pObject = m_pArray[m_count - 1];
        pObject->release();
        m_pArray[m_count - 1] = nullptr;
        m_count--;
    }
}

void SXArray::removeObjectsInArray(SXArray* pOtherArray)
{
    for (unsigned int i = 0; i < pOtherArray->count(); i++) {
        removeObject((*pOtherArray)[i]);
    }
}

void SXArray::removeAllObjects()
{
    for (unsigned int i = 0; i < m_count; i++) {
        SXObject* pObject = m_pArray[i];
        if (pObject) {
            pObject->release();
            m_pArray[i] = nullptr;
        }
    }
    m_count = 0;
}

bool SXArray::isEqual(const SXObject* pObject) const
{
    const SXArray* pOtherArray = dynamic_cast<const SXArray*>(pObject);
    if (!pOtherArray || pOtherArray->count() != m_count) {
        return false;
    }
    
    for (unsigned int i = 0; i < m_count; i++) {
        if (!(*this)[i]->isEqual((*pOtherArray)[i])) {
            return false;
        }
    }
    
    return true;
}

SXObject* SXArray::copy() const
{
    SXArray* pArray = new SXArray();
    if (pArray->initWithCapacity(m_capacity)) {
        for (unsigned int i = 0; i < m_count; i++) {
            SXObject* pTmpObject = (*this)[i]->copy();
            pArray->addObject(pTmpObject);
            pTmpObject->release();
        }
    } else {
        delete pArray;
        pArray = nullptr;
    }
    
    return pArray;
}

void SXArray::resizeArray(unsigned int capacity)
{
    // Create a new array with the new capacity.
    SXObject** pArr = new SXObject*[capacity]();
    
    // Copy all existing elements.
    for (unsigned int i = 0; i < m_count; i++) {
        pArr[i] = m_pArray[i];
    }
    
    // Delete old array.
    delete [] m_pArray;
    
    m_pArray = pArr;
    m_capacity = capacity;
}

void SXArray::reorderArrayAtIndex(unsigned int index)
{
    for (unsigned int i = index + 1; i < m_count; i++) {
        m_pArray[i - 1] = m_pArray[i];
    }
}

}
