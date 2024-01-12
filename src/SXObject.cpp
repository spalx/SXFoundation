/**
 * @file SXObject.hpp
 * @brief Implementation of the SXObject class.
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

#include "SXObject.hpp"
#include "SXPoolManager.hpp"

namespace spalx {

SXObject::SXObject()
:m_referenceCount(1) // All objects start with 1 reference count.
{
}

SXObject::~SXObject()
{
    
}

void SXObject::release()
{
    m_referenceCount--;
    
    if (m_referenceCount == 0) {
        delete this;
    }
}

void SXObject::retain()
{
    m_referenceCount++;
}

SXObject* SXObject::autorelease()
{
    SXPoolManager::sharedPoolManager()->addObject(this);
    release();
    
    return this;
}

unsigned int SXObject::retainCount() const
{
    return m_referenceCount;
}

bool SXObject::isEqual(const SXObject* pObject) const
{
    return this == pObject;
}

SXObject* SXObject::copy() const
{
    return nullptr;
}

}
