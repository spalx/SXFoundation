/**
 * @file SXSet.hpp
 * @brief Implementation of the SXSet class.
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

#include "SXSet.hpp"

namespace spalx {

SXSet::SXSet()
{
    m_pSet = new std::unordered_set<SXObject*>;
}

SXSet::~SXSet()
{
    removeAllObjects();
    delete m_pSet;
    m_pSet = nullptr;
}

SXSet* SXSet::create()
{
    SXSet* pSet = new SXSet();

    if (pSet) {
        pSet->autorelease();
    }
        
    return pSet;
}

unsigned int SXSet::count() const
{
    return static_cast<unsigned int>(m_pSet->size());
}

void SXSet::addObject(SXObject* pObject)
{
    if (!containsObject(pObject)) {
        pObject->retain();
        m_pSet->insert(pObject);
    }
}

bool SXSet::containsObject(SXObject* pObject) const
{
    return m_pSet->find(pObject) != m_pSet->end();
}

void SXSet::removeObject(SXObject* pObject)
{
    if (containsObject(pObject)) {
        pObject->release();
        m_pSet->erase(pObject);
    }
}

void SXSet::removeAllObjects()
{
    for (SXObject* pObj : *m_pSet) {
        pObj->release();
    }
    m_pSet->clear();
}

SXSetIterator SXSet::begin() const
{
    return m_pSet->begin();
}

SXSetIterator SXSet::end() const
{
    return m_pSet->end();
}

SXObject* SXSet::anyObject() const
{
    if (m_pSet->empty()) {
        return nullptr;
    }
    
    for (SXObject* pObj : *m_pSet) {
        if (pObj) {
            return pObj;
        }
    }

    return nullptr;
}

SXObject* SXSet::copy() const
{
    SXSet* pSet = new SXSet();
    
    for (SXObject* pObj : *m_pSet) {
        SXObject* pTmpObject = pObj->copy();
        pSet->addObject(pTmpObject);
        pTmpObject->release();
    }
    
    return pSet;
}

}
