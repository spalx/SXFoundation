/**
 * @file SXNotificationCenter.hpp
 * @brief Implementation of the SXNotificationCenter class.
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

#include "SXNotificationCenter.hpp"
#include "SXArray.hpp"
#include <stdio.h>

namespace spalx {

SXNotificationCenter* SXNotificationCenter::pInstance = nullptr;
std::mutex SXNotificationCenter::mutex;

SXNotificationCenter* SXNotificationCenter::defaultCenter()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (!pInstance) {
        pInstance = new SXNotificationCenter();
    }
    
    return pInstance;
}

void SXNotificationCenter::addObserver(SXSelector<void(SXDictionary*)>* pSelector, const char* pName)
{
    SXArray* pObservers = dynamic_cast<SXArray*>((*m_pObservers)[pName]);
    if (!pObservers) {
        pObservers = new SXArray();
        pObservers->init();
        m_pObservers->setObject(pObservers, pName);
        pObservers->release();
    }
    pObservers->addObject(pSelector);
}

void SXNotificationCenter::removeObserver(SXSelector<void(SXDictionary*)>* pSelector, const char* pName)
{
    SXArray* pObservers = dynamic_cast<SXArray*>((*m_pObservers)[pName]);
    if (pObservers) {
        pObservers->removeObject(pSelector);
    }
}

void SXNotificationCenter::postNotification(const char* pName, SXDictionary* pUserInfo)
{
    const SXArray* pObservers = dynamic_cast<const SXArray*>((*m_pObservers)[pName]);
    if (pObservers) {
        for (unsigned int i = 0; i < pObservers->count(); i++) {
            SXSelector<void(SXDictionary*)>* pSelector = (SXSelector<void(SXDictionary*)>*)(*pObservers)[i];
            (*pSelector)(pUserInfo);
        }
    }
}

SXNotificationCenter::SXNotificationCenter()
{
    m_pObservers = new SXDictionary();
}

SXNotificationCenter::~SXNotificationCenter()
{
    if (m_pObservers) {
        m_pObservers->release();
        m_pObservers = nullptr;
    }
}

} // namespace spalx
